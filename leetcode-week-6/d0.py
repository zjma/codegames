class Solution(object):
    def trapRainWater(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        nrow = len(heightMap)
        ncol = len(heightMap[0]) if nrow>0 else 0
        def isBorder(x,y):
            return x==0 or x==nrow-1 or y==0 or y==ncol-1
        def valid(x,y):
            return x>=0 and x<nrow and y>=0 and y<ncol
        def validNbs(x,y):
            nx,ny = x,y+1
            if valid(nx,ny): yield (nx,ny)
            nx,ny = x,y-1
            if valid(nx,ny): yield (nx,ny)
            nx,ny = x+1,y
            if valid(nx,ny): yield (nx,ny)
            nx,ny = x-1,y
            if valid(nx,ny): yield (nx,ny)
        def AllPos():
            for x in range(nrow):
                for y in range(ncol):
                    yield (x,y)
        Max = 0
        Min = 99999999999999999
        for i,j in AllPos():
            Min = min(Min,heightMap[i][j])
            Max = max(Max,heightMap[i][j])

        lose = [[isBorder(x,y) for y in range(ncol)] for x in range(nrow)]
        q = [(x,y) for x,y in AllPos() if isBorder(x,y)]
        qh = 0
        qt = len(q)
        while qh<qt:
            cx,cy = q[qh]
            for nx,ny in validNbs(cx,cy):
                if lose[nx][ny]: break
                if heightMap[nx][ny]>=heightMap[cx][cy]:
                    lose[nx][ny]=True
                    q.append((nx,ny))
                    qt+=1
            qh+=1


        class Heap:
            def __init__(self):
                self.a = []
            def add(self, v):
                self.a.append(v)
                i = len(self.a)-1
                while True:
                    if i<=0: break
                    j = (i-1)//2
                    if self.a[j]<=self.a[i]: break
                    self.a[j],self.a[i] = self.a[i],self.a[j]
                    i = j
            def top(self):
                return self.a[0]
            def pop(self):
                self.a[0] = self.a[-1]
                self.a.pop()
                i = 0
                n = len(self.a)
                while i<n:
                    j = i*2+1
                    if j>=n: break
                    if j+1<n and self.a[j]>self.a[j+1]: j+=1
                    if self.a[i]<=self.a[j]: break
                    self.a[i],self.a[j] = self.a[j],self.a[i]
                    i = j
            def empty(self):
                return len(self.a)==0

        borderhp = Heap()
        for x,y in AllPos():
            if heightMap[x][y]==Min:
                borderhp.add((heightMap[x][y],x,y))
        q = []
        inq = [[False for _ in range(ncol)] for _ in range(nrow)]
        def showq():
            print
            for i in range(nrow):
                print ''.join(('1' if inq[i][j] else '0') for j in range(ncol))
            print

        showq()
        ans = 0
        while not borderhp.empty():
            cv,cx,cy = borderhp.top()
            borderhp.pop()
            inq[cx][cy] = True
            if len(q)>0:
                px,py = q[-1]
                ans+=(cv-heightMap[px][py])*len(q)
                print "cv={0},cxy=({3},{4}) ,hp={2},lenq={1}".format(cv,len(q),heightMap[px][py],cx,cy)
                print "ans={0}".format(ans)
            for nx,ny in validNbs(cx,cy):
                if inq[nx][ny]: continue
                borderhp.add((heightMap[nx][ny],nx,ny))
            if not lose[cx][cy]:
                q.append((cx,cy))
                showq()
        return ans

d = [
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

s = Solution()
print(s.trapRainWater(d))
