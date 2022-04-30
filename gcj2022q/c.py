from collections import Counter

tn=int(input())
for ti in range(tn):
    n=int(input())
    D=[int(x) for x in input().split()]
    D.sort()
    ctr=Counter([(D[i]-i) for i in range(n)])
    cur=sum(v for k,v in ctr.items() if k>=1)
    ans=0
    for i in range(n):
        ans=max(ans,cur)
        ctr[D[i]-i]-=1
        cur=cur-1+ctr.get(-i,0)
    print(f'Case #{ti+1}: {ans}')
