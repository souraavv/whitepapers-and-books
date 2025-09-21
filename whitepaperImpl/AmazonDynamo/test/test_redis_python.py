import redis
import time

rds = redis.Redis(host='localhost', port=6379, db=0, decode_responses=True)

t = time.time()
t2 = time.time()
print (t)
rds.set('a', t)
rds.set('b', t2)
val = float(rds.get('a'))
val2 = float(rds.get('b'))

print (val, val2)
if val < val2: 
    print ("yes smaller")
print (val, type(val))