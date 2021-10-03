from random import randint

def readLineToInts():
    return [int(x) for x in input().split()]
def solve(A):
    segval=[]
    seglen=[]
    for i,a in enumerate(A):
        if i==0 or A[i]!=A[i-1]:
            segval.append(A[i])
            seglen.append(1)
        else:
            seglen[-1]+=1
    segn=len(seglen)
    segnxt=[-1]*segn
    segpre=[-1]*segn
    for si in range(segn-1):
        segnxt[si]=si+1
        segpre[si+1]=si

    cur=0
    presum=0
    ans=[]
    while cur>=0:
        if segval[cur]==1:
            if seglen[cur]%2==1:
                nxt = segnxt[cur]
                if nxt<0: return None
                nxt2 = segnxt[nxt]
                if nxt2<0: return None
                assert segval[nxt]==0
                assert segval[nxt2]==1
                if seglen[nxt]%2==0:
                    for i in range(seglen[nxt]//2):
                        ans.append(presum+seglen[cur]+i*2)
                    seglen[cur]+=seglen[nxt]+seglen[nxt2]
                    seglen[nxt]=0
                    seglen[nxt2]=0
                    nxt3=segnxt[nxt2]
                    segnxt[cur]=nxt3
                    segpre[nxt3]=cur
                else:
                    for i in range(seglen[nxt]//2):
                        ans.append(presum+seglen[cur]+i*2)
                    for i in range((seglen[cur]+seglen[nxt])//2):
                        ans.append(presum+seglen[cur]+seglen[nxt]-1-i*2)
                    segval[cur]=0
                    if seglen[nxt2]==1:
                        segval[nxt2]=0
                    else:
                        seglen[nxt]+=1
                        seglen[nxt2]-=1
                    presum+=seglen[cur]+seglen[nxt]
                    cur=nxt2
            else:
                if segpre[cur]>=0:
                    assert segval[segpre[cur]]==0
                    for i in range(seglen[cur]//2):
                        ans.append(presum+i*2)
                    segval[cur]=0
                    presum+=seglen[cur]
                    cur=segnxt[cur]
                elif segnxt[cur]>=0:
                    assert segval[segnxt[cur]]==0
                    for i in range(seglen[cur]//2):
                        ans.append(presum+seglen[cur]-1-i*2)
                    segval[cur]=0
                    presum+=seglen[cur]
                    cur=segnxt[cur]
                else:
                    return None
        else:
            presum+=seglen[cur]
            cur=segnxt[cur]
    return ans

# def testSolve():
#     for _ in range(999):
#         A=[randint(0,1) for _ in range(8)]
#         actual=solve(A)
#
# testSolve()
# exit(0)

tn=int(input())
for ti in range(tn):
    n=int(input())
    A=readLineToInts()
    ans=solve(A)
    if ans==None:
        print('NO')
    else:
        print('YES')
        print(len(ans))
        if ans:
            print(' '.join([str(x) for x in ans]))
