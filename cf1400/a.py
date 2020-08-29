tn=int(input())
for ti in range(tn):
    n=int(input())
    s=input()
    ans=''.join([s[i*2] for i in range(n)])
    print(ans)
