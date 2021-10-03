from random import randint
n=300000
q=500000
print(n,q)
used = set()
for i in range(q):
    while True:
        x=randint(1,n)
        y=randint(1,n)
        if x==y or (x,y) in used or (y,x) in used: continue
        break
    used.add((x,y))
    print(x,y,randint(0,1))
