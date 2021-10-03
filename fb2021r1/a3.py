tn=int(input())
M=1000000007
def solve0(W):
    actualStr = ''
    for c in W:
        if c=='.':
            actualStr+=actualStr
        else:
            actual+=c
    return solvea2(actualStr)

def solvea2(W):
    n=len(W)
    ans=0
    lastNonFIdx = None
    for i,c in enumerate(W):
        if c!='F':
            if lastNonFIdx!=None and W[lastNonFIdx]!=c:
                ans+=(n-1-i+1)*(lastNonFIdx+1)
                ans%=M
            lastNonFIdx = i
    return ans

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
                firstNonFIdx[i+1]=firstNonFIdx[i] if firstNonFIdx[i]!=None else i
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
            sufans[i+1]=(sufans[i]+totalLen[i]+totalLen[i]*flipCount[i]) if newFlipAcross else (sufans[i]+totalLen[i]*flipCount[i])
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
        print(f'i={i} ans={ans[i]} sufans={sufans[i]} firstNonFIdx={firstNonFIdx[i]} firstNonFVal={firstNonFVal[i]} lastNonFIdx={lastNonFIdx[i]} lastNonFVal={lastNonFVal[i]} totalLen={totalLen[i]} flipCount={flipCount[i]} sigma={sigma[i]}')
        assert ans[i]==solve0(W[:i])
    return ans[n]
for ti in range(tn):
    W=randStr()
    ans=solve(W)
    solve0()
    # for i in range(n+1):
    print(f'Case #{ti+1}: {ans}')
