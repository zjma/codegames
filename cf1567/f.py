from random import randint

chars='.X'
def randMap():
    rn=5
    cn=5
    map=[[None for _ in range(cn)] for _ in range(rn)]
    for i in range(rn):
        for j in range(cn):
            if i==0 or i==rn-1 or j==0 or j==cn-1:
                map[i][j]='.'
            else:
                map[i][j]=chars[randint(0,1)]
    return map
def adjCoors(ri,ci):
    yield (ri,ci+1)
    yield (ri,ci-1)
    yield (ri-1,ci)
    yield (ri+1,ci)

def solve0(map):
    rn=len(map)
    cn=len(map[0])
    matters=set()
    def nextCoor(ri,ci):
        if ci==cn-1: return (ri+1,0)
        return (ri,ci+1)
    def explore(ri,ci,ans):
        if ri==rn:
            for rj in range(rn):
                for cj in range(cn):
                    if map[rj][cj]=='X' and sum(ans[x][y] for x,y in adjCoors(rj,cj))%5!=0:
                        return False
            return True
        ri2,ci2=nextCoor(ri,ci)
        if map[ri][ci]=='.':
            ans[ri][ci]=1
            if explore(ri2,ci2,ans):
                return True
            ans[ri][ci]=4
            if explore(ri2,ci2,ans):
                return True
            return False
        return explore(ri2,ci2,ans)

    ans=[[0 for _ in range(cn)] for _ in range(rn)]
    if explore(0,0,ans):
        return ans
    else:
        return None
def solve(map):
    rn=len(map)
    cn=len(map[0])
    def isValid(x,y): return 0<=x<rn and 0<=y<cn
    ans=[[0 for _ in range(cn)] for _ in range(rn)]
    need=[[None for _ in range(cn)] for _ in range(rn)]
    for ri in range(rn):
        for ci in range(cn):
            adjXs=[(x,y) for x,y in adjCoors(ri,ci) if isValid(x,y) and map[x][y]=='X']
            if adjXs:
                _need4=need4[adjXs[0][0]][adjXs[0][1]]
                if any(need4[rj][cj]!=_need4 for rj,cj in adjXs): return None
                ans[ri][ci]=4 if _need4 else 1
                for rj,cj in adjXs:
                    need4[rj][cj]=not _need4
            else:
                ans[ri][ci]=1
    for ri in range(rn):
        for ci in range(cn):
            if need4[ri][ci]: return None
    return ans
def printSol(ans):
    if ans:
        print('YES')
        for line in ans:
            print(''.join([str(x) for x in line]))
    else:
        print('NO')

for _ in range(999):
    map = randMap()
    print()
    print('Map=')
    for line in map: print(''.join(line))
    assignedMap0 = solve0(map)
    print('Sol0=')
    printSol(assignedMap0)
    assignedMap = solve(map)
    assert (assignedMap==None) == (assignedMap0==None)
