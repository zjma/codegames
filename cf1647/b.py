from collections import Counter
tn=int(input())
for ti in range(tn):
    n,m=[int(item) for item in input().split()]
    g=[None]*n
    for i in range(n):
        g[i]=input()
    ans='YES'
    for i in range(n-1):
        for j in  range(m-1):
            chars = [g[i][j],g[i+1][j],g[i][j+1],g[i+1][j+1]]
            c=Counter(chars)
            if c.get('1')==3:
                ans='NO'
    print(ans)
