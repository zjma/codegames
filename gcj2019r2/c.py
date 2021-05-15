INF=500
tn=int(input())
for ti in range(tn):
    n=int(input())
    C=[None]*n
    J=[None]*n
    for i in range(n):
        C[i],J[i]=[int(x) for x in input().split()]
    lb=[]
    ub=[]
    bad=False
    for i in range(n-1):
        dc=C[i]-C[i+1]
        dj=J[i+1]-J[i]
        if dj==0:
            if dc>0:
                bad=True
        elif dj>0:
            lb.append(dc/dj)
        else:
            ub.append(dc/dj)
    if bad:
        print(f'Case #{ti+1}: IMPOSSIBLE1')
    else:
        u=min(ub) if ub else INF
        l=max(lb) if lb else 0
        x,y=1,1
        while x<=200 and (l>=y/x or y/x>=u):
            if y==200:
                x,y=x+1,1
            else:
                x,y=x,y+1
        if x==201:
            print(f'Case #{ti+1}: IMPOSSIBLE')
        else:
            print(f'Case #{ti+1}: {x} {y}')
