def solve(a,b,c):
    resulta=-1 if a>=c else 1
    resultb=-1 if a*b<=c else b
    return resulta,resultb
TN=int(input())
for _ in range(TN):
    items=input().split()
    a=int(items[0])
    b=int(items[1])
    c=int(items[2])
    ra,rb=solve(a,b,c)
    print(f'{ra} {rb}')
