from collections import Counter
tn=int(input())
def enc(l2d, word):
    mapped_chars = [l2d[c] for c in word]
    return ''.join(mapped_chars)
for ti in range(tn):
    l2d = {chr(65+i):c for i,c in enumerate(input().split())}
    assert len(l2d)==26
    wn = int(input())
    words = [input() for _ in range(wn)]
    ciphers = [enc(l2d, x) for x in words]
    c2c=Counter(ciphers)
    ans = any(v>=2 for k,v in c2c.items())
    ans = 'YES' if ans else 'NO'
    print(f'Case #{ti+1}: {ans}')
