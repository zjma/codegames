import random
N=1000000
qn=200000
print(N,qn)
for _ in range(qn):
    print(random.randint(1,N*3))
