import asyncio
from pathlib import Path
from pprint import pprint
import random
import subprocess
import uuid

async def genInput():
    vn = random.randint(3,5)
    en = random.randint(vn, 5*vn)
    edges = []
    for ei in range(en):
        if ei<vn:
            v0 = ei
            v1 = (v0+1)%vn
            wt = random.randint(1,8)
            edges.append({'fr':v0,'to':v1,'wt':wt})
        else:
            v0 = random.randint(0,vn-1)
            v1 = random.randint(0,vn-1)
            if v0==v1: continue
            wt = random.randint(1,8)
            edges.append({'fr':v0,'to':v1,'wt':wt})
    queries = [random.randint(0,9) for _ in range(1)]
    return {
        'nodeCount': vn,
        'edges': edges,
        'queries': queries,
    }

class UnionFind:
    def __init__(self, n):
        self.parentOf = [i for i in range(n)]
    def merge(self, x, y):
        rx = self.find(x)
        ry = self.find(y)
        if rx==ry: return False
        self.parentOf[rx] = ry
        return True
    def find(self, x):
        if self.parentOf[x] == x: return x
        rx = self.find(self.parentOf[x])
        self.parentOf[x] = rx
        return rx

def kruskal(nodeCount, edges):
    uf = UnionFind(nodeCount)
    edges.sort(key=lambda e:e['wt'])
    ans = 0
    for edge in edges:
        if uf.merge(edge['fr'], edge['to']):
            ans+=edge['wt']
    return ans

async def runExpectedAsync(inputData):
    ans = []
    for q in inputData['queries']:
        updatedEdges = [{'fr':e['fr'], 'to':e['to'], 'wt':abs(q-e['wt'])} for e in inputData['edges']]
        curAns = kruskal(inputData['nodeCount'], updatedEdges)
        ans.append(curAns)
    return ans

async def runActualAsync(inputData):
    edges = inputData['edges']
    queries = inputData["queries"]
    caseId = uuid.uuid4().hex[:6]
    lines = []
    lines.append(f'{inputData["nodeCount"]} {len(edges)}')
    for edge in edges:
        lines.append(f'{edge["fr"]+1} {edge["to"]+1} {edge["wt"]}')
    lines.append(f'{len(queries)} {len(queries)} {0} {0} {max(max(e["wt"] for e in edges),max(queries))+1}')
    lines.append(f'{" ".join([str(q) for q in queries])}')
    inputText = '\n'.join(lines)
    Path('ein-egen').write_text(inputText)
    proc = subprocess.Popen(f'e.exe', shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    stdoutData,stderrData = proc.communicate(input=inputText.encode())
    ans = [int(x) for x in stdoutData.decode().split()]
    return ans

async def main():
    for i in range(999):
        inputData = await genInput()
        task1 = runExpectedAsync(inputData)
        task2 = runActualAsync(inputData)
        expected = await task1
        actual = await task2
        smr = {
            'case':i,
            'input':inputData,
            'expected':expected,
            'actual':actual
        }
        pprint(smr)
        assert expected == actual

asyncio.run(main())
