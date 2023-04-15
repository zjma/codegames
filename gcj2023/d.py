tn=int(input())
def t(i): return 13*i*(i+1)
for ti in range(tn):
    n = int(input())
    l=0
    r=int(n**0.5)+1
    while l+1<r:
        m=(l+r)//2
        if t(m)>=n:
            r=m
        else:
            l=m
    j = n-26*r*(r-1)//2-1
    ans = chr(65+j//r)
    print(f'Case #{ti+1}: {ans}')
