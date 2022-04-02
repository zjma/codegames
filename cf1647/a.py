tn=int(input())
for ti in range(tn):
    n=int(input())
    if n%3==0:
        ans='21'*(n//3)
    elif n%3==1:
        ans='12'*(n//3)+'1'
    else:
        ans='21'*(n//3)+'2'
    print(ans)
