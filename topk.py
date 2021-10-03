import random

def topK(arr, k):
    n=len(arr)
    if n==1: return arr[0]
    p=random.choice(arr)
    equal=[x for x in arr if x==p]
    small=[x for x in arr if x<p]
    large=[x for x in arr if x>p]
    if len(small)>=k: return topK(small,k)
    if len(small)+len(equal)<k: return topK(large,k-len(small)-len(equal))
    return p

def test():
    assert topK([4,3,2,1],3)==3
    assert topK([4,2,2,1],3)==2
    assert topK([4],1)==4
    print('!')
test()
