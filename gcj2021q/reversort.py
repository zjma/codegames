tn=int(input())
for ti in range(tn):
    n=int(input())
    A=[int(w) for w in input().split()]
    ans=0
    for _ in range(n-1):
        A2=[(v,i) for i,v in enumerate(A)]
        minVal,minIdx = min(A2)
        ans+=minIdx+1
        A=A[:minIdx][::-1]+A[minIdx+1:]
    print(f'Case #{ti+1}: {ans}')
