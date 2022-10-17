def work():
    input()
    s=input()
    nexts = [None]*26
    prevs = [None]*26
    def travel(cur):
        siz=1
        while nexts[cur]!=None:
            siz+=1
            cur=nexts[cur]
        return cur,siz
    for c in s:
        curval = ord(c)-97
        if prevs[curval]!=None: continue
        v2,siz = travel(curval)
        for plaintxt_cand in range(26):
            if plaintxt_cand==v2 and siz!=26: continue
            if nexts[plaintxt_cand]!=None: continue
            prevs[curval]=plaintxt_cand
            nexts[plaintxt_cand]=curval
            break
    ans=''.join([chr(prevs[ord(c)-97]+97) for c in s])
    print(ans)
tn=int(input())
for ti in range(tn):
    work()
