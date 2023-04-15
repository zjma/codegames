def work(m, r, sorted_lights):
    n = len(sorted_lights)
    used = 0
    last_covered_pos = 0
    last_used_light = -1
    while True:
        if last_covered_pos>=m: return used
        if last_used_light==n-1:
            if last_covered_pos<m: return -1
            return used

        nxt = last_used_light + 1
        while nxt<n and sorted_lights[nxt]-r<=last_covered_pos:
            nxt+=1
        if nxt-1==last_used_light: return -1
        last_used_light = nxt-1
        last_covered_pos = min(m, sorted_lights[nxt-1]+r)
        used+=1

tn=int(input())
for ti in range(tn):
    m,r,n = [int(x) for x in input().split()]
    sorted_lights = [int(x) for x in input().split()]
    assert n==len(sorted_lights)
    ans = work(m,r,sorted_lights)
    if ans<0: ans='IMPOSSIBLE'
    print(f'Case #{ti+1}: {ans}')
