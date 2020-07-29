TN=int(input())
def isBlack(pos):
    return (pos[0]+pos[1])%2
for TI in range(TN):
    rn,cn,k=[int(item) for item in input().split()]
    xpos=[int(item) for item in input().split()]
    hpos=[None]*k
    for i in range(k):
        hpos[i]=[int(item) for item in input().split()]
    ans='Y' if k==2 and isBlack(hpos[0])==isBlack(hpos[1]) and isBlack(hpos[1])==isBlack(xpos) else 'N'
    print(f'Case #{TI+1}: {ans}')
