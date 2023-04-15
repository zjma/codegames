from collections import Counter
def work(arr):
    n=len(arr)
    ctr = Counter(arr)
    if len(ctr)==1:
        return (n+1)//2
    i=1
    while arr[i]==arr[i-1]: i+=1
    arr = arr[i:]+arr[:i]
    ans = 0
    i=1
    while i<n:
        if arr[i]==arr[i-1]:
            ans+=1
            i+=2
        else:
            i+=1
    return ans
tn=int(input())
for ti in range(tn):
    ans = work(input())
    print(f'Case #{ti+1}: {ans}')
