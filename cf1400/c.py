def solve(s,x):
    n=len(s)
    a=[None]*n
    todos=[]
    for i,c in enumerate(s):
        if i<=x-1:
            if i+x<n:
                if a[i+x]==None:
                    a[i+x]=int(c)
                else:
                    if int(c)!=a[i+x]: return -1
            else:
                if c=='1': return -1
        elif i>=n-x:
            if i-x>=0:
                if a[i-x]==None:
                    a[i-x]=int(c)
                else:
                    if int(c)!=a[i-x]: return -1
            else:
                if c=='1': return -1
        else:
            if c=='0':
                if a[i-x]==1 or a[i+x]==1: return -1
                a[i-x]=0
                a[i+x]=0
            else:
                todos.append((i-x,i+x))
    for i,j in todos:
        if a[i]==0 and a[j]==0: return -1
    for i in range(n):
        if a[i]==None: a[i]=1
    return ''.join(str(x) for x in a)
tn=int(input())
for ti in range(tn):
    s=input()
    x=int(input())
    ans=solve(s,x)
    print(ans)
