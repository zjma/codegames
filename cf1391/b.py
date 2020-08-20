TN=int(input())
for TI in range(TN):
    rn,cn=[int(x) for x in input().split()]
    rows=[]
    for ri in range(rn):
        rows.append(input())
    ans=len([0 for ci in range(cn-1) if rows[-1][ci]=='D'])+len([0 for ri in range(rn-1) if rows[ri][-1]=='R'])
    print(ans)
