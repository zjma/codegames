INF=999999999
tn=int(input())
for ti in range(tn):
    n,c=input().split()
    n=int(n)
    c=int(c)
    if c<n-1 or c>n*(n+1)//2-1:
        ans='IMPOSSIBLE'
    else:
        A=[n]
        c-=n-1
        for i in range(n-2,-1,-1):
            maxdiff=n-i
            actualdiff=min(maxdiff-1,c)
            actualcost=actualdiff+1
            c-=actualdiff
            A=A[:actualcost-1][::-1]+[i+1]+A[actualcost-1:]
        ans=' '.join([str(a) for a in A])
    print(f'Case #{ti+1}: {ans}')
