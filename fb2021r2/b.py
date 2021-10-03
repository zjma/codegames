

def readLineToInts():
    return [int(x) for x in input().split()]

def explore(node, parentFreqs):
    ans = myBreakableEdgeCount+
    return ans

tn=int(input())
for ti in range(tn):
    n=int(input())
    v2adj2 = {}
    for _ in range(n-1):
        a,b=readLineToInts()
        a-=1
        b-=1
        v2adjs.setdefault(a,[]).append(b)
    freq = readLineToInts()
    f2vs = {}
    for idx,f in enumerate(freq):
        f2vs.setdefault(f,[]).append(idx)
    history = []
    explore(0)
    ans=n-1-len(disabledEdgeSet)
    print(f'Case #{ti+1}: {ans}')
