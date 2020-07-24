import math
def solve(arr, x):
    arr.sort(reverse=True)
    n=len(arr)
    cost=[math.ceil(x/v) for v in arr]
    dp=[0]*(n+1)
    for i in range(1,n+1):
        dp[i]=max(dp[i],dp[i-1])
        if i-cost[i-1]>=0:
            dp[i]=max(dp[i],dp[i-cost[i-1]]+1)
    return dp[n]

tn=int(input())
for ti in range(tn):
    items=input().split()
    n=int(items[0])
    x=int(items[1])
    arr=[int(v) for v in input().split()]
    print(solve(arr,x))
