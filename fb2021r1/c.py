from pprint import pprint

M = 1000000007

def mod(x): return x%M

def readInts():
    return [int(x) for x in input().split()]

class RectOracle:
    def __init__(self, rect):
        self.rn = len(rect)
        self.cn = 20
        self.presum = [[0 for _ in range(self.cn+1)] for _ in range(self.rn+1)]
        self.presum2 = [[0 for _ in range(self.cn+1)] for _ in range(self.rn+1)]
        for ri in range(self.rn):
            assert len(rect[ri])==self.cn
            for ci in range(self.cn):
                self.presum[ri+1][ci+1]=self.presum[ri][ci+1]+self.presum[ri+1][ci]-self.presum[ri][ci]+rect[ri][ci]
                self.presum2[ri+1][ci+1]=self.presum2[ri][ci+1]+self.presum2[ri+1][ci]-self.presum2[ri][ci]+rect[ri][ci]*(ci+1)

    def getAreaSum(self, ri0,ci0,ri1,ci1):
        if ri0>ri1 or ci0>ci1: return 0
        return self.presum[ri1+1][ci1+1]-self.presum[ri0][ci1+1]-self.presum[ri1+1][ci0]+self.presum[ri0][ci0]
    def getAreaSum2(self,ri0,ci0,ri1,ci1):
        if ri0>ri1 or ci0>ci1: return 0
        return self.presum2[ri1+1][ci1+1]-self.presum2[ri0][ci1+1]-self.presum2[ri1+1][ci0]+self.presum2[ri0][ci0]

def vecCap(vec, cap):
    ans = list(vec)
    for i in range(19,cap,-1):
        ans[i-1]+=ans[i]
        ans[i]=0
    return ans
def vecAdd(vec0,vec1): return [(vec0[i]+vec1[i]) for i in range(20)]
def vecSub(vec0, vec1): return [(vec0[i]-vec1[i]) for i in range(20)]
def newVec(i=None):
    ans = [0]*20
    if i!=None: ans[i]=1
    return ans

tn=int(input())
for ti in range(tn):
    n=int(input())
    cap = [0]*(n-1)
    mapNodeToNexts = [[] for _ in range(n)]
    for i in range(n-1):
        a,b,c=readInts()
        a-=1
        b-=1
        cap[i]=c
        mapNodeToNexts[a].append((i,b))
        mapNodeToNexts[b].append((i,a))

    mapNodeToChildren = [[] for _ in range(n)]
    def explore0(node,parent):
        for ei,child in mapNodeToNexts[node]:
            if child==parent: continue
            mapNodeToChildren[node].append((ei,child))
            explore0(child,node)
    explore0(0,-1)

    loadVec = [newVec() for _ in range(n)]
    sans = [None]*n
    node2vecs = [[] for _ in range(n)]
    def explore(node):
        subAns = []
        for ci,(ei,child) in enumerate(mapNodeToChildren[node]):
            explore(child)
            subVec = vecAdd(vecCap(loadVec[child],cap[ei]-1),newVec(cap[ei]-1))
            loadVec[node] = vecAdd(loadVec[node],subVec)
            node2vecs[node].append(subVec)
        T=node2vecs[node]
        rn=len(T)
        ro = RectOracle(T)
        acrossTotal=0
        for load in range(1,21):
            for ri in range(rn):
                toRoot = load*T[ri][load-1]
                toPeer = load*T[ri][load-1]*ro.getAreaSum(ri+1,load-1,rn-1,load-1)
                toRest = load*T[ri][load-1]*(ro.getAreaSum(0,load,rn-1,19)-ro.getAreaSum(ri,load,ri,19))
                acrossTotal=mod(acrossTotal+toRoot+toPeer+toRest)

        sans[node]=sum(sans[child] for _,child in mapNodeToChildren[node])+acrossTotal

    explore(0)

    S = [None]*(n-1)
    def explore2(node,pei,parentLoadVec,parentSans):
        subAnsSum = sum(sans[child] for ei,child in mapNodeToChildren[node])
        if pei>=0:
            tmpVec = vecAdd(vecCap(parentLoadVec,cap[pei]-1),newVec(cap[pei]-1))
            node2vecs[node].append(tmpVec)
            loadVec[node] = vecAdd(loadVec[node],tmpVec)
            subAnsSum=mod(subAnsSum+parentSans)

        T=node2vecs[node]
        ro = RectOracle(T)
        rn=len(T)
        cn=len(T[0])
        acrossTotal = 0
        for ri in range(rn):
            for ci in range(cn):
                cur = (ci+1)*T[ri][ci]*(1+ro.getAreaSum(ri+1,ci,rn-1,ci)+ro.getAreaSum(0,ci+1,rn-1,cn-1)-ro.getAreaSum(ri,ci+1,ri,cn-1))
                acrossTotal=mod(acrossTotal+cur)

        acrossCur=[0]*rn
        for chdIdx,(ei,child) in enumerate(mapNodeToChildren[node]):
            for load in range(1,21):
                cur = load*T[chdIdx][load-1]*(1+ro.getAreaSum(0,load-1,rn-1,cn-1)-ro.getAreaSum(chdIdx,load-1,chdIdx,cn-1))+T[chdIdx][load-1]*(ro.getAreaSum2(0,0,rn-1,load-2)-ro.getAreaSum2(chdIdx,0,chdIdx,load-2))
                acrossCur[chdIdx]=mod(acrossCur[chdIdx]+cur)
            S[ei]=mod(subAnsSum+acrossTotal-acrossCur[chdIdx])

        for chdIdx,(ei,child) in enumerate(mapNodeToChildren[node]):
            tempVec = vecSub(loadVec[node],T[chdIdx])
            newParentAns = mod(subAnsSum-sans[child]+acrossTotal-acrossCur[chdIdx])
            explore2(child,ei,tempVec,newParentAns)

    explore2(0,-1,newVec(),0)

    ans=1
    for s in S:
        ans=(ans*s)%M
    print(f'Case #{ti+1}: {ans}')
