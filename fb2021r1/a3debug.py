from random import randint

M=1000000007

def solve(W):
    n=len(W)
    ans=[0]*(n+1)
    sufans=[0]*(n+1)
    firstNonFIdx = [None]*(n+1)
    firstNonFVal = [None]*(n+1)
    lastNonFIdx = [None]*(n+1)
    lastNonFVal = [None]*(n+1)
    totalLen=[0]*(n+1)
    flipCount = [0]*(n+1)
    sigma = [0]*(n+1)
    for i,c in enumerate(W):
        if c in 'OX':
            if lastNonFIdx[i]!=None and lastNonFVal[i]!=c:
                dis=totalLen[i]-lastNonFIdx[i]
                sufans[i+1]=sufans[i]+totalLen[i]+1-dis
                ans[i+1]=ans[i]+sufans[i+1]
                firstNonFIdx[i+1]=firstNonFIdx[i]
                firstNonFVal[i+1]=firstNonFVal[i]
                lastNonFIdx[i+1] = totalLen[i]
                lastNonFVal[i+1] = c
                totalLen[i+1]=totalLen[i]+1
                flipCount[i+1]=flipCount[i]+1
                sigma[i+1]=sigma[i]+dis
            else:
                ans[i+1]=ans[i]+sufans[i]
                sufans[i+1]=sufans[i]
                firstNonFIdx[i+1]=firstNonFIdx[i] if firstNonFIdx[i]!=None else totalLen[i]
                firstNonFVal[i+1]=firstNonFVal[i] if firstNonFVal[i]!=None else c
                lastNonFIdx[i+1] = totalLen[i]
                lastNonFVal[i+1] = c
                totalLen[i+1]=totalLen[i]+1
                flipCount[i+1]=flipCount[i]
                sigma[i+1]=sigma[i]
        elif c=='F':
            ans[i+1]=ans[i]+sufans[i]
            sufans[i+1]=sufans[i]
            firstNonFIdx[i+1]=firstNonFIdx[i]
            firstNonFVal[i+1]=firstNonFVal[i]
            lastNonFIdx[i+1]=lastNonFIdx[i]
            lastNonFVal[i+1]=lastNonFVal[i]
            totalLen[i+1]=totalLen[i]+1
            flipCount[i+1]=flipCount[i]
            sigma[i+1]=sigma[i]
        elif c=='.':
            newFlipAcross = firstNonFVal[i]!=lastNonFVal[i]
            extra = (totalLen[i]-firstNonFIdx[i])*(lastNonFIdx[i]+1) if newFlipAcross else 0#12
            ans[i+1]=ans[i]*2+flipCount[i]*(totalLen[i]+1)*totalLen[i]-totalLen[i]*sigma[i]+extra#4+1*3*4+4*2+12
            sufans[i+1]=(sufans[i]*2+totalLen[i]*flipCount[i]+lastNonFIdx[i]+1) if newFlipAcross else (sufans[i]*2+totalLen[i]*flipCount[i])
            firstNonFIdx[i+1]=firstNonFIdx[i]
            firstNonFVal[i+1]=firstNonFVal[i]
            lastNonFIdx[i+1]=(lastNonFIdx[i]+totalLen[i]) if lastNonFIdx[i]!=None else None
            lastNonFVal[i+1]=lastNonFVal[i]
            totalLen[i+1]=totalLen[i]*2
            flipCount[i+1]=(flipCount[i]*2+1) if newFlipAcross else (flipCount[i]*2)
            sigma[i+1]=(sigma[i]*2+firstNonFIdx[i]+totalLen[i]-lastNonFIdx[i]) if newFlipAcross else (sigma[i]*2)
        ans[i+1]%=M
        sufans[i+1]%=M
        if firstNonFIdx[i+1]!=None: firstNonFIdx[i+1]%=M
        if lastNonFIdx[i+1]!=None: lastNonFIdx[i+1]%=M
        totalLen[i+1]%=M
        flipCount[i+1]%=M
        sigma[i+1]%=M
    return ans[n]
tn=int(input())
for ti in range(tn):
    n=int(input())
    W=input()
    ans=solve(W)
    print(f'Case #{ti+1}: {ans}')
