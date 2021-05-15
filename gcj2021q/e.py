import random
tn=int(input())
p=int(input())
for ti in range(tn):
    QueEasiness=[0]*10000
    players=[[[] for _ in range(2)] for _ in range(100)]
    auc=[0]*100
    for i in range(100):
        for qid,answer in enumerate(input()):
            answer=int(answer)
            players[i][answer].append(qid)
            QueEasiness[qid]+=answer
    for i in range(100):
        for _ in range(1000):
            qid0 = random.choice(players[i][0])
            qid1 = random.choice(players[i][1])
            if QueEasiness[qid0]<QueEasiness[qid1]:
                auc[i]+=1
    _,ans = min([(auc[pid],pid) for pid in range(100)])
    print(f'Case {ti+1}: {ans+1}')
