import os 
import rpyc
import math 
import time
import pickle
import random
import logging
import threading


from typing  import Dict
from bisect import bisect
from pprint import pprint
from datetime import timedelta, datetime
from rpyc.utils.server import ThreadedServer
from typing import List, Set, Dict, Tuple, Callable, Iterator, Union, Optional, Any, Counter, Literal, NoReturn

logging.basicConfig(level=logging.DEBUG)


class VectorClock:
    def __init__(self, ip:str, port:int, version_number:int, load:float, start_of_range:int) -> None:
        self.ip:str = ip
        self.version_number:int = version_number
        self.load:float = load 
        self.port:int = port
        self.start_of_range = start_of_range
        
    def to_dict(self) -> Dict:
        return {
            "ip": self.ip,
            "version_number": self.version_number,
            "load": self.load,
            "port": self.port,
            "start_of_range": self.start_of_range 
        }

class Client(rpyc.Service):
    def __init__(self, nodes) -> None:
        self.nodes: Any = nodes #* In future when some service reply this then we can cache this too
        self.cache = dict() #* will store the routing table for some time.
        ''' Key to Controller node hash (or id)'''
        self.locate_key = dict()
        ''' node hash -> (vector clock(ip, port, ...), last_update_time) ''' 
        self.all_nodes = list()
        ''' Universal constant/configure by users'''
        self.CACHE_TIMEOUT = 15
        self.READ = 3
        self.WRITE = 2
        self.N = self.READ + self.WRITE - 1
        self.HINTED_REPLICA_COUNT = 2
        self.RETRIES = 3 # can be replaced with log(nodes) in system
        ''' Some constants for return messages'''
        self.FAILURE:int = -1  
        self.SUCCESS:int = 0  
        self.IGNORE:int = 1
        self.EXPIRE:int = 3
        self.INVALID_RESOURCE = 4
        ''' IF there is unknown '''
        self.FIVE_STAR = 100 
        
        ''' Threads '''
        self.cache_lock = threading.Lock()
        self.cache_thread = threading.Thread(target=self.thread_clean_cache, args=(), daemon=True)

    '''
    This thread will look for all the cache data which is timeout and now need to remove
    since we are maintaining multiple level of indirection, through self.locate_key -> self.all_nodes
    and then self.cache, we need to remove those carefully
    '''
    def thread_clean_cache(self) -> NoReturn:
        logging.debug ("THREAD CALLED FOR CLEANING CACHE...")
        while True: 
            time.sleep(self.CACHE_TIMEOUT)
            stale_entries: list[Any] = list()
            curr_time: float = time.time()
            for node, vc in self.cache.items():
                if curr_time - self.cache[node].updated_time > self.CACHE_TIMEOUT:
                    stale_entries.append(node)
            self.cache_lock.acquire()
            for stale in stale_entries:
                self.all_nodes.remove(stale) 
                del self.cache[stale]
            self.cache_lock.release()

    def deserialize(self, response)-> Dict[Any, Any]:
        deserialize_response: Dict[Any, Any] = dict()
        for hash, vc in response.items():
            deserialize_response[hash] = VectorClock(ip=vc['ip'],port=vc['port'], 
                version_number=vc["version_number"], 
                load=vc["load"], start_of_range=vc["start_of_range"])    
        return deserialize_response

    def serialize(self, response)-> List[Any]:
        serialized_response:list = list()
        for hash, vc in response.items():
            serialized_response[hash] = vc.to_dict()
        return serialized_response

    '''
        This is a generic function used by to update cache
        in two cases
        1) normal case when the node corresponsing to key is not present
        2) When we got self.INVALID_RESOURCE
    '''
    def update_cache(self, key, replica_nodes, controller_node) -> None:
        logging.debug ("Updating cache...")
        curr_time: float = time.time()
        self.locate_key[key] = controller_node 
        for node_hash, vc in replica_nodes.items():
            if node_hash in self.cache.keys():
                self.cache_lock.acquire()
                if self.cache[node_hash]["vector_clock"].version_number < vc.version_number: # update only version number is newest
                    self.cache[node_hash] = {"vector_clock": vc, "updated_time": curr_time}
                self.cache_lock.release()
            else:     # if this is the fresh entry then simply update
                self.cache_lock.acquire()
                self.all_nodes.append(node_hash)
                self.all_nodes.sort()
                self.cache[node_hash] = {"vector_clock": vc, "updated_time": curr_time}
                self.cache_lock.release()
        logging.debug ("Updated Cache!")
    '''
    This function will fetch the routing table from some random node from self.nodes list
    '''
    def get_routing_info(self, key) -> None:
        while True:
            try:
                node: int = random.randint(0, len(self.nodes) - 1)
                who: int = random.randint(0, self.nodes[node]["vnodes"] - 1)
                #!FIXME: don't iterate on nodes
                url = (self.nodes[node]["ip"], int(self.nodes[node]["port"]) + who)
                conn = rpyc.connect(*url)
                conn._config['sync_request_timeout'] = 15
                replica_nodes, controller_node = conn.root.fetch_routing_info(key)
                replica_nodes = self.deserialize(response=pickle.loads(replica_nodes))
                self.update_cache(key=key, replica_nodes=replica_nodes, controller_node=controller_node)
                break
            except Exception as e:
                logging.debug (f"Some thing bad happened while fetching routing info...{e}")
                continue
        

    '''
    This function will return whether 
    cache is stale or not, by checking two things
    - If entry doesn't exists
    - If it exists but it is stale
    - key -> self.locate_key -> node-hash -> self.cache[] -> vector clock
    '''

    def cache_is_stale(self, key) -> bool:
        curr_time: float = time.time()
        if key not in self.locate_key:
            return True
        elif key in self.locate_key:
            controller_node = self.locate_key[key]
            if curr_time - self.cache[controller_node]['updated_time'] > self.CACHE_TIMEOUT:
                return True 
        return False 

    '''
    This function will return the nodes which are potential candidate
    for the given key
    '''
    def get_key_containing_nodes(self, key):
        if self.cache_is_stale(key=key): # Fetch in case it is not there.
            self.get_routing_info(key=key)
        controller_node = self.locate_key[key]
        controller_node_idx: int = bisect(self.all_nodes, controller_node)
        controller_node_idx = controller_node_idx - 1 if controller_node_idx else 0 
        n: int = len(self.all_nodes)
        logging.debug (f'Len = {n} and self.N = {self.N}')
        key_contained_by = []
        #* Since it is a ring, not a linear chain, we need to do %
        for pos in range(0, min(n, self.N)):
            key_contained_by.append(self.all_nodes[(controller_node_idx + pos) % n])
        return controller_node, key_contained_by


    def getNodes(self, key_contained_by) -> None:
        for node in key_contained_by:
            try:
                vc = self.cache[node]['vector_clock'] 
                logging.debug (f' IP = {vc.ip} and PORT = {vc.port}')
            except:
                logging.debug ("Can't fetch")

    '''
        Make this function really abstracted
        Talk to relevant nodes and then get the final output
        Write the logic to read now, based on concillation algo.
    '''
    def exposed_get(self, key)-> Dict[str, Any]:
        logging.debug ("GET is called!")
        controller_node, key_contained_by = self.get_key_containing_nodes(key=key)
        retry_count:int = 0
        while retry_count < self.RETRIES:
            logging.debug (f"Retrying ... {retry_count + 1}" )
            self.getNodes(key_contained_by=key_contained_by)            
            retry_count += 1
            break_reason: int = self.FIVE_STAR # Invalid break reason
            res = None
            for node in key_contained_by:
                try:
                    allow_replicas = (node != controller_node) 
                    vc = self.cache[node]['vector_clock'] 
                    url: Tuple[Any, Any] = (vc.ip, vc.port) 
                    conn = rpyc.connect(*url)
                    logging.debug (f'=================')
                    pprint (f"IP : {vc.ip} and PORT: {vc.port}")
                    logging.debug (f'=================')
                    conn._config['sync_request_timeout'] = 5
                    res = conn.root.exposed_get(key, allow_replicas)
                    # logging.debug (f"Response : {res['status']}")
                    logging.debug (f'Response : {res}')
                    if res and (res['status'] == self.SUCCESS): 
                        logging.debug (f"Read successfully: {res['value']}")
                        return {"status": self.SUCCESS, "value": res['value']}
                    elif res and (res['status'] == self.INVALID_RESOURCE): 
                        break_reason = self.INVALID_RESOURCE
                        # break
                except Exception as e:
                    logging.debug ("Some thing bad happen in get ", e)
                    pass 
            if break_reason == self.INVALID_RESOURCE: 
                self.update_cache(key=key, replica_nodes=res["replica_nodes"], controller_node=res["controller_node"])
            else:
                break
        return {"status": self.FAILURE, "msg": "Fail in get!"}

    '''
        Write the logic to write now
        We need this service to be mostly say ok to client
    '''
    def exposed_put(self, key, value) -> Dict[str, Any]:
        logging.debug (f"PUT IS CALLED: {key}, {value}")
        retry_count:int = 0
        
        while retry_count < self.RETRIES:
            controller_node, key_contained_by = self.get_key_containing_nodes(key=key)
            logging.debug (f"Retrying ... {retry_count + 1}" )
            self.getNodes(key_contained_by=key_contained_by)            
            
            retry_count += 1
            break_reason = ''
            res = None

            for node in key_contained_by:
                try:
                    ''' For the purpose of allowing replicas to accept the put request from the client'''
                    allow_replicas = (node != controller_node) 
                    vc = self.cache[node]["vector_clock"] 
                    url = (vc.ip, vc.port) 
                    logging.debug (f'=================')
                    pprint (f"IP : {vc.ip} and PORT: {vc.port}")
                    logging.debug (f'=================')
                    conn = rpyc.connect(*url)
                    # conn._config['sync_request_timeout'] = None
                    res = conn.root.exposed_put(key, value, allow_replicas)
                    logging.debug (f"Response : {res['status']}")
                    if res["status"] == self.SUCCESS: 
                        logging.debug (f"Write successfully: {res['msg']}")
                        return {"status": self.SUCCESS, "value": res['msg']}
                    elif res["status"] == self.INVALID_RESOURCE: 
                        break_reason = self.INVALID_RESOURCE
                        break
                except Exception as e:
                    logging.debug ("Expection in client put", e)
                    pass 
            if break_reason == self.INVALID_RESOURCE: 
                self.update_cache(key=key, replica_nodes=res["replica_nodes"], controller_node=res["controller_node"])
        return {"status": self.FAILURE, "msg": "Fail in PUT!"}

if __name__ == '__main__':
    port = 6002
    #TODO: Later move these to some service provided by Hashring or some 
    #TODO: complete independent service also ok.

    nodes: List[Dict[str, Any]] = [
        {
            'username': 'sourav',
            'ip': '10.237.27.95',
            'port': 3100,
            'vnodes': 4
        },
        {
            'username': 'baadalvm',
            'ip': '10.17.50.254',
            'port': 3100,
            'vnodes': 4
        }
    ]
    logging.debug (f"Client is listening at port = {port}...")
    ThreadedServer(Client(nodes=nodes), hostname='0.0.0.0', port=port).start()