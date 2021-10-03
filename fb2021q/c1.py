tn=int(input())
for ti in range(tn):
    n=int(input())
    goldOf = [int(item) for item in input().split()]
    nextsOf={}
    for i in range(n-1):
        x,y=[int(item)-1 for item in input().split()]
        nextsOf.setdefault(x,[]).append(y)
        nextsOf.setdefault(y,[]).append(x)
    highScoresOf={}
    visited=set()
    def explore(cur):
        visited.add(cur)
        childrenHighScores = []
        for child in nextsOf.get(cur,[]):
            if child in visited: continue
            explore(child)
            if child in highScoresOf:
                score,leaf = highScoresOf[child][0]
                childrenHighScores.append((score+goldOf[child],leaf))
            else:
                childrenHighScores.append((goldOf[child],child))
            pass
        if childrenHighScores:
            childrenHighScores.sort(reverse=True)
            highScoresOf[cur]=childrenHighScores[:2]
            pass
        pass
    explore(0)
    if 0 not in highScoresOf:
        ans=goldOf[0]
    elif len(highScoresOf[0])==1:
        ans=highScoresOf[0][0][0]+goldOf[0]
    else:
        ans=highScoresOf[0][0][0]+highScoresOf[0][1][0]+goldOf[0]
    print(f'Case #{ti+1}: {ans}')
