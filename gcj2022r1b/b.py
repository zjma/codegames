def work():
    n,p=[int(x) for x in input().split()]
    P=[None]*n

    for i in range(n):
        cur=[int(x) for x in input().split()]
        curmin=min(cur)
        curmax=max(cur)
        dp01new=(min(dp01+abs(premax-curmin),dp10+abs(premin-curmin))+curmax-curmin) if i>=1 else curmax
        dp10new=(min(dp01+abs(premax-curmax),dp10+abs(premin-curmax))+curmax-curmin) if i>=1 else (curmax*2-curmin)
        dp01,dp10=dp01new,dp10new
        premax,premin=curmax,curmin
    return min(dp01,dp10)
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
