def work():
    n=int(input())
    s=[input(),input()]
    start=0
    while start<n-1 and s[0][start]==s[1][start]=='.':
        start+=1
    end=n-1
    while end>=0 and s[0][end]==s[1][end]=='.':
        end-=1
    f=[[0,0] for _ in range(n)]
    for i in range(start,end+1):
        if i==start:
            if s[0][i]=='.' and s[1][i]=='*':
                f[i][0]=1
                f[i][1]=0
            elif s[0][i]=='*' and s[1][i]=='.':
                f[i][0]=0
                f[i][1]=1
            elif s[0][i]=='*' and s[1][i]=='*':
                f[i][0]=1
                f[i][1]=1
            else:
                assert False
        else:
            if s[0][i]=='.' and s[1][i]=='*':
                f[i][0]=min(f[i-1][0]+2,f[i-1][1]+2)
                f[i][1]=min(f[i-1][0]+2,f[i-1][1]+1)
            elif s[0][i]=='*' and s[1][i]=='.':
                f[i][0]=min(f[i-1][0]+1,f[i-1][1]+2)
                f[i][1]=min(f[i-1][0]+2,f[i-1][1]+2)
            elif s[0][i]=='*' and s[1][i]=='*':
                f[i][0]=min(f[i-1][0]+2,f[i-1][1]+2)
                f[i][1]=min(f[i-1][0]+2,f[i-1][1]+2)
            else:
                f[i][0]=min(f[i-1][0]+1,f[i-1][1]+2)
                f[i][1]=min(f[i-1][0]+2,f[i-1][1]+1)
    return min(f[end])

tn=int(input())
for ti in range(tn):
    print(work())
