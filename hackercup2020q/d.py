from queue import deque
INF=999999999999999999
def solve(n,m,C):
    F=[INF for _ in range(n-1)]
    F[0]=0
    history=deque()
    history.append((F[0],0))
    for i in range(1,n-1):
        while history and history[0][1]+m<i: history.popleft()
        if C[i]>0 and history:
            F[i]=history[0][0]+C[i]
            while history and history[-1]>=(F[i],i): history.pop()
            history.append((F[i],i))
    ans=INF
    for i in range(max(0,n-1-m),n-1):
        ans=min(ans,F[i])
    if ans>=INF: ans=-1
    return ans

TN=int(input())
for TI in range(TN):
    n,m=[int(item) for item in input().split()]
    C=[0]*n
    for i in range(n):
        C[i]=int(input())
    ans=solve(n,m,C)
    print(f'Case #{TI+1}: {ans}')
