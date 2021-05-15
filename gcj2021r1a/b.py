def sumOf(fact):
    return sum(k*v for k,v in fact.items())

tn=int(input())
for ti in range(tn):
    m=int(input())
    P=[0]*m
    N=[0]*m
    val2cnt = {}
    for i in range(m):
        P[i],N[i]=[int(x) for x in input().split()]
        val2cnt[P[i]]=N[i]
    s=sum(P[i]*N[i] for i in range(m))

    def factorize(x):
        res = {}
        i=0
        while x>=2 and i<m:
            while x%P[i]==0:
                x//=P[i]
                res[P[i]]=res.get(P[i],0)+1
            if res.get(P[i],0)>N[i]: return None
            i+=1
        if x>=2: return None
        return res

    ans = 0
    for s2 in range(2,29941):
        s1=s-s2
        fact = factorize(s1)
        if fact and sumOf(fact)==s2:
            ans = s1
            break
    print(f'Case #{ti+1}: {ans}')
