from collections import defaultdict
from math import floor
from functools import cache

@cache
def beau(d,x):
    return x%d==0 and x%(d*d)!=0

@cache
def allBf(n,d):
    ret = []
    for cand in range(1,floor(n**0.5)+1):
        if n%cand==0:
            cand2 = n//cand
            if beau(d,cand):
                ret.append(cand)
            if cand2!=cand and beau(d,cand2):
                ret.append(cand2)
    ret.sort()
    print(f'allBf(n={n},d={d})={ret}')
    return ret

def work(x,d):
    p2c=defaultdict(int)
    for bf in allBf(x,d):
        p2c[bf]+=1
        base=min(p2c.keys())
        while True:
            newp=base*bf
            if newp>x: break
            p2c[newp]+=1
            largerKeys = [key for key in p2c.keys() if key>base]
            if not largerKeys: break
            base=min(largerKeys)
    return p2c[x]

tn=int(input())
for ti in range(tn):
    x,d=[int(x) for x in input().split()]
    ans = work(x,d)
    output = 'YES' if ans>=2 else 'NO'
    print(output)
