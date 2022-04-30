def work():
    n,k=[int(x) for x in input().split()]
    E=[int(x) for x in input().split()]
    s0=0
    s1=0
    for i in range(n):
        s1+=E[i]
        for j in range(i+1,n):
            s0+=E[i]*E[j]
    if s1==0:
        if s0!=0: return 'IMPOSSIBLE'
        return '1'
    else:
        if s0%s1==0:
            return -s0//s1
        else:
             return 'IMPOSSIBLE'
             
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
