def hop(pos,layer,offset):
    if offset==3:
        return pos+layer-1,layer-2,0
    else:
        return pos+layer-1,layer,offset+1

# print(hop(24,3,3))
# exit(0)
def work():
    n,k=[int(x) for x in input().split()]
    savetarget=n**2-1-k
    firstcand=4*n-6
    firstpos=2
    if savetarget%2==1:
        return 'IMPOSSIBLE'
    cand=firstcand
    pos=firstpos
    layer=n
    offset=0
    saves=[]
    while cand>0 and savetarget>0:
        if cand<=savetarget:
            newpos,newlayer,newoffset=pos,layer,offset
            for _ in range(4):
                newpos,newlayer,newoffset=hop(newpos,newlayer,newoffset)
            savetarget-=cand
            saves.append((pos,newpos-1))
            cand-=8
            pos,layer,offset=newpos,newlayer,newoffset
        else:
            pos,layer,offset=hop(pos,layer,offset)
            cand-=2
    if savetarget==0:
        return saves
    else:
        return 'IMPOSSIBLE'
tn=int(input())
for ti in range(tn):
    ans=work()
    if ans=='IMPOSSIBLE':
        print(f'Case #{ti+1}: {ans}')
    else:
        print(f'Case #{ti+1}: {len(ans)}')
        for v0,v1 in ans:
            print(f'{v0} {v1}')
