from __future__ import division
import array
import difflib
import hashlib
import numpy
import random
import string

# N = A modulo clock with numbers 0 to 2^m - 1
# n = node
# m = # of bits in key/node identifiers
# k = a key

m = 160
number_of_nodes = 125
N = []

for i in range(number_of_nodes):
    N.append(hashlib.sha1(str(random.getrandbits(number_of_nodes))).hexdigest())

N.sort()

def successor (N,k):
    if (k >= N[0]) & (k < N[-1]):
        return N[next(i for i, v in enumerate(N) if v > k)]
    elif (k < N[0]) | (k >= N[-1]):
        return N[0]
    
def predecessor (N,k):
    if (k > N[0]) & (k <= N[-1]):
        return N[next(i for i, v in enumerate(N) if v > k) - 2]
    elif (k <= N[0]) | (k > N[-1]):
        return N[-1]

def finger_table (N,n,m):
    results = []
    for i in range(m):
        #print i,":",(format(((int(n,16)+(2**i)) % (2**m)),'x').zfill(40))
        results.append(successor(N,(format(((int(n,16)+(2**i)) % (2**m)),'x').zfill(40))))
    return sorted(list(set(results)))

def route (N,n1,k,m):
    routing_table = finger_table(N,n1,m)
    if n1 == k:
        return 0
    elif k in routing_table:
        return 1
    else:
        n2 = predecessor(routing_table,k)
        return 1 + route(N,n2,k,m)

def route_world (N,n,m):
    Total_hops = 0
    for i in range(len(N)):
        Total_hops = Total_hops + route(N,n,N[i],m)
    return Total_hops / (len(N))


