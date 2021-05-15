def achievable(needs, start):
    counts = [0]*(start)+[1]
    for i in range(start,-1,-1):
        burnable = counts[i]-needs[i] if i<len(needs) else counts[i]
        if burnable<0: return False
        counts[i]-=burnable
        if i>=1: counts[i-1]+=burnable
        if i>=2: counts[i-2]+=burnable
    return True

tn = int(input())
for ti in range(tn):
    n,a,b = [int(x) for x in input().split()]
    needs = [int(x) for x in input().split()]
    for start in range(len(needs), 400):
        if achievable(needs, start):
            ans = start
            break
    print(f'Case #{ti+1}: {start+1}')
