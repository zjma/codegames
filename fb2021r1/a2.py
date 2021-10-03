tn=int(input())
M=1000000007
for ti in range(tn):
    n=int(input())
    W=input()
    ans=0
    lastNonFIdx = None
    for i,c in enumerate(W):
        if c!='F':
            if lastNonFIdx!=None and W[lastNonFIdx]!=c:
                ans+=(n-1-i+1)*(lastNonFIdx+1)
                ans%=M
            lastNonFIdx = i
    print(f'Case #{ti+1}: {ans}')
