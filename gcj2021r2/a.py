tn,n=[int(x) for x in input().split()]
for ti in range(tn):
    for i in range(n-1):
        print(f'M {i+1} {n}')
        response=int(input())
        if response!=i+1:
            print(f'S {i+1} {response}')
            response=int(input())
            #assert response==1
    print(f'D')
    response=int(input())
