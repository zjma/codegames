class UnionFind:
    def __init__(self, n):
        self.parents=[i for i in range(n)]
        self.heights=[0 for i in range(n)]
    def find(self, x):
        if self.parents[x]==x: return x
        result=self.find(self.parents[x])
        self.parents[x]=result
        return result
    def merge(self, x, y):
        rx=self.find(x)
        ry=self.find(y)
        if self.heights[rx]==self.heights[ry]:
            self.parents[rx]=ry
            self.heights[ry]+=1
        elif self.heights[rx]>self.heights[ry]:
            self.parents[ry]=rx
        else:
            self.parents[rx]=ry

TN=int(input())
for TI in range(TN):
    n,m=[int(item) for item in input().split()]
    uf=UnionFind(n)
    for _ in range(m):
        lo,hi=[int(item) for item in input().split()]
        lo-=1
        hi-=1
        while lo<hi:
            uf.merge(lo,hi)
            lo+=1
            hi-=1
    reprToCount={}
    for i in range(n):
        repr=uf.find(i)
        reprToCount[repr]=reprToCount.get(repr,0)+1
    reprs=list(reprToCount.keys())
    rn=len(reprs)
    fg=[[(False,False) for _ in range(n//2+1)] for _ in range(rn+1)]
    #f[a][b]: using the first repr, can we get sum b?
    #g[a][b]: if f[a][b]==True, do we use the a-th repr?
    fg[0][0]=(True,False)
    for i,repr in enumerate(reprs):
        count=reprToCount[repr]
        fg[i+1][0]=(True,False)
        for j in range(count,n//2+1):
            if fg[i][j-count][0]:
                fg[i+1][j]=(True,True)
            elif fg[i][j][0]:
                fg[i+1][j]=(True,False)
            else:
                fg[i+1][j]=(False,None)

    j=max(s for s in range(n//2+1) if fg[rn][s][0])
    i=rn
    assignedReprs=set()
    while i>0:
        if fg[i][j][1]:
            j-=reprToCount[reprs[i-1]]
            assignedReprs.add(reprs[i-1])
        i-=1
    b=[('1' if uf.find(i) in assignedReprs else '0') for i in range(n)]
    ans=''.join(b)
    print(f'Case #{TI+1}: {ans}')
