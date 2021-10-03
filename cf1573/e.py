def readLineToInts():
    return [int(x) for x in input().split()]
tn=int(input())

def solve(A):
    cands = set()
    ans=0
    for a in A:
        if not A:
            cands.add(a)
        elif a not in cands:
            cands.add(a)
            ans+=1
        else:
            cands=set([a])
    return ans
for ti in range(tn):
    n=int(input())
    A=readLineToInts()
    print(solve(A))
