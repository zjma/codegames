tn=int(input())
for ti in range(tn):
    #ans = work()
    rn,cn = [int(x) for x in input().split()]
    evenRow='-'.join(['+']*(cn+1))
    oddRow='.'.join(['|']*(cn+1))
    artrn = rn*2+1
    print(f'Case #{ti+1}:')
    for ri in range(artrn):
        defaultRow = evenRow if ri%2==0 else oddRow
        if ri//2==0:
            print('..'+defaultRow[2:])
        else:
            print(defaultRow)
