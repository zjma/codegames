def gcd(x,y):
    if y==0: return x
    return gcd(y,x%y)

def getVec(hole0, hole1):
    x0,y0=hole0
    x1,y1=hole1
    dx,dy=(x1-x0),(y1-y0)
    g=gcd(abs(dx),abs(dy))
    return dx//g,dy//g

def getDist(hole0, hole1):
    x0,y0=hole0
    x1,y1=hole1
    dx,dy=(x1-x0),(y1-y0)
    return dx**2+dy**2

def findNextHit(holes,curHid,vec):
    ansHid=None
    for hid,hole in enumerate(holes):
        if hid==curHid: continue
        if getVec(holes[curHid],hole)==vec:
            if ansHid==None or getDist(holes[curHid],hole)<getDist(holes[curHid],holes[ansHid]):
                ansHid=hid
    return ansHid

def getAns(path): return len(set([s for s,_ in path]))

def visit(holes, wormSetup, path, stop, inworm, vec):
    if (stop,inworm) in path: return getAns(path)
    path.append((stop,inworm))
    ret=0
    if not inworm:
        if stop in wormSetup:
            ret=max(ret,visit(holes, wormSetup, path, wormSetup[stop], True, vec))
        else:
            ret = max(ret, getAns(path))
    else:
        hid=findNextHit(holes,stop,vec)
        if hid==None:
            ret=max(ret, getAns(path))
        else:
            ret=max(ret,visit(holes,wormSetup,path,hid,False,vec))
    path.pop()
    return ret

def AllVecs(holes):
    n=len(holes)
    for i in range(n):
        for j in range(i+1,n):
            yield getVec(holes[i],holes[j])

def AllWormSetup(hids):
    n=len(hids)
    if n==2:
        yield {hids[1]:hids[0],hids[0]:hids[1]}
        yield {}
    elif n>=3:
        for setup in AllWormSetup(hids[:n-1]):
            yield setup
        for i in range(n-1):
            subList=hids[:i]+hids[i+1:n-1]
            for setup in AllWormSetup(subList):
                ret= {**setup,hids[i]:hids[n-1],hids[n-1]:hids[i]}
                yield ret

tn=int(input())
for ti in range(tn):
    n=int(input())
    holes = []
    for i in range(n):
        x,y=[int(x) for x in input().split()]
        holes.append((x,y))
    if n==1:
        ans=1
    else:
        ans=0
        for hid in range(n):
            for vec in AllVecs(holes):
                for setup in AllWormSetup([i for i in range(n)]):
                    ans=max(ans,visit(holes,setup,[],hid,False,vec))
    print(f'Case #{ti+1}: {ans}')
