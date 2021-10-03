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
N=0
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
    N+=n
print(N)
