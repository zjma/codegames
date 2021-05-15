INF=999999999
tn,n,q=[int(w) for w in input().split()]

def query(a,b,c):
    print(f'{a} {b} {c}')
    ans=int(input())
    assert ans in [a,b,c]
    return ans

for ti in range(tn):
    response=query(1,2,3)
    if response==1:
        A=[-INF,2,1,3,INF]
    elif response==2:
        A=[-INF,1,2,3,INF]
    else:
        A=[-INF,1,3,2,INF]
    for i in range(4,n+1):
        lo=0
        hi=len(A)-1
        while lo+1<hi:
            if hi-lo==2:
                if A[hi]==INF:
                    response = query(A[lo],A[lo+1],i)
                    if response==A[lo]:
                        assert False
                    elif response==i:
                        hi=lo+1
                    else:
                        lo=lo+1
                else:
                    response = query(A[hi],A[lo+1],i)
                    if response==A[hi]:
                        assert False
                    elif response==i:
                        lo=lo+1
                    else:
                        hi=lo+1

            else:
                gap0=(hi-lo)//3
                gap2=(hi-lo+1)//3
                b1=lo+gap0
                b2=hi-gap2
                response=query(A[b1],A[b2],i)
                if response==A[b1]:
                    hi=b1
                elif response==A[b2]:
                    lo=b2
                else:
                    lo,hi=b1,b2
        A=A[:hi]+[i]+A[hi:]
    ans=' '.join([str(a) for a in A[1:-1]])
    print(ans)
    verdict=input()
