from collections import defaultdict

def read_ints_from_line():
    items = input().split()
    return [int(item) for item in items]
n,k = read_ints_from_line()

C = [None]*n
for i in range(n):
    C[i] = input().replace(' ','')
card_set = set(C)

def get_feat_match(v0,v1):
    return (-(v0+v1))%3

def get_match(card0, card1):
    f2=[str(get_feat_match(int(card0[fid]),int(card1[fid]))) for fid in range(k)]
    return ''.join(f2)

match_count_of = defaultdict(int)
for i in range(n):
    for j in range(i+1,n):
        wanted = get_match(C[i],C[j])
        if wanted in card_set:
            match_count_of[wanted]+=1

ans=0
for card,match_count in match_count_of.items():
    ans+=match_count*(match_count-1)//2
print(ans)
