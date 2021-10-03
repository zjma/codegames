def readIntegerLine():
    return [int(item) for item in input().split()]

tn=int(input())
INF=999999999999999999
for ti in range(tn):
    n,k=readIntegerLine()
    G=readIntegerLine()
    assert len(G)==n
    nexts={}
    for _ in range(n-1):
        u,v=readIntegerLine()
        nexts.setdefault(u-1,[]).append(v-1)
        nexts.setdefault(v-1,[]).append(u-1)
    f=[[[-INF for _ in range(3)] for _ in range(k+1)] for _ in range(n)]
    visited=set()
    def explore(cur):
        visited.add(cur)
        children = []
        for nxt in nexts.get(cur,[]):
            if nxt in visited: continue
            children.append(nxt)
            explore(nxt)
        chdCount=len(children)
        #dp[a][b][c] first a children, use b extra edges, the number of J children is c (mod 2), max?
        dp=[[[-INF for _ in range(4)] for _ in range(k+1)] for _ in range(chdCount+1)]
        dp[0][0][3]=0
        for a in range(1,chdCount+1):
            child=children[a-1]
            for b in range(k+1):
                dp[a][b][3]=dp[a-1][b][3]

                cands=[dp[a-1][b][0],]
                for b2 in range(b+1):
                    cands.append(dp[a-1][b-b2][3]+max(f[child][b2][0],f[child][b2][2]))
                for b2 in range(b):
                    cands.append(dp[a-1][b-1-b2][0]+max(f[child][b2][0],f[child][b2][2]))
                dp[a][b][0]=max(cands)

                cands = [dp[a-1][b][1],]
                for b2 in range(b+1):
                    cands.append(dp[a-1][b-b2][3]+f[child][b2][1])
                for b2 in range(b):
                    cands.append(dp[a-1][b-1-b2][0]+f[child][b2][1])
                    cands.append(dp[a-1][b-1-b2][2]+f[child][b2][1])
                for b2 in range(b):
                    cands.append(dp[a-1][b-b2-1][1]+max(f[child][b2][0],f[child][b2][2]))
                dp[a][b][1]=max(cands)

                cands=[dp[a-1][b][2],]
                for b2 in range(b+1):
                    cands.append(dp[a-1][b-b2][1]+f[child][b2][1])
                for b2 in range(b):
                    cands.append(dp[a-1][b-b2-1][2]+max(f[child][b2][0],f[child][b2][2]))
                dp[a][b][2]=max(cands)
        if chdCount==0:
            f[cur][0][1]=G[cur]
            f[cur][0][2]=G[cur]
            return
        for x in range(k+1):
            f[cur][x][0]=dp[chdCount][x][0]
            f[cur][x][1]=dp[chdCount][x][1]+G[cur]
            f[cur][x][2]=dp[chdCount][x][2]+G[cur]
    explore(0)
    cands=[G[0],]
    for kk in range(1,k+1):
        cands.append(f[0][kk-1][1])
        cands.append(f[0][kk-1][2])
        if kk>=2: cands.append(f[0][kk-2][0])
    ans=max(cands)
    print(f'Case #{ti+1}: {ans}')
