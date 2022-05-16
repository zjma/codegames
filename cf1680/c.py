def binsearch(l,r,check):
    while l+1<r:
        m=(l+r)//2
        if check(m):
            r=m
        else:
            l=m
    return l,r

def work():
    s=input()
    sv=[int(c) for c in s]
    totalonecount=sum(sv)
    n=len(s)
    def check(cost):
        start=0
        width=0
        curcount=[0,0]
        while True:
            if curcount[0]<=cost:
                if curcount[1]<totalonecount-cost:
                    if start+width==n: return False
                    newhire=sv[start+width]
                    width+=1
                    curcount[newhire]+=1
                else:
                    return True
            else:
                victim=sv[start]
                start+=1
                width-=1
                curcount[victim]-=1
    l1,r1 = binsearch(-1,n,check)
    return r1

tn=int(input())
for ti in range(tn):
    print(work())
