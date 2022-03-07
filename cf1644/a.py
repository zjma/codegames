def readLineToInts():
    return [int(item) for item in input().split()]

tn=readLineToInts()[0]
for ti in range(tn):
    map=input()
    Ri=map.find('R')
    Gi=map.find('G')
    Bi=map.find('B')
    bi=map.find('b')
    ri=map.find('r')
    gi=map.find('g')
    ans=Ri>ri and Gi>gi and Bi>bi
    print(f'{"YES" if ans else "NO"}')
    
