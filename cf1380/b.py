def solve(s):
    n=len(s)
    count={}
    count['R']=0
    count['P']=0
    count['S']=0
    for c in s:
        count[c]+=1
    dpr=count['P']-count['R']
    dsr=count['S']-count['R']
    if dpr>=dsr and dsr>=0:
        s1,r1,p1=n,0,0
    elif dpr>=0 and 0>=dsr:
        s1,r1,p1=n,0,0
    elif dsr>=dpr and dpr>=0:
        s1,r1,p1=0,n,0
    elif dsr>=0 and 0>=dpr:
        s1,r1,p1=0,n,0
    else:
        s1,r1,p1=0,0,n
    return 'S'*s1+'R'*r1+'P'*p1

TN=int(input())
for TI in range(TN):
    print(solve(input()))
