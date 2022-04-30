from random import randint
INF=999999999
def allCands(x):
    if x==1:
        yield [0]
    else:
        for cand in allCands(x-1):
            yield [0]+cand
            yield [1]+cand

def work0(D):
    n=len(D)
    best=(-INF,[])
    for cand in allCands(n):
        cur=0
        prev=-INF
        i=0
        j=n-1
        for op in cand:
            if op==0:
                if D[i]>=prev:
                    cur+=1
                    prev=D[i]
                i+=1
            else:
                if D[j]>=prev:
                    cur+=1
                    prev=D[j]
                j-=1
        best=max(best,(cur,cand))
    print(f'best={best}')
    return best[0]
def work(D):
    n=len(D)
    i=0
    j=n-1
    prev=-INF
    ans=0
    while i<=j:
        if D[j]<prev:
            j-=1
        elif D[i]<prev:
            i+=1
        elif D[i]<D[j]:
            prev=D[i]
            i+=1
            ans+=1
        else:
            prev=D[j]
            j-=1
            ans+=1

    return ans

tn=int(input())
for ti in range(tn):
    n=input()
    D=[int(x) for x in input().split()]
    ans = work(D)
    print(f'Case #{ti+1}: {ans}')
