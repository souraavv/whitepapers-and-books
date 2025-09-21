import os 
import sys 
import time 
import json
import math
import rpyc 
import socket 
import pickle
import random
import logging 
import threading
import redis 

from hashlib import md5
from pprint import pprint
from bisect import bisect 
from json import JSONEncoder
from datetime import datetime 
from rpyc.utils.server import ThreadedServer
from typing import List, Set, Dict, Tuple, Callable, Iterator, Union, Optional, Any, Counter, Literal, NoReturn
 
logging.basicConfig(level=logging.DEBUG)

'''
gossip_data:
    “end_of_range”: {ip_x, v_id, version_number, load, start_of_range}
    
'''

class VectorClock:
    def __init__(self, ip: str, port: int, version_number: int, load: float, start_of_range: int):
        self.ip: str = ip
        self.version_number: int = version_number
        self.load: float = load 
        self.port: int = port
        self.start_of_range: int = start_of_range
    
    ''' From vector clock to dict. '''
    def to_dict(self) -> Dict:
        return {
            "ip": self.ip,
            "version_number": self.version_number,
            "load": self.load,
            "port": self.port,
            "start_of_range": self.start_of_range 
        }
    

class Worker(rpyc.Service):
    def __init__(self, port:int, redis_port:int) -> None:
        '''
        Constants (or configurable)
        '''
        self.FAILURE:int = -1  
        self.SUCCESS:int = 0  
        self.IGNORE:int = 1
        self.EXPIRE:int = 3
        self.INVALID_RESOURCE = 4
        self.GOSSIP_INTERVAL:int = 5
        self.PING_DOWN_NODE_INTERVAL:int = 30
        self.REPLICATE_SYNC_TIMEOUT:int = 5
        self.REPLICATED_TIMEOUT:int = 15
        self.REPLICA_RETRY = 2
        self.READ:int = 3 # Take it as config from client
        self.WRITE:int = 2 # Take it as config from client
        self.REDIS_WRITE_RETRY:int = 3 # to retry on watch error
        self.REDIS_PORT:int = redis_port 
        self.N = self.READ + self.WRITE - 1# set it properly
        self.hashmap: str = f'hash-map-{port}'
        self.sorted_set: str = f'sorted-set-{port}' # this is over the keys of hashmap so that efficient search can be made O(logN + m)
        self.FORMAT = "%Y-%m-%d %H:%M:%S"
        '''
        Locks
        '''
        self.lock_routing_table = threading.Lock() # Active nodes
        self.lock_down_routing_table = threading.Lock() # Down nodes
        '''
        Meta data a worker need to have
        '''
        self.ip:str = 'localhost'
        self.port:int = port # port at which this worker node will server
        self.start_of_range:str = "-1" 
        self.end_of_range: str = "-1"
        self.hash_ring_url: tuple[Literal['10.194.58.46'], Literal[3000]] = ('10.194.58.46', 3000) # hash ring 
        self.routing_table = dict() #* Will store the routing table of active nodes
        self.down_routing_table = dict() #* Will store all those entry which are down now
        self.hash_function: Callable[..., int] = (lambda key: int(md5(string=str(key).encode(encoding="utf-8")).hexdigest(), base=16)) # same hash function is used in hashring
        self.requests_log = dict() # Used by background thread which will keep sending the data to these nodes (to satisfy replica property)
        self.get_requests_log = dict() # response_id -> (fresh_value, fresh_timestamp)
        
        ''' Local state which will help our State based CRDT to work
            This will store timestamp(uid) where + means, increment operation
            and - with timestamp means decrement operation 
        '''
        self.state = dict()
        '''
        Redis instance
        '''
        self.rds = redis.Redis(host='localhost', port=self.REDIS_PORT, db=0, decode_responses=True)
        
        '''
        Setting up daemon threads
        '''
        gossip_thread = threading.Thread(target=self.start_gossip, args = (), daemon=True)
        ping_down_node_thread = threading.Thread(target=self.thread_ping_down_node, args = (), daemon=True)
        replicate_thread = threading.Thread(target=self.replicate, args = (), daemon=True)
        ''' Replica sync thread '''
        replica_sync_thread = threading.Thread(target=self.sync_replica, args =(), daemon=True)

        gossip_thread.start()
        ping_down_node_thread.start()
        replicate_thread.start()
        replica_sync_thread.start()
 

    def deserialize(self, routing_table) -> Dict[Any, Any]:
        deserialize_routing_table: Dict[Any, Any] = dict()
        for hash, vc in routing_table.items():
            deserialize_routing_table[hash] = VectorClock(ip=vc['ip'],port=vc['port'], 
                                                          version_number=vc["version_number"], 
                                                          load=vc["load"], start_of_range=vc["start_of_range"])
        return deserialize_routing_table

    def serialize(self, routing_table) -> Dict[Any, Any]:
        serialized_routing_table: Dict[Any, Any] = dict()
        for hash, vc in routing_table.items():
            serialized_routing_table[hash] = vc.to_dict()
        return serialized_routing_table

    '''
    This function will fetch for which it is now the new primary. Since it is added fresh now.
    '''

    def get_keys_from_redis_by_range(self, start_range, end_range)-> Tuple[Dict[Any, Any], Dict[Any, Any]]:
        logging.info ("fetching from redis....")
        res: list[str] = self.rds.zrangebylex(name=self.sorted_set, min='['+start_range, max='['+ end_range)
        keys_value = dict()
        keys_timestamp = dict() 
        for key in res:
            key = str(self.rds.get(name=str(key)))
            keys_value[key] = str(self.rds.hget(name=self.hashmap, key=key))
            keys_timestamp[key] = str(self.rds.get(name=key))
        return keys_value, keys_timestamp
    '''
    This function will be called by new node which will ask for fetching
    the key:value from the neighbour nodes
    '''
    def exposed_giveback_keys(self, start_range, end_range) -> Dict[str, Any]:
        try:
            keys_value, keys_timestamp = self.get_keys_from_redis_by_range(start_range=start_range, end_range=end_range)
            return {
                    "status": self.SUCCESS, 
                    "keys_value": pickle.dumps(keys_value), 
                    "keys_timestamp": pickle.dumps(keys_timestamp)
            } 
        except Exception as e:
            logging.debug (f"Something bad happen in giveback keys...{e}")
            return {
                "status": self.FAILURE,
                "message": e
            }

    '''
    Since this is the new node added to the hashring, its first duty 
    is to fetch the keys which it owns and thus It will talk to 
    old primary and secondaries.
    '''
    def fetch_and_store_keys(self, primary, replica_nodes) -> None:
        logging.info ("\nA NEW NODE IS FETCHING KEYS...")
        next_nodes: list[Any] = list()
        if primary == -1:
            logging.debug ("First ever node in the ring...")
            return 
        next_nodes.append(primary)
        next_nodes.extend(replica_nodes)
        logging.debug (f'all nodes: ', next_nodes)
        for node in next_nodes:
            max_retry, fetching_done = 3, False
            while max_retry > 0:
                try:
                    ''' First try to make a contact with primary'''
                    hostname, port, _ = node
                    url: Tuple[Any, Any] = (hostname, port)
                    logging.debug (f'Fetching from {hostname}, {port}')
                    conn = rpyc.connect(*url) 
                    conn._config['sync_request_timeout'] = 5      
                    ''' Get the data from the old primary '''
                    res = conn.root.giveback_keys(self.start_of_range, self.end_of_range)
                    if res['status'] == self.SUCCESS:
                        ''' Setup the data to the redis '''
                        keys_value = pickle.loads(res['keys_value'])
                        keys_timestamp = pickle.loads(res['key_timestamp'])
                        logging.debug (f"Fetching keys..\nAll keys fetched: {keys_value}")
                        with self.rds.pipeline() as pipe:
                            pipe.watch(self.hashmap)
                            pipe.watch(self.sorted_set)
                            pipe.multi()
                            while True:
                                try:
                                    for key, value in keys_value.items():
                                        key_hash = str(self.hash_function(key))
                                        pipe.hset(name=self.hashmap, key=key, value=value)
                                        pipe.zadd(name=self.sorted_set, mapping={key_hash: 1})
                                        pipe.set(name=key_hash, value=key)
                                    for key, value in keys_timestamp.items():
                                        pipe.set(key, value)
                                    logging.debug ("Succefully bring all the keys")
                                    pipe.execute()
                                    break
                                except redis.WatchError as e:
                                    logging.debug ("Watch error inside fetch and store keys: ", e)
                                    continue
                    else:
                        logging.debug ("Didn't succeed")
                        logging.debug (res)

                    fetching_done = True
                    break
                except Exception as e:
                    max_retry -= 1
                    continue

            if fetching_done:
                break
        

    def exposed_init_table(self, routing_info, primary, replica_nodes) -> None:
        logging.debug (msg="NEW NODE ADDED IN RING...")
        new_added = routing_info['new_added']
        self.routing_table[str(new_added['end_of_range'])] = VectorClock(ip=new_added['ip'],
        port=new_added['port'], version_number=new_added["version_number"],
        load=new_added["load"], start_of_range=new_added["start_of_range"]) 
        self.start_of_range = new_added['start_of_range']
        self.end_of_range = new_added['end_of_range']
        self.fetch_and_store_keys(primary=primary, replica_nodes=replica_nodes) 
        
        
    def exposed_update_table(self, routing_info:Dict[Any, Any]) -> None:
        ''' Update your starting point '''
        self.lock_routing_table.acquire()
        self.routing_table[str(self.end_of_range)].start_of_range = routing_info['new_start']
        self.routing_table[str(self.end_of_range)].version_number += 1
        ''' Add the fresh entry to the table '''
        new_added = routing_info['new_added']
        self.routing_table[str(new_added['end_of_range'])] = VectorClock(ip=new_added['ip'],
        port = new_added['port'], version_number = new_added["version_number"],
        load = new_added["load"], start_of_range = new_added["start_of_range"]) 
        self.lock_routing_table.release()
        
    '''
    This will be background thread which will keep running at some interval
    '''
    def ping(self, ip, port, timeout = 2) -> bool:
        logging.debug (f"pinging.... {ip}:{port}")
        sock = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM) #presumably 
        sock.settimeout(timeout)
        try:
            sock.connect((ip, port))
        except:
            logging.debug ("cant still ping :(")
            return False
        else:
            logging.debug ("Can ping :)")
            sock.close()
            return True

    def ping_thread(self, to_ping) -> None:
        # logging.debug (f"need to ping: by:{self.port}: nodes = ",  to_ping)
        nodes = set(self.routing_table.keys())
        down_nodes = set(self.down_routing_table.keys())    
        for node in to_ping:  
            if node in down_nodes:
                vc = self.down_routing_table[str(node)]
                ip, port = vc.ip, int(vc.port)
                response: bool = self.ping(ip=ip, port=port)
                if response == True:
                    logging.debug ("\nREMOVE FROM DOWN NODE: ", node)
                    self.lock_down_routing_table.acquire()
                    del self.down_routing_table[str(node)]
                    self.lock_down_routing_table.release()
                    logging.debug ("\nADDING TO ACTIVE NODE: ", node)
                    self.lock_routing_table.acquire()
                    # vc.version_number += 1
                    self.routing_table[node] = vc 
                    self.lock_routing_table.release()

            elif node in nodes: 
                vc = self.routing_table[str(node)]
                ip, port = vc.ip, int(vc.port)
                response = self.ping(ip=ip, port=port)  
                if response == False:
                    logging.debug ("REMOVING FROM ACTIVE ", node)
                    self.lock_routing_table.acquire()
                    del self.routing_table[str(node)]
                    self.lock_routing_table.release()
                    logging.debug ("ADDING TO ACTIVE ", node)
                    self.lock_down_routing_table.acquire()
                    # vc.version_number += 1
                    self.down_routing_table[str(node)] = vc
                    self.lock_down_routing_table.release()

    '''
    This is a thread which will try to ping self down nodes
    '''
    def thread_ping_down_node(self) -> NoReturn:
        while True:
            if (len(self.down_routing_table)):
                logging.debug ("\nPINGING DOWN NODE...")
                self.ping_thread(to_ping=list(self.down_routing_table.keys()))
            time.sleep(self.PING_DOWN_NODE_INTERVAL)
            
    '''
    Start the gossip
    '''
    def start_gossip(self) -> NoReturn:
        while True: 
            time.sleep(self.GOSSIP_INTERVAL) # Take some rest before gossip
            self.print_routing_table()
            if (len(self.routing_table) or len(self.down_routing_table)):
                nodes = list(self.routing_table.keys())
                nodes.sort() # Get the nodes
                down_nodes = set(self.down_routing_table.keys()) # Get the down keys
                n:int = len(self.routing_table)
                idx:int = random.randint(0, n - 1)
                talk_to = nodes[idx]
                node:VectorClock = self.routing_table[talk_to] # pick a random node to talk
                url = (node.ip, node.port)
                if (node.ip == self.ip) and (node.port == self.port): # Can't gossip with self, need a friend
                    continue
                ask_guest_to_ping = list()
                try:
                    conn = rpyc.connect(*url) 
                    conn._config['sync_request_timeout'] = 5
                    '''
                    We are using 2-way communication to, in first go we send
                    both our active and down routing table and then in response
                    we are getting what entry we need to udpate
                    '''        
                    ''' Dump both active routing table and down routing table '''
                    routing_table, down_routing_table = pickle.dumps(self.serialize(routing_table=self.routing_table)), pickle.dumps(self.serialize(routing_table=self.down_routing_table))
                    ''' After doing chit chat get some gift '''
                    gift_routing_table, gift_down_routing_table, ask_guest_to_ping = conn.root.do_chit_chat(routing_table, down_routing_table)
                    ''' Unwrap the gift '''
                    gift_routing_table: Dict[Any, Any] = self.deserialize(routing_table=pickle.loads(gift_routing_table))
                    gift_down_routing_table: Dict[Any, Any] = self.deserialize(routing_table=pickle.loads(gift_down_routing_table))
                    ''' node here represent the hash(or end_of_key)
                    update the outdated entry in both routing and down routing table 
                    update your routing table '''
                    for node, vc in gift_routing_table.items():
                        if node not in self.routing_table.keys():
                            self.routing_table[node] = vc 
                    for node, vc in gift_down_routing_table.items():
                        if node not in self.down_routing_table.keys():
                            self.down_routing_table[node] = vc 
                    #* ping the nodes.
                except Exception as e: 
                    logging.debug ("Some thing bad happen while chit chat..", e)
                    ask_guest_to_ping.append(nodes[idx])

                ''' To all those whom I was not able to connect during chit-chat'''
                if len(ask_guest_to_ping): 
                    ping_thread = threading.Thread(target=self.ping_thread, args = (ask_guest_to_ping, ))
                    ping_thread.start()

    '''
    This function is used by replicas to do chit chat so that they 
    can sycn each other, this is basically other(guest) replicas send 
    some info to a node and that node process (see where it is outdated)
    and then also wrap gift for the guest, which mean the info which is
    new to the guest
    '''
    def exposed_replicas_chit_chat(self, start_key_range, end_key_range, guest_keys_value, guest_keys_timestamp) -> Dict[str, Any]:
        self_keys_value, self_keys_timestamp = self.get_keys_from_redis_by_range(start_range=start_key_range, end_range=end_key_range)
        # logging.debug ("---"*10)
        # logging.debug (type(self_keys_timestamp), type(self_keys_timestamp))
        # logging.debug ("---"*10)
        
        guest_keys_value = pickle.loads(guest_keys_value)
        guest_keys_timestamp = pickle.loads(guest_keys_timestamp)
        gift_keys_value, gift_keys_timestamp = dict(), dict()
        with self.rds.pipeline() as pipe:
            pipe.watch(self.sorted_set)
            pipe.watch(self.hashmap)
            pipe.multi()
            while True:
                try:
                    for key, timestamp in guest_keys_timestamp.items():
                        exits: bool = key in self_keys_timestamp.keys()
                        depreciated_key: Any | Literal[False] = exits and (guest_keys_timestamp[key] > self_keys_timestamp[key])
                        if depreciated_key:
                            key_hash = str(self.hash_function(key))
                            if (not exits):
                                pipe.set(name=key_hash, value=key)
                                pipe.zadd(name=self.sorted_set, mapping={key_hash: 1})
                            pipe.hset(name=self.hashmap, key=key, value=guest_keys_value[key])
                            pipe.set(name=key, value=timestamp)
                        else: 
                            if self_keys_timestamp[key] > timestamp:
                                gift_keys_value[key] = self_keys_value[key]
                                gift_keys_timestamp[key] = self_keys_timestamp[key]
                    
                    pipe.execute()
                    break 
                except Exception as e:
                    logging.debug ("Redis watch error", e)
                    time.sleep(10)
                    continue

        for key, value in self_keys_value.items():
            if key not in guest_keys_value:
                gift_keys_value[key] = value 
                gift_keys_timestamp[key] = self_keys_timestamp[key]
        
        return {
            "status": self.SUCCESS, 
            "gift_keys_value": pickle.dumps(gift_keys_value), 
            "gift_keys_timestamp": pickle.dumps(gift_keys_timestamp)
        }
             
    '''
    Replica sycn thread: Below is a thread, which keep running in order
    to make replica in sync so that even in case of failure if some node
    was down for few time and later came up, it will eventually get the
    data from other nodes. This makes code more resilient to the fault 
    '''

    def sync_replica(self)-> None:
        while True:
            try:
                time.sleep(self.REPLICATE_SYNC_TIMEOUT)
                logging.debug ("-----"*10)
                logging.debug ("REPLICAS ARE GETTING SYNC!...")
                logging.debug ("-----"*10)
                nodes = list(self.routing_table.keys())
                if (len(nodes) <= 1):
                    logging.debug ("Not enough nodes for replicas to do chit chat")
                    continue
                nodes = sorted(nodes)
                my_pos: int = bisect(nodes, self.start_of_range)
                boundary: int = min(len(nodes) - 1, self.N)
                random_idx: int = random.randint(1, boundary)
                start_key_range = self.routing_table[nodes[my_pos - boundary]].start_of_range
                random_node = end_key_range = nodes[my_pos - random_idx]
                ip, port = self.routing_table[random_node].ip, self.routing_table[random_node].port
                keys_value, keys_timestamp = self.get_keys_from_redis_by_range(start_key_range, end_key_range)
                conn = rpyc.connect(ip, port)
                conn._config['sync_request_timeout'] = 10         
        
                keys_value: bytes = pickle.dumps(keys_value)
                keys_timestamp: bytes = pickle.dumps(keys_timestamp)
                res = conn.root.replicas_chit_chat(start_key_range, end_key_range, keys_value, keys_timestamp)
                if res['status'] == self.SUCCESS:
                    gift_keys_value, gift_keys_timestamp = pickle.loads(res['gift_keys_value']), pickle.loads(res['gift_keys_timestamp'])
                    # logging.debug (f"Types of gift: {gift_keys_value} and {gift_keys_timestamp}\n")
                    with self.rds.pipeline() as pipe:
                        pipe.watch(self.hashmap)
                        pipe.watch(self.sorted_set)
                        pipe.multi()
                        while True:
                            try: 
                                for key, value in gift_keys_value.items():
                                    key_hash = str(self.hash_function(key))
                                    pipe.set(name=key_hash, value=key)
                                    pipe.zadd(name=self.sorted_set, mapping={key_hash: 1})
                                    pipe.hset(name=self.hashmap, key=key, value=value)
                                    pipe.set(name=key, value=gift_keys_timestamp[key])
                                pipe.execute()
                                break 
                            except Exception as e:
                                logging.debug ("Redis Watch error ", e)
                                continue
            except Exception as e: 
                logging.debug ("Connection issue")
                continue
        
    '''
    Do chit chat
    '''
    def exposed_do_chit_chat(self, routing_table, down_routing_table) -> Any:
        ''' Unwrap the gift '''
        routing_table: Dict[Any, Any] = self.deserialize(routing_table=pickle.loads(routing_table))
        down_routing_table: Dict[Any, Any] = self.deserialize(routing_table=pickle.loads(down_routing_table))
        ''' Prepare the gift '''
        gift_routing_table: Dict[Any, Any]= dict()
        gift_down_routing_table: Dict[Any, Any] = dict()

        guest_active_nodes = set(list(routing_table.keys()))
        guest_down_nodes = set(list(down_routing_table.keys()))

        self_active_nodes = set(list(self.routing_table.keys()))
        self_down_nodes = set(list(self.down_routing_table.keys()))

        '''
        If guest have some down keys which are active in mine, I need to tell guest
        to try to ping over those
        '''
        ask_guest_to_ping: Set[Any] = self_active_nodes & guest_down_nodes
        no_need_to_ask_guest = set()
        need_to_ping: Set[Any] = guest_active_nodes & self_down_nodes
        no_need_to_ping = set()
        '''
        If guest have some active keys which are in my down_keys, 
        I need to ping those
        '''
        for node in ask_guest_to_ping:
            if node in self.routing_table.keys():
                version_number = self.routing_table[node].version_number
                if (version_number < down_routing_table[node].version_number):
                    need_to_ping.add(node)
                    no_need_to_ask_guest.add(node) 
                 
        ask_guest_to_ping = ask_guest_to_ping - no_need_to_ask_guest
        
        for node in need_to_ping:
            version_number = self.down_routing_table[node].version_number
            #* If I have down record later point in time, then the node which 
            #* asked me to ping, then I will ask that node to ping
            if (version_number > routing_table[node].version_number):
                no_need_to_ping.add(node) # If my version number at down is more updated then the one who is asking me to udpate
                ask_guest_to_ping.add(node)

        need_to_ping = need_to_ping - no_need_to_ping
        
        ping_thread = threading.Thread(target=self.ping_thread, args = (need_to_ping, ))
        ping_thread.start()
        '''
        If entry is active in both, and I'm the most updated I will send this
        as gift to the guest in routing table
        '''
        active_in_both: Set[Any] = self_active_nodes & guest_active_nodes
        for node in active_in_both:
            if routing_table[node].version_number < self.routing_table[node].version_number:
                gift_routing_table[node] = self.routing_table[node]
            elif routing_table[node].version_number > self.routing_table[node].version_number:
                self.lock_routing_table.acquire()
                self.routing_table[node] = routing_table[node]
                self.lock_routing_table.release()
        '''
        If entry is down in both then, update your if you have stale, if you
        have much updated then ask guest to udpate
        '''
        down_in_both: Set[Any] = self_down_nodes & guest_down_nodes
        for node in down_in_both:
            if down_routing_table[node].version_number < self.down_routing_table[node].version_number:
                gift_down_routing_table[node] = self.down_routing_table[node]
            elif down_routing_table[node].version_number > self.down_routing_table[node].version_number:
                self.lock_down_routing_table.acquire()
                self.down_routing_table[node] = down_routing_table[node]    
                self.lock_down_routing_table.release()    
        '''
        A fresh entry which I haven't seen before
        '''
        surprise_gift_from_guest = guest_active_nodes - self_active_nodes
        for node in surprise_gift_from_guest:
            if node not in self_down_nodes:
                self.lock_routing_table.acquire()
                self.routing_table[node] = routing_table[node]
                self.lock_routing_table.release()

        surprise_gift_from_guest = guest_down_nodes - self_down_nodes
        for node in surprise_gift_from_guest:
            if node not in self_active_nodes:
                self.lock_down_routing_table.acquire()
                self.down_routing_table[node] = down_routing_table[node]
                self.lock_down_routing_table.release()
        '''
        A fresh entry which guest haven't seen before 
        '''
        surprise_gift_to_guest = self_active_nodes - guest_active_nodes
        for node in surprise_gift_to_guest:
            if node not in guest_down_nodes: 
                gift_routing_table[node] = self.routing_table[node]

        surprise_gift_to_guest = self_down_nodes - guest_down_nodes
        for node in surprise_gift_to_guest:
            if node not in guest_active_nodes:
                gift_down_routing_table[node] = self.down_routing_table[node]
        
            
        ''' wrap the gift'''
        gift_routing_table = pickle.dumps(self.serialize(routing_table=gift_routing_table))
        gift_down_routing_table = pickle.dumps(self.serialize(routing_table=gift_down_routing_table))
        
        logging.debug ("done chit-chat")
        return (gift_routing_table, gift_down_routing_table, list(ask_guest_to_ping))

    '''
    This function will be called by client for getting the appropriate routing
    tables.
    '''
    def exposed_fetch_routing_info(self, key:str, need_serialized=True):
        try:
            logging.debug ("SOME ONE NEED ROUTING TABLES...")
            self_active_nodes = list(self.routing_table.keys())
            self_active_nodes.sort()
            key_hash = str(self.hash_function(key))
            idx: int = bisect(self_active_nodes, key_hash)
            idx = 0 if (idx == len(self_active_nodes)) else idx
            logging.debug (f'Len of self active nodes : {len(self_active_nodes)} and accessing index = {idx}')
            if len(self_active_nodes) > 0:
                controller_node = self_active_nodes[idx]
                replica_nodes = dict()
                n: int = len(self_active_nodes)
                # since it is a ring, we need to do %
                for pos in range(0, min(len(self_active_nodes), self.N)):
                    node_hash = self_active_nodes[(idx + pos) % n]
                    replica_nodes[node_hash] = self.routing_table[node_hash] 

                if need_serialized:
                    replica_nodes: bytes = pickle.dumps(self.serialize(routing_table=replica_nodes))
                logging.debug ("SENDING ROUTING TABLE")
                return replica_nodes, controller_node
        except Exception as e:
            logging.debug (f'Something bad happen during fetching routing table info {e}')

    def print_routing_table(self) -> None:
        logging.debug ("--" *10, "Routing table of ", self.port, "--"* 10)
        logging.debug("--"*10, "Active Routing table", "--" * 10)
        for node, vc in self.routing_table.items():
            logging.debug (f"[{int(vc.start_of_range) % 1000}, {int(node) % 1000}]| url = ({vc.ip}, {vc.port}), version = {vc.version_number} | Load = {vc.load}")
        logging.debug("--"*10, "Down Routing Table", "--" * 10)
        for node, vc in self.down_routing_table.items():
            logging.debug (f"[{int(vc.start_of_range) % 1000} , {int(node) % 1000}]| url = ({vc.ip}, {vc.port}), version = {vc.version_number} | Load = {vc.load}")   
        logging.debug("--"*25)


    '''
    This function is used for the purpose of async replicated put by the replica nodes
    @value = +1/-1 based on increment or decrement operation 
    '''
    def exposed_replicated_put(self, key, value, request_id, timestamp):
        logging.debug (f"Replica are called on {self.ip}, {self.port} for put..{key} = {value}")
        node: str = self.end_of_range
        unique_key: str = f'{key}_{self.port}' # BUG FIX: included port, since we are using common redis list earlier 
        value_to_append: float = value * timestamp # capture both +/- along with timestamp 
        with self.rds.pipeline() as pipe:
            pipe.watch(key)
            pipe.multi()
            while True:
                try:
                    pipe.rpush(unique_key, value_to_append)
                    pipe.execute()
                    break 
                except redis.WatchError as e:
                    logging.debug ("Watch error: ", e)
                    continue
        logging.debug ("Replcation done..")
        return {"status": self.SUCCESS, "request_id": request_id, "node": node, "msg": "Success"}
    
    '''
    This is a thread which will use the state of self.request_logs
    and based on that it will try to replicated (key, value) on self.N replicas
    Each key, value, node has a retry_count which is set to self.REPLICA_RETRY
    after that we stop retrying
    To save lot of rpc calls we are using piggy backing and thus saving lot 
    of unnecessary calls
    '''

    def wait_for_responses(self, responses, required, called_by="") -> Dict[str, int]:
        logging.debug ("Waiting for responses...")
        while True:
            count_success_responses = 0
            count_error_responses = 0
            try:
                for response in responses:
                    if response.ready:
                        res = response.value
                        if res['status'] == self.SUCCESS:
                            count_success_responses += 1 
                        else:
                            count_error_responses += 1
                logging.debug (f'CALLED BY : {called_by} :: success: {count_success_responses}, error = {count_error_responses}')
                if count_success_responses >= required:
                    logging.debug ("Done with waiting for reponses: success")
                    return {"status": self.SUCCESS} 
                if count_error_responses > self.N - required:
                    logging.debug ("Done with waiting for reponses: failure")
                    return {"status": self.FAILURE}

                    # else:
                        # logging.debug ("not ready!", response.ready)
            except Exception as e:
                logging.debug ("Something bad happen ", e)
                
        logging.debug ("Done with waiting for reponses")

    def replicate(self) -> NoReturn:
        while True:
            time.sleep(self.REPLICATED_TIMEOUT)
            logging.debug ("Replicate called")
            piggy_backing = dict() 
            stop_retrying: List[Any] = list() # store all those nodes whose retry count reached zero
            for request_id, replicas in self.requests_log.items():
                key, value, timestamp =  self.requests_log[request_id]['info']
                for node, status in replicas.items():
                    if node == 'info' or node == 'replicated_on':
                        continue
                    if status['retry_count'] <= 0:
                        stop_retrying.append(request_id)
                        continue 
                    if status['status'] == self.FAILURE:
                        self[request_id][node]['retry_count'] -= 1
                        if node not in piggy_backing.keys():
                            piggy_backing[node] = []
                            piggy_backing[node].append({
                                "key": key,
                                "value": value, 
                                "timestamp": timestamp,
                                "request_id": request_id
                            })
                #* Delete those for which we will not retry now.
                for node in stop_retrying:
                    del self[request_id][node]
            '''
            Used to approve success and ignored request so that they 
            can be removed from the self.requests_log
            '''
            def callback(res) -> None:
                # logging.debug (f"Callback called for replicating...{res}")
                success_requests, ignored_requests, node = res 
                
                for request_id in success_requests:
                    self.requests_log[request_id]["replicated_on"] += 1
                    del self.requests_log[request_id][node]
                for request_id in ignored_requests:
                    del self.requests_log[request_id][node]

            '''
            Do a rpyc call to send the piggyback
            '''
            responses: list[Any] = list()
            for node, requests in piggy_backing.items():
                ip, port = self.routing_table[node].ip, self.routing_table[node].port
                conn = rpyc.connect(ip, port)
                async_func = rpyc.async_(conn.root.bulk_put)
                res = async_func(requests)
                res.add_callback(callback)
                res.set_expiry(self.EXPIRE)
                responses.append(res) 

            
            waiting: Dict[str, int] = self.wait_for_responses(responses=responses, required=len(responses), called_by='replicate')
            logging.debug (f'Waiting status: {waiting}')
    '''
    This is used by piggybacks so that put can be handled for mutiple
    key, values which are going to the same node
    '''
    def exposed_bulk_put(self, requests)-> Tuple[List[Any], List[Any], str]:
        # logging.debug (f"Bulk of request arrived: {requests}")
        success_requests, ignored_requests = [], []
        for request in requests:
            result = self.exposed_replicas_put(key=request.key, value=request.value, request_id=request.request_id, timestamp=request.timestamp)
            if result.status == self.SUCCESS:
                success_requests.append(request.request_id)
            elif result.status == self.IGNORE:
                ignored_requests.append(request.request_id)
        return success_requests, ignored_requests, self.end_of_range

    '''
    Below get is made for {key: value} for password like services only

    This method is exposed to client for reads
    - Node will fetch the next N entry from the routing table
    and ask all of them the key: value and timestamp

    '''

    def exposed_get_key(self, key, request_id) -> Dict[str, Any]:
        logging.debug ('--' * 5, "Someone need get info", '--' * 5)
        unique_key: str = f'{key}_{self.port}'
        #!FIXME: add exception hadling please...
        return {
            "state": self.rds.lrange(name=unique_key, start=0, end=-1),
            "request_id": request_id,
            "node": self.end_of_range,
            "status": self.SUCCESS
        }

    def make_request_id(self, key)-> Tuple[str, float]:
        timestamp: float = time.time()
        now = str(timestamp)
        request_id = str(self.hash_function(now + str(key)))
        return request_id, timestamp 

    '''
    Called by client
    This get is only made for primary node, 
    '''
    def exposed_get(self, key, allow_replicas=False):
        logging.debug (f"GET CALLED FOR KEY = {key}")
        request_id, _ = self.make_request_id(key=key)
        start, end = self.start_of_range, self.end_of_range
        replica_nodes, controller_node = self.exposed_fetch_routing_info(key=key, need_serialized=False)
        key_hash = str(self.hash_function(key))
        correct_node: bool = ((start > end and (key_hash >= start or key_hash <= end)) or (start <= key_hash and key_hash < end))
        
        unique_key: str = f'{key}_{self.port}'
        
        if correct_node or allow_replicas:
            logging.debug ("At the right node for READ!....")
            if request_id not in self.get_requests_log:
                self.get_requests_log[request_id] = dict()
            # query from redis
            self_state = self.rds.lrange(name=unique_key, start=0, end=-1) 
            self_state = [float(s) for s in self_state]
            logging.debug (f'Self state in get: {self_state}')

            for s in self_state:
                self.get_requests_log[request_id][s] = 1

            ''' 
            Callback with the async call raised for all the rest nodes
            So that we can have some sort of weak consensus (typically << N / 2)
            '''
            def callback(response) -> None:
                try:
                    res = response.value
                    if (res == None):
                        return
                    replica_state = res['state']
                    logging.debug (f'Replica state = {replica_state}')
                    replica_state = [float(s) for s in replica_state]
                    request_id = res['request_id']
                    for s in replica_state: 
                        if s not in self.get_requests_log[request_id]:
                            self.get_requests_log[request_id][s] = 0
                        '''
                        How many redis instances have seen this s as there entry
                        later we will fetch this value see if this is greater than
                        self.READ, then we will pass this kind of read in 
                        reconcillation step
                        '''
                        self.get_requests_log[request_id][s] += 1
                except Exception as e:
                    logging.debug ("Something bad happen in exposed_get ", e)

            responses: List[Any] = list()
            for node in replica_nodes:
                if node in self.routing_table.keys():
                    try:
                        vc = self.routing_table[node]
                        conn = rpyc.connect(vc.ip, vc.port)
                        async_func = rpyc.async_(conn.root.get_key)
                        res = async_func(key, request_id)
                        res.add_callback(callback)
                        res.set_expiry(self.EXPIRE)
                        responses.append(res)
                    except Exception as e: 
                        logging.debug (f'Fetching response and something bad happen {e}')
            
            logging.debug ("Waiting for get...")
            waiting: Dict[str, int] = self.wait_for_responses(responses=responses, required=self.READ, called_by='GET')
            logging.debug ("Wait done {waiting}..")
            final_state = 0
            try:
                if waiting['status'] == self.SUCCESS: 
                    for element, response in self.get_requests_log[request_id].items():
                        ''' We are only looking for those reponses which are coming from atleast self.r'''
                        logging.debug (f'Element in get: {element}\n Response in get: {response}')
                        if response >= self.READ:
                            ''' 
                                To put all this in simple words, for each or recording operation (+/-)
                                we are looking whether there are at-least self.READ node which have 
                                seen this.
                            '''
                            final_state += 1 if element > 0 else -1
                    return {"status": self.SUCCESS, "value": {final_state}}
                else: 
                    return {"status": self.FAILURE, "msg": "Service unavailable! Retry again"}
            except Exception as e:
                logging.debug(f'Something bad happen during the final part of get {e}')
        else:
            return {'status': self.INVALID_RESOURCE, 'replica_nodes': replica_nodes, 'controller_node': controller_node}

    '''
        Client will pass key, value, version_number
        
        @value can be positive and negative which in case of cart represents
        the cart-in and cart-out operation, we will multiply this with timestamp
        to obtain the timestamp (whose sign will encode the information about the
        cart-in and cart-out). This is just an optimization in order to avoid 
        the storage of two different information (timestamp, cart-in/cart-out)
    '''
    def exposed_put(self, key, value, allow_replicas=False):
        logging.debug (f"PUT REQUEST: key = {key}, value = {value}")
        
        request_id, timestamp = self.make_request_id(key) # generate a unique request id
        key_hash = str(self.hash_function(key)) # to locate the key in the ring
        start, end = self.start_of_range, self.end_of_range 
        replica_nodes, controller_node = self.exposed_fetch_routing_info(key=key, need_serialized=False)
        correct_node: bool = ((start > end and (key_hash >= start or key_hash <= end)) or (start <= key_hash and key_hash < end))
        # Data to be stored unique_key.append(value) : value magically store timestamp with the sign of value
        unique_key: str = f'{key}_{self.port}'
        value_to_append: float = value * timestamp
        if allow_replicas or correct_node:    
            if allow_replicas:
                logging.debug (f'PUT is handeled by replicas node, primary may be down!!!')
            logging.debug ("Writing to REDIS..")
            with self.rds.pipeline() as pipe:
                pipe.watch(key)
                pipe.multi()
                while True:
                    try:
                        pipe.rpush(unique_key, value_to_append)
                        pipe.execute()
                        break 
                    except redis.WatchError as e:
                        logging.debug ("Watch error in redis:", e)
                        continue
            # controller node is not always the first node.(May be I'm a programmer)
            logging.debug ("Done writing to redis")
            if len(self.routing_table) < self.WRITE:
                return {"status": self.FAILURE, "msg": "Not enough replicas to write, Please try later!"}

            '''
            Below is the logic to replicate on the replicas
            callback() is used by async call to write on replicas
            callback() in case receiving success will remove it remove request logs
            and if it recieve ignore (in case replica is more updated for that key)
            then it will simply add 
            '''
            ''' This is a callback function used by async thread. '''
            def callback(response) -> None:
                try:
                    res = response.value
                    request_id = res['request_id']
                    node = res['node']
                    self.requests_log[request_id]["replicated_on"] += 1
                    if (res['status'] == self.SUCCESS) or (res['status'] == self.IGNORE):
                        del self.requests_log[request_id][node]
                except Exception as e:
                    logging.debug ("Something bad happend in put: ", e)    
        
            ''' Add to the requests_logs, so that background thread can run '''
            SEND_RPC = 1

            if request_id not in self.requests_log.keys():
                self.requests_log[request_id] = {"info": (), "replicated_on": 0}
            self.requests_log[request_id]["info"] = (key, value, timestamp)
            self.requests_log[request_id]["replicated_on"] = 0
            for node, vc in replica_nodes.items():
                if node != self.end_of_range:
                    self.requests_log[request_id][node] = {"status": SEND_RPC, "retry_count": self.REPLICA_RETRY}
            '''
            Try to send the async rpyc request to the replica node 
            So that they can have key, value stored.
            '''
            responses = []
            for node, vc in replica_nodes.items():
                if node != self.end_of_range: #* End of range represent node hash
                    try:
                        conn = rpyc.connect(vc.ip, vc.port)
                        async_func = rpyc.async_(conn.root.replicated_put)
                        res = async_func(key, value, request_id, timestamp)
                        res.add_callback(callback)
                        res.set_expiry(self.EXPIRE)
                        responses.append(res)
                    except Exception as e:
                        logging.debug ("Some thing bad happen at put ", e)
                        pass 
            '''
            Now wait for the W to finish the writes and once they are done
            we are free to repsonse to the client for their write
            and our background thread will try to make it to write to N replicas
            '''
            waiting = self.wait_for_responses(responses=responses, required=self.WRITE, called_by='PUT') 

            if waiting['status'] == self.SUCCESS:
                return {"status": self.SUCCESS, 
                        "msg": f"Successfully wrote {key} = {value}", 
                        "version_number": -1} 
            else: 
                return {"status": self.FAILURE, 
                        "msg": "Service unavailable! Retry again"}

        else:
            ''' Return the node which should contain this key, if I'm not the controller
            of that key any more/ or was never. '''
            return {'status': self.INVALID_RESOURCE, 'replica_nodes': replica_nodes, 'controller_node': controller_node}



if __name__ == '__main__':
    port: int = int(sys.argv[1])
    redis_port: int = 6379
    logging.debug (f"Listenting semantic worker at {port}...")
    ThreadedServer(Worker(port=port, redis_port=redis_port), hostname='0.0.0.0', port=port, protocol_config={'allow_public_attrs': True}).start()
    