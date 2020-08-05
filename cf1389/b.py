INF=9999999999
def solve(n,A,k,z):
    f=[[[-INF,-INF] for _ in range(z+1)] for _ in range(2)]
    f[0][0][0]=A[0]
    f[0][0][1]=A[0]
    for x in range(1,k+1):
        for y in range(z+1):
            cur=x-y-y
            if cur<0: continue
            f[x%2][y][0]=max(f[(x-1)%2][y][0],f[(x-1)%2][y][1])+A[cur]
            if y>=1: f[x%2][y][1]=f[(x-1)%2][y-1][0]+A[cur]
    return max(f[k%2][p][q] for p in range(z+1) for q in range(2))

TN=int(input())
for TI in range(TN):
    n,k,z=[int(x) for x in input().split()]
    A=[int(x) for x in input().split()]
    ans=solve(n,A,k,z)
    print(ans)
