import os 
import copy 
import rpyc 
import time 
import redis
import logging 
import subprocess
import subprocess as sp
 
from hashlib import md5
from bisect import bisect
from pexpect import pxssh
from pprint import pprint
from dotenv import load_dotenv
from os.path import join, dirname
from rpyc.utils.server import ThreadedServer
from typing import List, Set, Dict, Tuple, Callable, Iterator, Union, Optional, Any, Counter

logging.basicConfig(level=logging.DEBUG)

'''
Description of parameters used
    1. nodes_conf: {hostname -> configuration}
    2. ring: [hashi(hostname) -> (hostname, port, who)]
    3. vnode: Virtual node count
    4. hosts: Active host which are used in rings
    5. keys: List of all keys of vnodes present on the ring: maintain sorted so can binarysearch
    6. hash_function: str -> int 
    7. resources : Handle by admin, to add a new resource in the list
'''

class HashRing(rpyc.Service):
    def __init__(self, nodes_conf: List[Dict[str, Any]], spawn_whom:str, **kwargs) -> None:
        self.hash_function:Callable[..., int] = (lambda key: int(md5(string=str(object=key).encode(encoding="utf-8")).hexdigest(), base=16))
        self.ring: Dict[int, Any] = dict()
        self.vnodes: int = 2
        self.hosts: Dict[str, Dict[str, Any]] = dict()
        self.keys = list()
        self.resources: List[Dict[str, Any]] = nodes_conf 
        self.spawn_whom: str = spawn_whom
        ''' Defining constants '''
        self.N = 4
        self.sleep_time = 10
        self.default_vnodes: int = 2
        self.SPAWN_WORKER_PORT = 4001

    def give_hash(self, key: str) -> str:
        return str(object=self.hash_function(key))

    def initialize_worker(self, conf) -> None:        
        mydir: str = os.path.dirname(os.path.realpath(filename=__file__))
        s = pxssh.pxssh()    
        dotevn_path: str = join(dirname(p=__file__), '.env')
        load_dotenv(dotevn_path)
        username, hostname = conf['username'], conf['hostname']
        env_key: str = "_".join([username.upper(), "_".join(hostname.split('.'))])
        logging.debug (env_key)
        password: str | None = os.environ.get(env_key)
        logging.debug (hostname, username, password)
        uri: str = f"{username}@{hostname}"
        s.login(server=hostname, username=username, password=password, sync_multiplier=5, auto_prompt_reset=False)
        s.prompt()
        s.sendline(s=f'mkdir -p Dynamo')
        s.prompt()
        sp.run(args=['scp', 'spawn_worker.py', 'worker.py', f'{uri}:~/Dynamo/']).check_returncode()
        s.sendline(f'redis-cli SHUTDOWN')
        s.prompt()
        s.sendline('nohup redis-server &')
        s.prompt()
        s.sendline(f'redis-cli flushall')
        s.prompt()
        s.sendline('cd Dynamo && python3 spawn_worker.py')
        logging.debug (s.before)
        s.prompt()
        
    def make_setup_ready(self) -> None:
        for conf in self.resources:
            self.initialize_worker(conf=conf)

    '''
    Check the configuration change or existence in the present ring, if even
    a single change we reconfigure the complete ring again
    '''
    def configure_nodes(self, nodes_conf: List[Dict[str, Any]]) -> bool:
        if not isinstance(nodes_conf, List):
            raise ValueError(
                f'nodes_conf configuation must be Dict, got {type(nodes_conf)}'
            )

        conf_changed: bool = False
        for conf in nodes_conf:
            hostname = conf['hostname']
            if hostname not in self.hosts.keys():
                conf_changed = True
            self.hosts[hostname] = conf 
        return conf_changed
   
    '''
    Create ring: This function will add new nodes_conf, if configuration changes
                 or a new node is added
    '''

    def get_neighbours(self, vnode_hash:str) -> Any:
        idx: int = bisect(a=self.keys, x=vnode_hash)
        idx: int = 0 if (idx == len(self.keys)) else idx
        return (idx - 1, idx)

    def create_ring(self, nodes_conf: List[Dict[str, Any]]) -> None:
        go_to_ring = dict()
        for node_conf in nodes_conf:
            hostname = node_conf['hostname']
            port = node_conf['port']
            for who in range(0, int(node_conf["vnodes"])):
                go_to_ring[self.give_hash(f'{hostname}_{who}')] = (hostname, port + who, who)
            
            conn = rpyc.connect(hostname, self.SPAWN_WORKER_PORT)
            conn._config['sync_request_timeout'] = None 
            conn.root.spawn_worker(port=node_conf["port"], vnodes=node_conf["vnodes"], spawn_whom=self.spawn_whom)
        
        time.sleep(self.sleep_time) 

        for vnode_hash, vnode_info in go_to_ring.items():
            # right and left are considered assuming clockwise movement
            # and back of head is always facing center while moving
            hostname, port, who = vnode_info
            left_idx, right_idx = self.get_neighbours(vnode_hash=vnode_hash)
            only_single_node:bool = True
            
            left_node_hash, right_node_hash =  vnode_hash, -1
            if len(self.ring) > 0:
                left_node_hash, right_node_hash = self.keys[left_idx], self.keys[right_idx]
                only_single_node = False 

            new_added = {
                "start_of_range": str(int(left_node_hash) + 1),
                "ip": hostname,
                "port": port,
                "version_number": 0,
                "load": 0,
                "end_of_range": str(vnode_hash) 
            }

            response_to_new_node = {
                            "new_start": str(int(left_node_hash) + 1),
                            "new_end": str(vnode_hash),
                            "new_added": new_added
                        }

            logging.debug ("----"*5)
            logging.debug (f" New: [{int(new_added['start_of_range']) % 10000}, {int(new_added['end_of_range']) % 10000 }, ip:port({new_added['ip']}, {new_added['port']})]")
            self_url:tuple[Any, Any] = (hostname, port)
            try:
                conn = rpyc.connect(*self_url) 
                conn._config['sync_request_timeout'] = None 
                primary, replica_nodes = -1, list()
                if only_single_node == False:
                    primary = self.ring[right_node_hash]
                    for i in range(min(len(self.ring), self.N)):
                        node_idx = (i + right_idx + 1) % (len(self.ring))
                        secondary = self.ring[self.keys[node_idx]]
                        if primary != secondary:
                            replica_nodes.append(secondary)

                conn.root.init_table(routing_info=response_to_new_node, primary=primary, replica_nodes=replica_nodes)
                if only_single_node == False:
                    response_to_right_node:dict[str, Any] = {
                                    "new_start": str(int(vnode_hash) + 1),
                                    "new_end": str(right_node_hash),
                                    "new_added": new_added
                                }
                
                    if response_to_right_node["new_start"] == response_to_new_node["new_start"]:
                        logging.debug ("--------------  They are same ------------------")
                    right_ip, right_port, _ = self.ring[self.keys[right_idx]]
                    logging.debug (f" Already: [{int(response_to_right_node['new_start']) % 1000 }, {int(response_to_right_node['new_end']) % 1000}, ip:port({right_ip}, {right_port})]")
                    logging.debug (self.keys[right_idx])
                    right_url = (right_ip, right_port)
                    conn = rpyc.connect(*right_url) 
                    conn._config['sync_request_timeout'] = None 
                    conn.root.update_table(response_to_right_node)
            except Exception as e:
                logging.debug ("Some thing bad happend in ring ", e)
            self.ring[vnode_hash] = vnode_info #add to ring
            self.keys = sorted(self.ring.keys()) #sort the keys
            logging.debug ("----"*5)
        self.keys = sorted(self.ring.keys())

    '''
    To remove a node from the ring, first remove it from node list, then 
    from the distribution and at last from the ring too
    '''
    def remove_node(self, hostname: str) -> None:
        try:
            node_conf: dict = self.hosts.pop(hostname)
            
        except Exception:
            raise KeyError (
                f'Node: {hostname} not found, available nodes_conf are {self.hosts.keys()}'
            )
        else:
            for who in range(0, node_conf.get("vnodes")):
                del self.ring[(self.give_hash(f'{hostname}_{who}'))]
            self.keys: List[str] = sorted(self.ring.keys())
            self.resources.append(node_conf)

    '''
     Add a new node in the ring
    '''
    def exposed_add_node(self, node_conf:List[Dict[str, Any]]) -> Dict:
        if self.configure_nodes(nodes_conf=node_conf):
            self.create_ring(nodes_conf=node_conf)
        return {"status": 0, "msg": "success"}

    '''
    A generic function to fetch the several property of node configuration
    '''
    def _get(self, key:str, what) -> Any:
        p: int = bisect(self.keys, self.give_hash(key=key)) 
        p = 0 if p == len(self.keys) else p
        hostname, port, who = self.ring[self.keys[p]]
        if what == 'hostname': 
            return hostname
        return self.hosts[hostname][what]
        
    def get_host(self, key:str) -> str:
        return self._get(key=key, what='hostname')

    def exposed_get_all_node_location(self, ip:str, virtual_id:str) -> Any:
        vnode: str = f'{ip}-{virtual_id}'
        return {"status": 0, "msg": "success", "res": self.ring}

    # API for resource grant and revoke
    def exposed_allocate_nodes(self, required_nodes) -> Any:
        if required_nodes > len(self.resources):
            return {"status": -1, "msg": "Not sufficient resources available", "output": len(self.resources)}
        
        node_conf:List[Dict[str, Any]] = []
        for idx in range(0, required_nodes):
            node_conf.append(self.resources[idx])
            
        pprint (f'Asked: {required_nodes}\n Allocated: {node_conf}')
        # add the nodes to the list
        self.exposed_add_node(node_conf)
        for node in node_conf:
            self.resources.remove(node)
        return {"status": 0, "msg": "success"}

    def exposed_remove_nodes(self, remove_count) -> Any:
        # can ask each node there load, and may be the nodes with less load can be reomved
        pass


