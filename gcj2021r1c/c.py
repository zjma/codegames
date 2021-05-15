def getRepr(s):
    if s=='0': return []
    ret = []
    sn=len(s)
    for i in range(sn):
        if i==0 or s[i]!=s[i-1]:
            start=i
        if i==sn-1 or s[i]!=s[i+1]:
            ret.append(i-start+1)
    return ret

tn=int(input())
for ti in range(tn):
    S,E=input().split()
    def work(S,E):
        if E=='0':
            if S=='0': return 0
            s=getRepr(S)
            return len(s)
        else:
            e=getRepr(E)
            extra=0
            if S=='0':
                extra=1
                S='1'
            s=getRepr(S)
            sn=len(s)
            en=len(e)
            for si in range(sn):
                canAmend=sn%2==0 or si>=1
                canAppend=sn%2==1 or si>=1
                if (sn-si)==en:
                    if s[si:-1]!=e[:-1]:continue
                    if s[-1]>e[-1] or (s[-1]<e[-1] and not canAmend): continue
                    return extra+si+e[-1]-s[-1]
                elif (sn-si)==en-1:
                    if s[si:-1]!=e[:-2]: continue
                    if s[-1]>e[-2] or (s[-1]<e[-2] and not canAmend): continue
                    if not canAppend: continue
                    return extra+si+e[-2]+e[-1]-s[-1]
            if en>=3: return 'IMPOSSIBLE'
            return extra+sn-1+sum(e)
    ans=work(S,E)
    print(f'Case #{ti+1}: {ans}')
