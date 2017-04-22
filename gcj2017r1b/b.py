def valid(s):
    if s[0]==s[-1]: return False
    return True

def build(r,y,b):
    n=r+y+b
    if r*2>n or y*2>n or b*2>n: return None
    if y*2==n:
        s1='Y'*y
        s2='R'*r+'B'*b
        l=n//2
        ret=""
        for i in range(l):
            ret+=s2[i]+s1[i]
        return ret
    if n%2==0:
        l=n//2
        y1=l-r
        y2=y-y1
        s1='R'*r+'Y'*y1
        s2='Y'*y2+'B'*b
        ret1=""
        for i in range(l):
            ret1+=s2[i]+s1[i]
        ret2=""
        for i in range(l):
            ret2+=s1[i]+s2[i]
        if valid(ret1): return ret1
        return ret2
    else:
        l=n//2
        y1=l-r
        y2=y-y1
        s1='R'*r+'Y'*y1
        s2='Y'*y2+'B'*b
        ret=""
        for i in range(l):
            ret+=s2[i]+s1[i]
        ret+=s2[l]
        return ret
def solve(r,y,b,ry,yb,rb):
    if ry>b or yb>r or rb>y: return "IMPOSSIBLE"
    if b>0 and ry==b:
        if r>0 or y>0 or yb>0 or rb>0: return "IMPOSSIBLE"
        return "OB"*b
    if yb==r and r>0:
        if y>0 or b>0 or ry>0 or rb>0: return "IMPOSSIBLE"
        return "GR"*r
    if rb==y and y>0:
        if r>0 or b>0 or ry>0 or yb>0: return "IMPOSSIBLE"
        return "VY"*y
    rr=r-yb
    yy=y-rb
    bb=b-ry
    ybchain="RG"*yb+"R"
    rbchain="YV"*rb+"Y"
    rychain="BO"*ry+"B"
    raw=build(rr,yy,bb)
    if raw==None: return "IMPOSSIBLE"
    raw=raw.replace('R',ybchain,1)
    raw=raw.replace('Y',rbchain,1)
    raw=raw.replace('B',rychain,1)
    return raw

if __name__=='__main__':
    item=input()
    tn=int(item)
    for ti in range(tn):
        items=input().split()
        n=int(items[0])
        r=int(items[1])
        ry=int(items[2])
        y=int(items[3])
        yb=int(items[4])
        b=int(items[5])
        rb=int(items[6])
        ans=solve(r,y,b,ry,yb,rb)
        print("Case #{0}: {1}".format(ti+1,ans))
