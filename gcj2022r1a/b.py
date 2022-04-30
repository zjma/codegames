def printArrInline(arr):
    print(' '.join([str(x) for x in arr]))
def work():
    n=int(input())
    assert n==100
    A0 = [(2**i) for i in range(30)]
    A1 = [(1000000000-x) for x in range(70)]
    A = A0+A1
    printArrInline(A)
    B=[int(x) for x in input().split()]
    buc0 = []
    buc1 = []
    for x in (B+A1+A0[::-1]):
        if sum(buc0)<=sum(buc1):
            buc0.append(x)
        else:
            buc1.append(x)
    printArrInline(buc0)

tn=int(input())
for ti in range(tn):
    work()
