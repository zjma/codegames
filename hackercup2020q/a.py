TN=int(input())
def solve(n,I,O):
    ans=[['Y' for _ in range(n)] for _ in range(n)]
    for hops in range(n):
        for i in range(n-hops):
            j=i+hops
            ans[i][j]='Y' if i==j or ans[i][j-1]=='Y' and O[j-1]=='Y' and I[j]=='Y' else 'N'
    for hops in range(n):
        for i in range(n-1,hops-1,-1):
            j=i-hops
            ans[i][j]='Y' if i==j or ans[i][j+1]=='Y' and O[j+1]=='Y' and I[j]=='Y' else 'N'
    return ans
for TI in range(TN):
    n=int(input())
    I=input()
    O=input()
    ans=solve(n,I,O)
    print(f'Case #{TI+1}:')
    for i in range(n):
        print(''.join(ans[i]))
