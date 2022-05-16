from functools import lru_cache
from collections import defaultdict
from queue import deque
M=1000000007

@lru_cache
def mul(a,b):
    return a*b%M

@lru_cache
def eeuclid(a,b):
    xx,yy,x,y=0,1,1,0
    while b:
        q=a//b
        a,b=b,a%b
        xx,x=x-q*xx,xx
        yy,y=y-q*yy,yy
    return a,x,y

@lru_cache
def inv(x):
    a,k1,k2=eeuclid(x,M)
    return (k1%M)

@lru_cache
def factorial(x):
    if x==0: return 1
    return mul(x,factorial(x-1))

def work(S):
    q=deque()
    childrenof=defaultdict(set)
    for pid,vc in enumerate(S):
        if vc>=len(q)+2 or vc<=0: return 0
        topopcount=len(q)+1-vc
        lastpopped=None
        for _ in range(topopcount):
            lastpopped=q.popleft()
        if q:
            childrenof[q[0]].add(pid)
        if lastpopped!=None:
            childrenof[pid].add(lastpopped)
        if lastpopped!=None and q:
            childrenof[q[0]].remove(lastpopped)
        q.appendleft(pid)
    root=q.pop()
    def explore(cur):
        cn=len(childrenof[cur])
        subcount = [0]*cn
        subans = [0]*cn
        for ci,child in enumerate(childrenof[cur]):
            subcount[ci],subans[ci] = explore(child)
        totchild=sum(subcount)
        ans=factorial(totchild)
        for ci in range(cn):
            ans=mul(ans,subans[ci])
            ans=mul(ans,inv(factorial(subcount[ci])))
        return totchild+1,ans
    totcount,ans=explore(root)
    return ans
tn=int(input())
for ti in range(tn):
    n=int(input())
    S=[int(x) for x in input().split()]
    ans=work(S)
    print(f'Case #{ti+1}: {ans}')
