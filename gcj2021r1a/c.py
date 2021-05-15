from pprint import pprint

def getAllStandards(n):
    if n==1:
        yield 'F'
        yield 'T'
    else:
        for s in getAllStandards(n-1):
            yield f'{s}T'
            yield f'{s}F'

def grade(qn, std, answer):
    return len([1 for i in range(qn) if std[i]==answer[i]])

def findAllMatch(qn, sn, answersheets, scores):
    result = []
    for standard in getAllStandards(qn):
        if all(grade(qn, standard, answersheets[i])==scores[i] for i in range(sn)):
            result.append(standard)
    return result

pprint(findAllMatch(6,2,['FFTTTF','FTFTFT'],[2,4]))
