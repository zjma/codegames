from math import floor,log

n,m=[int(x) for x in input().split()]
initial=[int(x) for x in input().split()]
queries=[]
for _ in range(m-1):
    args=[int(x) for x in input().split()]
    queries.append(args)

class Node:
    def __init__(self, label):
        self.label=label
        self.left=None
        self.right=None
        self.value=0
        self.depth=None
        self.ancestors=[]
    def __str__(self):
        leftLabel=self.left.label if self.left else 'nul'
        rightLabel=self.right.label if self.right else 'nul'
        return f'label={self.label},left={leftLabel},right={rightLabel},value={self.value},depth={self.depth},ancestors={[a.label for a in self.ancestors]}'

nodes=[Node(i) for i in range(2*m-1)]
repr=[nodes[i] for i in range(m)]
for qi,args in enumerate(queries):
    tid0=args[0]-1
    tid1=args[1]-1
    nodes[m+qi].left=repr[tid0]
    nodes[m+qi].right=repr[tid1]
    repr[tid0]=nodes[m+qi]

def initTree(node, ancestors):
    if node==None: return
    node.depth=len(ancestors)
    pi=0
    while len(ancestors)>=2**pi:
        node.ancestors.append(ancestors[-(2**pi)])
        pi+=1
    ancestors.append(node)
    initTree(node.left, ancestors)
    initTree(node.right, ancestors)
    ancestors.pop()

initTree(nodes[-1], [])

def dumpTree(root):
    if root==None: return
    print(root)
    dumpTree(root.left)
    dumpTree(root.right)

# dumpTree(nodes[-1])

def LCA(v0, v1):
    if v0==v1: return v0
    if v0.depth>v1.depth: v0,v1=v1,v0
    while v1.depth>v0.depth: v1=v1.ancestors[floor(log(v1.depth-v0.depth, 2))]
    while v0!=v1:
        an=len(v0.ancestors)
        aidx=0
        while aidx<an and v0.ancestors[aidx]!=v1.ancestors[aidx]: aidx+=1
        aidx=max(aidx-1,0)
        v0=v0.ancestors[aidx]
        v1=v1.ancestors[aidx]
    return v0

for i in range(n-1):
    tid0=initial[i]-1
    tid1=initial[i+1]-1
    LCA(nodes[tid0],nodes[tid1]).value+=1

cost=n-1
for i in range(m):
    cost-=nodes[i].value
print(cost)
for qi,query in enumerate(queries):
    cost-=nodes[m+qi].value
    print(cost)
