NsPerHour=3600000000000
NsPerMin=NsPerHour//60
NsPerSec=NsPerMin//60
TotalNanos = NsPerHour*12

def getNs(hourHandTicks, minHandTicks, secHandTicks):
    return (secHandTicks*3+hourHandTicks*193-minHandTicks*196)%TotalNanos

def permutations(a,b,c):
    yield (a,b,c)
    yield (a,c,b)
    yield (b,a,c)
    yield (b,c,a)
    yield (c,a,b)
    yield (c,b,a)

tn=int(input())
for ti in range(tn):
    a,b,c=[int(x) for x in input().split()]
    answers = []
    for ht,mt,st in permutations(a,b,c):
        ns = getNs(ht,mt,st)
        hourPos=ns
        minPos=(ns*12)%TotalNanos
        secPos=(ns*720)%TotalNanos
        if (hourPos-ht)%TotalNanos==(minPos-mt)%TotalNanos==(secPos-st)%TotalNanos:
            answers.append(ns)
    answers.sort(key=lambda a:a%NsPerSec)
    ans=answers[0]
    h=ans//NsPerHour
    ans%=NsPerHour
    m=ans//NsPerMin
    ans%=NsPerMin
    s=ans//NsPerSec
    ans%=NsPerSec
    print(f'Case #{ti+1}: {h} {m} {s} {ans}')
