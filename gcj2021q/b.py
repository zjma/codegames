INF=999999999
tn=int(input())
for ti in range(tn):
    x,y,S=input().split()
    x=int(x)
    y=int(y)
    n=len(S)
    fc=[None]*(n+1)
    fj=[None]*(n+1)
    fc[1]=0 if S[0] in 'C?' else INF
    fj[1]=0 if S[0] in 'J?' else INF
    for w in range(2,n+1):
        fc[w]=min(fc[w-1],fj[w-1]+y) if S[w-1] in 'C?' else INF
        fj[w]=min(fj[w-1],fc[w-1]+x) if S[w-1] in 'J?' else INF
    ans=min(fc[n],fj[n])
    print(f'Case #{ti+1}: {ans}')
