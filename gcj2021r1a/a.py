def inc(a):
    n=len(a)
    digits = [int(x) for x in a[::-1]]
    carry=1
    for i in range(n):
        digits[i]+=carry
        carry=digits[i]//10
        digits[i]%=10
    if carry>=1:
        digits.append(carry)
    return ''.join([str(x) for x in digits[::-1]])

def fix(a,b):
    a=inc(a)
    if len(b)>len(a) or len(b)==len(a) and b>=a:
        return b
    if len(b)==len(a) and a>b:
        return f'{b}0'
    pre_a = a[:len(b)]
    if pre_a==b:
        return a
    elif pre_a<b:
        zeros='0'*(len(a)-len(b))
        return f'{b}{zeros}'
    else:
        zeros='0'*(len(a)-len(b)+1)
        return f'{b}{zeros}'

tn=int(input())
for ti in range(tn):
    ans=0
    n=int(input())
    X=input().split()
    for i in range(1,n):
        newXi=fix(X[i-1], X[i])
        ans+=len(newXi)-len(X[i])
        X[i]=newXi
    print(f'Case #{ti+1}: {ans}')
