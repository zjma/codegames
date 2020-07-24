def kill(left, arr, right, x, k, y):
    n=len(arr)
    if n==0: return 0
    strongest=max(arr)
    if left==None and right==None:
        if n<k: return -1
        b=n//k
        r=n%k
        return min(b*x+r*y,x+(n-k)*y)
    borderMax=max([v for v in (left,right) if v!=None])
    if strongest<borderMax:
        b=n//k
        r=n%k
        return min(b*x+r*y,n*y)
    if n<k: return -1
    b=n//k
    r=n%k
    return min(b*x+r*y,x+(n-k)*y)

def solve(initial,target,x,k,y):
    v2pos={v:i for i,v in enumerate(initial)}

    targetIndices=[]
    for v in target:
        if v not in v2pos: return -1
        if targetIndices and v2pos[v]<targetIndices[-1]: return -1
        targetIndices.append(v2pos[v])

    tn=len(targetIndices)
    if tn==0: return kill(None,initial,None,x,k,y)

    ans=kill(None,initial[:targetIndices[0]],initial[targetIndices[0]],x,k,y)
    if ans==-1: return -1
    for i in range(tn-1):
        sub=kill(initial[targetIndices[i]],initial[targetIndices[i]+1:targetIndices[i+1]],initial[targetIndices[i+1]],x,k,y)
        if sub==-1: return -1
        ans+=sub
    sub=kill(initial[targetIndices[tn-1]],initial[targetIndices[tn-1]+1:],None,x,k,y)
    if sub==-1: return -1
    ans+=sub
    return ans

input()
x,k,y=[int(item) for item in input().split()]
initial=[int(item) for item in input().split()]
target=[int(item) for item in input().split()]
ans=solve(initial,target,x,k,y)
print(ans)
