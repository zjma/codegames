def work(colors):
    n=len(colors)
    seen = set()
    ans = []
    for i in range(n):
        if i==0 or colors[i]!=colors[i-1]:
            # start of a segment of colors[i]
            if colors[i] in seen:
                return None
            seen.add(colors[i])
            ans.append(colors[i])
    return ans
tn=int(input())
for ti in range(tn):
    n=int(input())
    nums = [int(x) for x in input().split()]
    ans = work(nums)
    ans = 'IMPOSSIBLE' if ans==None else ' '.join([str(x) for x in ans])
    print(f'Case #{ti+1}: {ans}')
