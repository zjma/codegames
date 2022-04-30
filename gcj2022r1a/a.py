def work():
    s=input()
    n=len(s)
    ans=''
    for i in range(n-1):
        if s[i]*2+s[i+1:]<s[i:]:
            ans+=s[i]*2
        else:
            ans+=s[i]
    ans+=s[-1]
    return ans
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
