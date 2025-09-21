import rpyc
import logging
from rpyc.utils.server import ThreadedServer 
from subprocess import call, Popen, run

logging.basicConfig(level=logging.DEBUG)


class SpawnWorkers(rpyc.Service):
    def __init__(self):
        self.REDIS_PORT = 6379
    def exposed_spawn_worker(self, port, vnodes, spawn_whom='syntactic'):
        logging.debug (f'SPAWN WORKER of {spawn_whom}:: Port for {spawn_whom}: {port}, vnodes = {vnodes}')
        if spawn_whom == 'syntactic':
            for i in range(0, vnodes):
                Popen(['python3', 'worker.py', str(port + i)])
        elif spawn_whom == 'semantic':
            for i in range(0, vnodes):
                Popen(['python3', 'worker_semantic.py', str(port + i)])
        return "success"
    
 
if __name__ == "__main__":
    port = 4001
    logging.debug (f'Listening at port 4001...')
    ThreadedServer(SpawnWorkers(), hostname='0.0.0.0', port=port).start()
