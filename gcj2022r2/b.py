def calc0(r,x,y):
    return 1 if round((x**2+y**2)**0.5)<=r else 0

def work():
    k=int(input())
    c0={i:{j:calc0(k,i,j) for j in range(-k,k+1)} for i in range(-k,k+1)}
    c1={i:{j:0 for j in range(-k,k+1)} for i in range(-k,k+1)}
    for r in range(-k,k+1):
        for x in range(-r,r+1):
            y=round((r**2-x**2)**0.5)
            c1[x][y]=c1[x][-y]=c1[y][x]=c1[-y][x]=1
    return sum(abs(c0[i][j]-c1[i][j]) for i in range(-k,k+1) for j in range(-k,k+1))
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
