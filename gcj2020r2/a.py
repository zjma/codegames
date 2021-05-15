def binSearch(lo,hi,check):
    while lo+1<hi:
        m=(lo+hi)//2
        if check(m):
            hi=m
        else:
            lo=m
    return lo,hi
def seqsum(x):
    return (x+1)*x//2
def getNextStackIdx(l,r):
    return 0 if l>=r else 1

def sum2(start, steps):
    return (start+start+(steps-1)*2)*steps//2

tn=int(input())
for ti in range(tn):
    S=[int(x) for x in input().split()]
    def willStackIdxChangeAfterMSteps(m):
        SS=list(S)
        si0 = getNextStackIdx(SS[0],SS[1])
        SS[si0]-=seqsum(m)
        si1 = getNextStackIdx(SS[0],SS[1])
        return si0!=si1
    lo,hi=binSearch(0,abs(S[0]-S[1])+1,willStackIdxChangeAfterMSteps)
    si0=getNextStackIdx(S[0],S[1])
    if seqsum(hi)>S[si0]:
        S[si0]-=seqsum(lo)
        print(f'Case #{ti+1}: {lo} {S[0]} {S[1]}')
    else:
        S[si0]-=seqsum(hi)
        def willSeeNegAfterXSteps(x):
            SS=list(S)
            SS[1-si0]-=sum2(hi+1,(x+1)//2)
            SS[si0]-=sum2(hi+2,x//2)
            return SS[0]<0 or SS[1]<0
        lo2,hi2 = binSearch(0,max(S),willSeeNegAfterXSteps)
        S[1-si0]-=sum2(hi+1,(lo2+1)//2)
        S[si0]-=sum2(hi+2,lo2//2)
        print(f'Case #{ti+1}: {hi+lo2} {S[0]} {S[1]}')
