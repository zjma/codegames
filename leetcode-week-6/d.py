class Solution(object):
    def trapRainWater(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        Max = 0
        Min = 99999999999999999
        nrow = len(heightMap)
        ncol = len(heightMap[0]) if nrow>0 else 0
        for i in range(nrow):
            for j in range(ncol):
                Min = min(Min,heightMap[i][j])
                Max = max(Max,heightMap[i][j])
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

        ans = 0
        for h in range(Min+1,Max+1):
            tried = [ [False for _ in range(ncol)] for _ in range(nrow)]
            for i in range(nrow):
                for j in range(ncol):
                    if tried[i][j]: continue
                    tried[i][j] = True
                    if heightMap[i][j]>=h: continue
                    q = [(i,j)]
                    qh = 0
                    qt = 1
                    while qh<qt:
                        cx,cy = q[qh]
                        for nx,ny in validNbs(cx,cy):
                            if tried[nx][ny]: continue
                            if heightMap[nx][ny]<h:
                                tried[nx][ny] = True
                                q.append((nx,ny))
                                qt+=1
                        qh+=1
                    wasted = any([isBorder(x,y) for x,y in q])
                    if not wasted:
                        print "at {0} : {1}".format(h,len(q))
                        ans += len(q)
        return ans

d = [
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

s = Solution()
print(s.trapRainWater(d))
