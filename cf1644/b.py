def readLineToInts():
    return [int(item) for item in input().split()]

tn=readLineToInts()[0]
for ti in range(tn):
    n=readLineToInts()[0]
    for i in range(n):
        curans = ([(j+1) for j in range(n) if j!=i]+[i+1])[::-1]
        print(' '.join([str(x) for x in curans]))
