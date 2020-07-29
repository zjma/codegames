def max2(arr):
    if arr:
        return max(arr)
    return 0,0
class Oracle:
    def __init__(self,finalized=False):
        self.kv={}
        self.keyToBestAfterIgnored={}
        self.overallBest=0
        self.overallBestKey=None
        self.secondBest=0
        self.finalized=finalized
    def getWithIgnore(self, keyToIgnore):
        assert self.finalized
        return self.secondBest if keyToIgnore==self.overallBestKey else self.overallBest
    def addCandidate(self, key, value):
        self.kv[key]=value
    def finalize(self):
        vks=[(v,k) for k,v in self.kv.items()]
        self.overallBest,self.overallBestKey=max2(vks)
        self.secondBest,_=max2([x for x in vks if x!=(self.overallBest,self.overallBestKey)])
        self.finalized=True
def solve(n,P,H):
    segs=[]
    for i in range(n):
        segs.append((P[i]-H[i],P[i],-i-1))
        segs.append((P[i],P[i]+H[i],i+1))
    segs.sort(key=lambda seg:seg[1])
    dp={}
    segn=len(segs)
    for i,seg in enumerate(segs):
        lo,hi,label=seg
        length=dp.setdefault(lo,Oracle(True)).getWithIgnore(-label)
        dp.setdefault(hi,Oracle()).addCandidate(label,length+hi-lo)
        if i==segn-1 or segs[i+1][1]!=hi:
            dp[hi].finalize()
    return max(o.getWithIgnore(None) for o in dp.values())
TN=int(input())
for TI in range(TN):
    n=int(input())
    P=[0]*n
    H=[0]*n
    for i in range(n):
        P[i],H[i]=[int(item) for item in input().split()]
    ans=solve(n,P,H)
    print(f'Case #{TI+1}: {ans}')
