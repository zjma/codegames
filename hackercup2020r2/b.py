def solve(n,p):
    f={}
    f[(1,0)]=0
    for m in range(2,n+1):
        for r in range(m):
            meVsWorse=0 if r==0 else (r*(1-p+p*(1+f[(m-1,r-1)])))
            meVsBetter=0 if r==(m-1) else ((m-r-1)*(p+(1-p)*(1+f[(m-1,r)])))
            worseVsWorse=0 if r==0 else (r*(r-1)/2*(1+f[(m-1,r-1)]))
            betterVsBetter=0 if r==(m-1) else ((m-r-1)*(m-r-2)/2*(1+f[(m-1,r)]))
            worseVsBetter=0 if r in (0,m-1) else (r*(m-r-1)*((1-p)*(1+f[(m-1,r)])+p*(1+f[(m-1,r-1)])))
            f[(m,r)]=(meVsWorse+meVsBetter+worseVsWorse+betterVsBetter+worseVsBetter)*2/(m*(m-1))
    return [f[(n,i)] for i in range(n)]
tn=int(input())
for ti in range(tn):
    items=input().split()
    n=int(items[0])
    p=float(items[1])
    ans=solve(n,p)
    print(f'Case #{ti+1}:')
    for i in range(n):
        print(ans[i])