if __name__ == '__main__':
    types_of_workers:list = ['semantic', 'syntactic']
    worker_type: int = int(input('Which worker you want to initialize ? \n1. Semantic:: Suitable for in-general key-value store\n2. Syntactic::Suitable for username & password\nEnter response(1/2): '))
    logging.debug (worker_type)
    if (worker_type != 1) and (worker_type != 2):
        raise ValueError('Invalid argument provided, please provide 1 or 2')
    spawn_whom:str = types_of_workers[worker_type - 1]
    workers_port:int = 3100 if spawn_whom == 'semantic' else 3000
    logging.debug (f"Workers will be spawn for {spawn_whom}\nWorker port: {workers_port}")
    nodes: List[Dict[str, Any]] = [
        {
            'username': 'sourav',
            'hostname': '10.237.27.95',
            'port': workers_port,
            'vnodes': 6
        },
        {
            'username': 'baadalvm',
            'hostname': '10.17.50.254',
            'port': workers_port,
            'vnodes': 6
        }
    ]
    HashRing_port:int = 3000
    logging.debug (f"Hashring started listening on port {HashRing_port}...")
    ThreadedServer(HashRing(nodes_conf=nodes, spawn_whom=spawn_whom), hostname='0.0.0.0', port=HashRing_port).start()

