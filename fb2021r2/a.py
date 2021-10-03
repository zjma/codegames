def calc(curOldModels, curNewModels, goal):
    pending = []
    nxtOldModels = []
    nxtNewModels = []
    for style,cost in curOldModels:
        if goal.get(style,0)>=1:
            nxtOldModels.append((style,cost))
            goal[style]-=1
        else:
            pending.append((style,cost))
    for style in curNewModels:
        if goal.get(style,0)>=1:
            nxtNewModels.append(style)
            goal[style]-=1
        else:
            pending.append((style,0))
    for v,c in goal.items():
        for _ in range(c):
            style,cost = pending.pop()
            nxtOldModels.append((v,cost+1))
    return nxtOldModels,nxtNewModels

def readLineToInts():
    return [int(x) for x in input().split()]

tn=int(input())
for ti in range(tn):
    n,m = readLineToInts()
    curNewModels = readLineToInts()
    curOldModels = {}
    for i in range(n):
        curGoal = readLineToInts()
        goal = {}
        for g in curGoal:
            goal[g]=goal.get(g,0)+1
        curOldModels,curNewModels = calc(curOldModels,curNewModels,goal)
    ans = sum(cost-1 for _,cost in curOldModels) if curOldModels else 0
    print(f'Case #{ti+1}: {ans}')
