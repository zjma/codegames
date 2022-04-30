from random import shuffle,randint,choice
def work(F,P):
    n=len(F)
    nxtsOf = {}
    roots = []
    for i in range(n):
        if P[i]>=0:
            nxtsOf.setdefault(P[i], []).append(i)
        else:
            roots.append(i)
    def calc(cur):
        if cur not in nxtsOf:
            return 0,F[cur]
        else:
            curcold = 0
            subhots = []
            for nxt in nxtsOf[cur]:
                subcold,subhot = calc(nxt)
                curcold+=subcold
                subhots.append(subhot)
            subhotmin = min(subhots)
            curhot = max(F[cur],subhotmin)
            curcold+=sum(subhots)-subhotmin
            return curcold,curhot
    ans = 0
    for root in roots:
        curcold,curhot = calc(root)
        ans += curcold+curhot
    return ans

def genP(n):
    ans = [randint(-1,i-1) for i in range(n)]
    return ans

for ti in range(100000):
    n=1000
    F=[randint(1,1000000000) for i in range(n)]
    P=genP(n)
    # print(f'Case #{ti+1}:')
    # print(f'F={F}')
    # print(f'P={P}')
    ans = work(F,P)
    # print(f'ans={ans}')

def main():
    tn=int(input())
    for ti in range(tn):
        n=int(input())
        F=[int(x) for x in input().split()]
        P=[int(x)-1 for x in input().split()]
        ans = work(F,P)
        print(f'Case #{ti+1}: {ans}')
