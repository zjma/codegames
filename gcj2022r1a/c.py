from collections import Counter
from queue import deque

def getCounter(stk,w):
    ctr = Counter(stk)
    return [ctr.get(i,0) for i in range(w)]

def work():
    e,w = [int(x) for x in input().split()]
    demand = [[0 for _ in range(w)] for _ in range(e+1)]
    for i in range(e):
        for ci,x in enumerate(input().split()):
            demand[i][ci] = int(x)
    q = deque()
    visitedSet = {}
    def explore(finishedcount,stk,dis):
        if finishedcount<e and getCounter(stk,w)==demand[finishedcount]:
            finishedcount+=1
        st = (finishedcount,stk)
        if st in visitedSet: return
        visitedSet[st]=dis
        q.append(st)
    explore(0,tuple(),0)
    while q:
        curst = q.popleft()
        curdis = visitedSet[curst]
        finishedcount,curstk = curst
        curctr=getCounter(curstk,w)
        if len(curstk)>=1:
            explore(finishedcount,curstk[:-1], curdis+1)
        for wi in range(w):
            if curctr[wi]<demand[finishedcount][wi]:
                explore(finishedcount,curstk+(wi,), curdis+1)
    termSt = (e,tuple())
    return visitedSet[termSt]
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
