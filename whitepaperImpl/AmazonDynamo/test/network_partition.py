import logging 
import subprocess

logging.basicConfig(level=logging.DEBUG)

def block_traffic(ip_address, port_set) -> None:
    logging.debug (f'Network partition is called for ip: {ip_address} and ports= {port_set}')
    for port in port_set:
        isolate_command: str = \
        f'''sudo iptables -I INPUT 1 -s {ip_address} -p tcp --dport {port} -j DROP; 
        sudo iptables -I OUTPUT 1 -d {ip_address} -p tcp --dport {port} -j DROP;'''
        subprocess.run(args=[isolate_command], shell=True) # Update with password
    logging.debug ("Network is partitioned...")

def heal_firewall(ip_address, port_set) -> None:
    logging.debug (f'Network heal is called for ip: {ip_address} and ports= {port_set}')
    for port in port_set:
        heal_command: str = \
        f'''sudo iptables -D INPUT -s {ip_address} -p tcp --dport {port} -j DROP; 
        sudo iptables -D OUTPUT -d {ip_address} -p tcp --dport {port} -j DROP;'''
        
        subprocess.run(args=[heal_command], shell=True) # Update with password
    logging.debug("The network partition is healed")


if __name__ == '__main__':
    logging.debug (f'1. Network partition')
    logging.debug (f'2. Heal partition')
    which = int(input('Which option ? '))
    which_node = int(input('which nodes cluster (sourav(1), baadalvm(2)) ? '))
    which_task = int(input('Which task Semantic(1) and Syntactic(2) ? '))
    ip = '10.237.27.95' if which_node == 1 else '10.17.50.254'
    semantic_vnodes = [3100, 3104, 3105]
    syntactic_vnodes = [3000, 3004, 3005]
    vnodes = semantic_vnodes if which_task == 1 else syntactic_vnodes
    if which == 1:
        block_traffic(ip_address=ip, port_set=vnodes)
    elif which == 2:
        heal_firewall(ip_address=ip, port_set=vnodes)