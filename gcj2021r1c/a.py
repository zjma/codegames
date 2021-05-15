tn=int(input())
for ti in range(tn):
    n,k=[int(x) for x in input().split()]
    A=[int(x) for x in input().split()]
    A=sorted(list(set(A)))

    G2=[]
    G1=[]
    if A[0]>=2:
        G1.append(A[0]-1)
    for i in range(len(A)-1):
        if A[i]+1<A[i+1]:
            G2.append(A[i+1]-A[i]-1)
    if A[-1]<k:
        G1.append(k-A[-1])

    def take1():
        return max(G1+G2+[0])
    def take2():
        Gx=G1+[(g+1)//2 for g in G2]+[0,0]
        Gx.sort()
        return Gx[-1]+Gx[-2]
    ans0=take1()
    ans1=take2()
    ans=max(ans0,ans1)/k
    print(f'Case #{ti+1}: {ans}')
