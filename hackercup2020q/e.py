INF=999999999999999999
def getBackbone(rootless,src,dst) -> list:
    def findPathFromSrc(root,parent):
        if root==None: None
        if root==src: return [root]
        for nxt in rootless.setdefault(root,[]):
            if nxt==parent: continue
            sub=findPathFromSrc(nxt,root)
            if sub: return sub+[root]
        return None
    return findPathFromSrc(dst,None)

class SegTree:
    def __init__(self, slb, srb):
        self.slb=slb
        self.srb=srb
        self.value=[INF]*(srb-slb+1)
    def getmin(self, qlb, qrb):
        if qlb>self.srb or qrb<self.slb or qlb>qrb: return INF
        qlb=max(self.slb,qlb)
        qrb=min(self.srb,qrb)
        return min(self.value[qlb-self.slb:qrb-self.slb+1])
    def update(self, pos, val):
        self.value[pos-self.slb]=min(self.value[pos-self.slb],val)

def solve(volume,rootless,C,src,dst) -> int:
    bbNodes=getBackbone(rootless,src,dst)
    f=[INF]*len(C)
    f[src]=0
    segtree=SegTree(1,len(bbNodes)-1)
    segtree.update(len(bbNodes)-1,0)
    def calc(nodeToChildren,node,nodeDepth,bbDepth):
        if C[node]>0:
            f[node]=segtree.getmin(bbDepth+1,bbDepth+volume-nodeDepth+bbDepth)+C[node]
        for nxt in nodeToChildren.get(node,[]):
            calc(nodeToChildren,nxt,nodeDepth+1,bbDepth)
    def update(nodeToChildren,node,nodeDepth):
        if C[node]>0:
            segtree.update(nodeDepth,f[node])
        for nxt in nodeToChildren.get(node,[]):
            update(nodeToChildren,nxt,nodeDepth+1)
    def getBbNodeTree(node,prevBbNode,nextBbNode,parent):
        result={}
        def dfs(node,parent):
            nonlocal result
            if node==None: return
            for nxt in rootless.setdefault(node,[]):
                if nxt in (prevBbNode,nextBbNode,parent): continue
                result.setdefault(node,[]).append(nxt)
                dfs(nxt,node)
        dfs(node,None)
        return result
    for i in range(1,len(bbNodes)-1):
        curDepth=len(bbNodes)-1-i
        nodeToChildren=getBbNodeTree(bbNodes[i],bbNodes[i-1],bbNodes[i+1],None)
        calc(nodeToChildren,bbNodes[i],curDepth,curDepth)
        update(nodeToChildren,bbNodes[i],curDepth)
    ans=segtree.getmin(1,volume)
    if ans>=INF: ans=-1
    return ans

TN=int(input())
for TI in range(TN):
    n,m,a,b=[int(item) for item in input().split()]
    rootless={}
    C=[0]*n
    for i in range(n):
        p,C[i]=[int(x) for x in input().split()]
        p-=1
        if p>=0:
            rootless.setdefault(i,[]).append(p)
            rootless.setdefault(p,[]).append(i)
    ans=solve(m,rootless,C,a-1,b-1)
    print(f'Case #{TI+1}: {ans}')
