tn=int(input())
for ti in range(tn):
    C=[None]*3
    M=[None]*3
    Y=[None]*3
    K=[None]*3
    for i in range(3):
        C[i],M[i],Y[i],K[i]=[int(x) for x in input().split()]
    ansCLimit=min(C)
    ansMLimit=min(M)
    ansYLimit=min(Y)
    ansKLimit=min(K)
    possible=ansCLimit+ansMLimit+ansYLimit+ansKLimit>=1000000
    if possible:
        ansC=min(ansCLimit,1000000)
        ansM=min(ansMLimit,1000000-ansC)
        ansY=min(ansYLimit,1000000-ansC-ansM)
        ansK=min(ansKLimit,1000000-ansC-ansM-ansY)
        print(f'Case #{ti+1}: {ansC} {ansM} {ansY} {ansK}')
    else:
        print(f'Case #{ti+1}: IMPOSSIBLE')
