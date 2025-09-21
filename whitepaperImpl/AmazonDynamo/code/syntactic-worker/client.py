import os 
import math 
import time
import rpyc
import random
import pickle
import logging
import threading

from typing  import Dict
from bisect import bisect
from datetime import timedelta, datetime
from rpyc.utils.server import ThreadedServer

logging.basicConfig(level=logging.DEBUG)

class VectorClock:
    def __init__(self, ip:str, port:int, version_number:int, load:float, start_of_range:int) -> None:
        self.ip:str = ip
        self.version_number:int = version_number
        self.load:float = load 
        self.port:int = port
        self.start_of_range:str = start_of_range
        
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
        self.nodes = nodes #* In future when some service reply this then we can cache this too
        self.cache = dict() #* will store the routing table for some time.
        self.locate_key = dict() #* key -> node_hash, 
        self.all_nodes = []#* node hash -> (vector clock(ip, port, ...), last_update_time)
        ''' Universal constant/configure by users'''
        self.CACHE_TIMEOUT = 20
        self.READ = 3
        self.WRITE = 2
        self.HINTED_REPLICA_COUNT = 2
        self.RETRIES = 3 # can be replaced with log(nodes) in system
        ''' Some constants for return messages'''
        self.FAILURE:int = -1  
        self.SUCCESS:int = 0  
        self.IGNORE:int = 1
        self.EXPIRE:int = 3
        self.INVALID_RESOURCE = 4

        ''' Threads '''
        self.cache_lock = threading.Lock()
        self.cache_thread = threading.Thread(target=self.thread_clean_cache, args=(), daemon=True)

    '''
    This thread will look for all the cache data which is timeout and now need to remove
    since we are maintaining multiple level of indirection, through self.locate_key -> self.all_nodes
    and then self.cache, we need to remove those carefully
    '''
    def thread_clean_cache(self):
        logging.debug ("THREAD CALLED FOR CLEANING CACHE...")
        while True: 
            time.sleep(self.CACHE_TIMEOUT)
            stale_entries = []
            curr_time = time.time()
            for node, vc in self.cache.items():
                if curr_time - self.cache[node].updated_time > self.CACHE_TIMEOUT:
                    stale_entries.append(node)
            
            self.cache_lock.acquire()
            for stale in stale_entries:
                self.all_nodes.remove(stale) 
                del self.cache[stale]
            self.cache_lock.release()

    def deserialize(self, response):
        deserialize_response = {}
        for hash, vc in response.items():
            deserialize_response[hash] = VectorClock(ip=vc['ip'],port=vc['port'], 
                version_number=vc["version_number"], 
                load=vc["load"], start_of_range=vc["start_of_range"])
        return deserialize_response

    def serialize(self, response):
        serialized_response = {}
        for hash, vc in response.items():
            serialized_response[hash] = vc.to_dict()
        return serialized_response

    '''
        This is a generic function used by to update cache
        in two cases
        1) normal case when the node corresponsing to key is not present
        2) When we got self.INVALID_RESOURCE
    '''
    def update_cache(self, key, replica_nodes, controller_node):
        print ("Updating cache...")
        curr_time = time.time()
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
        
        # print ("Updated Cache!", self.cache)
    '''
    This function will fetch the routing table from some random node from self.nodes list
    '''
    def get_routing_info(self, key):
        while True:
            try:
                node = random.randint(0, len(self.nodes) - 1)
                who = random.randint(0, self.nodes[node]["vnodes"] - 1)
                #!FIXME: don't iterate on nodes
                url = (self.nodes[node]["ip"], int(self.nodes[node]["port"]) + who)
                conn = rpyc.connect(*url)
                conn._config['sync_request_timeout'] = None 
                replica_nodes, controller_node = conn.root.fetch_routing_info(key)
                replica_nodes = self.deserialize(pickle.loads(replica_nodes))
                # print ("Recieved: ", replica_nodes)
                self.update_cache(key, replica_nodes, controller_node)
                break
            except Exception as e:
                print (f"Some thing bad happened while fetching routing info...", e)
                continue
        

    '''
    This function will return whether 
    cache is stale or not, by checking two things
    - If entry doesn't exists
    - If it exists but it is stale
    - key -> self.locate_key -> node-hash -> self.cache[] -> vector clock
    '''

    def cache_is_stale(self, key) -> bool:

        curr_time = time.time()

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
        if self.cache_is_stale(key): # Fetch in case it is not there.
            self.get_routing_info(key)
        controller_node = self.locate_key[key]
        controller_node_idx = bisect(self.all_nodes, controller_node)
        controller_node_idx = controller_node_idx - 1 if controller_node_idx else 0 
        n = len(self.all_nodes)
        key_contained_by = []
        #* Since it is a ring, not a linear chain, we need to do %
        for pos in range(0, min(n ,self.READ)):
            key_contained_by.append(self.all_nodes[(controller_node_idx + pos) % n])
        return controller_node, key_contained_by


    '''
        Make this function really abstracted
        Talk to relevant nodes and then get the final output
        Write the logic to read now, based on concillation algo.
    '''
    def exposed_get(self, key):
        print ("GET is called!")
        controller_node, key_contained_by = self.get_key_containing_nodes(key)
        retry_count:int = 0
        while retry_count < self.RETRIES:
            print (f"Retrying ... {retry_count + 1}" )
            retry_count += 1
            break_reason = ''
            res = None
            for node in key_contained_by:
                try:
                    vc = self.cache[node]['vector_clock'] 
                    url = (vc.ip, vc.port) 
                    conn = rpyc.connect(*url)
                    conn._config['sync_request_timeout'] = None
                    res = conn.root.exposed_get(key)
                    print (f"Response : {res['status']}")
                    
                    if res['status'] == self.SUCCESS: 
                        print (f"Read successfully: {res['value']}")
                        return {"status": self.SUCCESS, "value": res['value']}
                    elif res['status'] == self.INVALID_RESOURCE: 
                        break_reason = self.INVALID_RESOURCE
                        break
                except Exception as e:
                    print ("Some thing bad happen ", e)
                    pass 
            if break_reason == self.INVALID_RESOURCE: 
                self.update_cache(key, res["replica_nodes"], res["controller_node"])
            else:
                break
        return {"status": self.FAILURE, "msg": "Fail in get!"}

    '''
        Write the logic to write now
        We need this service to be mostly say ok to client
    '''
    def exposed_put(self, key, value):
        print (f"PUT IS CALLED: {key}, {value}")
        retry_count:int = 0
        while retry_count < self.RETRIES:
            controller_node, key_contained_by = self.get_key_containing_nodes(key)
            print (f"Retrying ... {retry_count + 1}" )
            retry_count += 1
            break_reason = ''
            res = None
            for node in key_contained_by:
                try:
                    vc = self.cache[node]["vector_clock"] 
                    url = (vc.ip, vc.port) 
                    print (f"URL = {url}")
                    conn = rpyc.connect(*url)
                    conn._config['sync_request_timeout'] = None
                    res = conn.root.exposed_put(key, value)
                    print (f"Response : {res['status']}")
                    if res["status"] == self.SUCCESS: 
                        print (f"Write successfully: {res['msg']}")
                        return {"status": self.SUCCESS, "value": res['msg']}
                    elif res["status"] == self.INVALID_RESOURCE: 
                        break_reason = self.INVALID_RESOURCE
                        break
                except Exception as e:
                    print ("Expection in client put", e)
                    pass 
            if break_reason == self.INVALID_RESOURCE: 
                self.update_cache(key, res["replica_nodes"], res["controller_node"])
        return {"status": self.FAILURE, "msg": "Fail in PUT!"}

        pass

if __name__ == '__main__':
    port = 6001
    #TODO: Later move these to some service provided by Hashring or some 
    #TODO: complete independent service also ok.
    nodes = [
        {
            'username': 'sourav',
            'ip': '10.237.27.95',
            'port': 3000,
            'vnodes': 4
        },
        {
            'username': 'baadalvm',
            'ip': '10.17.50.254',
            'port': 3000,
            'vnodes': 4
        }
    ]
    print (f"Client is listening at port = {port}...")
    ThreadedServer(Client(nodes), hostname='0.0.0.0', port=port).start()