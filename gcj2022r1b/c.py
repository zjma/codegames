from random import randint
def randBinStr(size):
    vals = [i for i in range(8)]
    sel=[0]*8
    for i in range(size):
        pos = randint(0,7-i)
        vals[pos],vals[-1]=vals[-1],vals[pos]
        sel[vals.pop()]=1
    return ''.join([str(sel[i]) for i in range(8)])

def work():
    cur='00000000'
    while True:
        print(cur)
        verdict=int(input())
        if verdict==0:
            return True
        elif verdict==-1:
            return False
        else:
            cur = randBinStr(verdict)
tn=int(input())
for ti in range(tn):
    if not work(): break
