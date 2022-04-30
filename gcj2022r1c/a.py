from collections import defaultdict

allchars = [chr(i+65) for i in range(26)]

def getpattern(word,char):
    ans=''
    prev=None
    for i,c in enumerate(word):
        cur='1' if c==char else '0'
        if cur!=prev:
            ans+=cur
        prev=cur
    return ans

def work():
    n=int(input())
    words=input().split()

    P=defaultdict(list)
    isP1=[False]*n
    tot=0
    for wid,word in enumerate(words):
        tot+=len(word)
        for char in allchars:
            pat=getpattern(word,char)
            if len(pat)>=4: return 'IMPOSSIBLE'
            if pat=='101': return 'IMPOSSIBLE'
            if pat=='0': continue
            P[(char,pat)].append(wid)
            if pat=='1':
                isP1[wid]=True
    # print(P)
    for char in allchars:
        if len(P[(char,'010')])>=2:
            return 'IMPOSSIBLE'
        elif len(P[(char,'010')])==1:
            if len(P[(char,'10')])>=1 or len(P[(char,'01')])>=1 or len(P[(char,'1')])>=1:
                return 'IMPOSSIBLE'
        else:
            if len(P[(char,'10')])>=2 or len(P[(char,'01')])>=2:
                return 'IMPOSSIBLE'

    letter2extra=defaultdict(int)

    nextof=[None]*n
    prevof=[None]*n
    for char in allchars:
        letter2extra[char]+=sum(len(words[wid]) for wid in P[(char,'1')])
        for wid0 in P[(char,'01')]:
            for wid1 in P[(char,'10')]:
                nextof[wid0]=wid1
                prevof[wid1]=wid0
    ans=''
    for i in range(n):
        if not isP1[i] and prevof[i]==None:
            visited=set()
            cur=i
            while True:
                visited.add(cur)
                c0=words[cur][0]
                c1=words[cur][-1]
                ans+=c0*letter2extra[c0]+words[cur]+c1*letter2extra[c1]
                letter2extra[c0]=0
                letter2extra[c1]=0
                cur=nextof[cur]
                if cur in visited: return 'IMPOSSIBLE'
                if cur==None: break
    for char in allchars:
        ans+=char*letter2extra[char]
    if len(ans)<tot: return 'IMPOSSIBLE'
    return ans
tn=int(input())
for ti in range(tn):
    ans = work()
    print(f'Case #{ti+1}: {ans}')
