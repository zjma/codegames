import math

tn=int(input())
for ti in range(tn):
    y=int(input())
    def build(x,k):
        X=[x]
        for _ in range(k-1):
            X.append(X[-1]+1)
        return int(''.join([str(x) for x in X]))
    def work(y,k):
        l=0
        r=int('9'*math.ceil(len(str(y))/k))
        while l+1<r:
            m=(l+r)//2
            if build(m,k)>y:
                r=m
            else:
                l=m
        return build(r,k)
    ans=min([work(y,k) for k in range(2,18)])
    print(f'Case #{ti+1}: {ans}')
