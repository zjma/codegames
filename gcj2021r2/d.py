tn=int(input())
for ti in range(tn):
    r,c,f,s=[int(x) for x in input().split()]
    src=[None]*r
    dst=[None]*r
    for i in range(r):
        src[i]=input()
    for i in range(r):
        dst[i]=input()
    map=[[None for j in range(c)] for i in range(r)]
    val=[[None for j in range(c)] for i in range(r)]
    nodes=[]
    for i in range(r):
        for j in range(c):
            if src[i][j]=='M' and dst[i][j]=='G':
                nodes.append((i,j))
                map[i][j]=len(nodes)-1
                val[i][j]=0
            elif src[i][j]=='G' and dst[i][j]=='M':
                nodes.append((i,j))
                map[i][j]=len(nodes)-1
                val[i][j]=1
    def validonestep(x,y):
        if x>=1: yield (x-1,y)
        if x<r-1: yield (x+1,y)
        if y>0: yield (x,y-1)
        if y<c-1: yield (x,y+1)
    def dfs(nid,visited,prev):
        x0,y0=nodes[nid]
        for x1,y1 in validonestep(x0,y0):
            nid1=map[x1][y1]
            if nid1==None or val[x0][y0]==val[x1][y1]: continue
            if not nid1 in visited:
                visited.add(nid1)
                if prev.get(nid1,None)==None or dfs(prev[nid1],visited,prev):
                    prev[nid1]=nid
                    return True
        return False
    prevOf={}
    match=0
    for nid,node in enumerate(nodes):
        if dfs(nid,set(),prevOf):
            match+=1
    ans=len(nodes)-match//2
    print(f'Case #{ti+1}: {ans}')
