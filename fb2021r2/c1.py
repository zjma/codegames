def readLineToInts():
    return [int(x) for x in input().split()]


tn=int(input())
for ti in range(tn):
    rn,cn,k = readLineToInts()
    k-=1
    G=[None]*rn
    for i in range(rn):
        G[i]=input()
    presum = [[0 for _ in range(cn+1)] for _ in range(rn+1)]
    for ri in range(rn):
        for ci in range(cn):
            cur=1 if G[ri][ci]=='X' else 0
            presum[ri+1][ci+1]=presum[ri+1][ci]+presum[ri][ci+1]-presum[ri][ci]+cur
    def subsum(ri,ci,rj,cj):
        ri=max(ri,0)
        ci=max(ci,0)
        rj=min(rj,rn-1)
        cj=min(cj,cn-1)
        return presum[rj+1][cj+1]-presum[rj+1][ci]-presum[ri][cj+1]+presum[ri][ci]
    def hasX(k,ci,diff):#diff=-1: upmove
        if diff==0:
            return G[k][ci]=='X'
        elif diff<=0:
            if subsum(0,ci,k-diff-1,ci)<=k:
                if 0<=k-diff<rn:
                    ret = G[k-diff][ci]=='X'
                else:
                    ret = False
            else:
                ret = True
        else:
            if subsum(k-diff+1,ci,rn-1,ci)<=rn-k-1:
                if 0<=k-diff<rn:
                    ret = G[k-diff][ci]=='X'
                else:
                    ret = False
            else:
                ret = True
        return ret
    def getCost(diff):
        ret = len([ci for ci in range(cn) if hasX(k,ci,diff)])
        return ret
    mindiff=k-rn
    maxdiff=k+1
    ans=min(getCost(diff)+abs(diff) for diff in range(mindiff,maxdiff+1))
    print(f'Case #{ti+1}: {ans}')
