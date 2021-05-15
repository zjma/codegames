M=1000000007
def F(x):
    if x==0: return 1
    return x*F(x-1)

def C(n,x):
    return F(n)//F(x)//F(n-x)

def work(S,start,length):
    n=len(S)
    if n==0: return 1
    i=n-1
    while i>=0 and S[i]!=1:
        i-=1
    if i<0: return 0
    co=C(n-1,i)
    sub0=work(S[:i])
    sub1=work([x-1 for x in S[i+1:]])
    return sub0*sub1*co%M
tn=int(input())
for ti in range(tn):
    n=int(input())
    S=[int(x) for x in input().split()]
    ans=work(S)
    print(f'Case #{ti+1}: {ans}')
