tn=int(input())
def exec(W,curHand):
    ans=0
    for c in W:
        if curHand==0 and c=='O':
            ans+=1
            curHand=1
        elif curHand==1 and c=='X':
            ans+=1
            curHand=0
    return ans
for ti in range(tn):
    n=int(input())
    W=input()
    ans=min(exec(W,0),exec(W,1))
    print(f'Case #{ti+1}: {ans}')
