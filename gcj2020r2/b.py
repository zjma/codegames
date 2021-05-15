from collections import defaultdict
from queue import deque

class Edge:
    def __init__(self, id, next):
        self.id = id
        self.next = next

class Atem:
    def __init__(self, nodeId, rank):
        self.nodeId = nodeId
        self.rank = rank
    def __repr__(self):
        return f'Atem(node={self.nodeId},rank={self.rank})'
class Btem:
    def __init__(self, nodeId, dist):
        self.nodeId = nodeId
        self.dist = dist
    def __repr__(self):
        return f'Btem(node={self.nodeId},dist={self.dist})'


def merge(v2es, A,B):
    v2distTime={1:0}
    e2ass = {}
    assignedCount=1
    lastDist=0

    def assign(node,dis):
        v2distTime[node]=dis
        for e in v2es[node]:
            if e.next in v2distTime:
                assert e.id not in e2ass
                e2ass[e.id] = max(1,dis-v2distTime[e.next])

    while A or B:
        if A and assignedCount==A[0].rank:
            curAssigned=0
            while A and assignedCount==A[0].rank:
                assign(A[0].nodeId, lastDist+1)
                A.popleft()
                curAssigned+=1
            assignedCount+=curAssigned
            lastDist+=1
        else:
            assign(B[0].nodeId, B[0].dist)
            lastDist=B[0].dist
            assignedCount+=1
            B.popleft()
    return e2ass

def work(ti):
    c,d=[int(x) for x in input().split()]
    X=[int(x) for x in input().split()]
    A,B=[],[]
    for i,x in enumerate(X):
        xv=int(x)
        if xv<0:
            A.append(Atem(i+2,-xv))
        else:
            B.append(Btem(i+2,xv))
    A.sort(key=lambda a:a.rank)
    B.sort(key=lambda a:a.dist)
    A=deque(A)
    B=deque(B)
    v2es=defaultdict(list)
    for di in range(d):
        u,v=[int(x) for x in input().split()]
        v2es[u].append(Edge(di,v))
        v2es[v].append(Edge(di,u))
    e2ass = merge(v2es,A,B)
    ans=' '.join([str(e2ass[i]) for i in range(d)])
    print(f'Case #{ti+1}: {ans}')

tn=int(input())
for ti in range(tn):
    work(ti)
