tn=int(input())
def readInts():
    return [int(x) for x in input().split()]
for ti in range(tn):
    n,m,a,b=readInts()
    if a<n+m-1 or b<n+m-1:
        print(f'Case #{ti+1}: Impossible')
    else:
        print(f'Case #{ti+1}: Possible')
        f=[[None for _ in range(m)] for _ in range(n)]
        for i in range(n):
            for j in range(m):
                f[i][j]=(b-(n+m-2)) if i==0 and j==m-1 else (a-(n+m-2)) if i==n-1 and j==m-1 else 1
        for i in range(n):
            print(' '.join([str(v) for v in f[i]]))
