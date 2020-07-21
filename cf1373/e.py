def findPref(targetDigitSum):
    assert targetDigitSum>=0
    if targetDigitSum==0: return ''
    if targetDigitSum<=8: return str(targetDigitSum)
    rem=targetDigitSum-8
    if rem%9==0:
        return '9'*(rem//9)+'8'
    return str(rem%9)+'9'*(rem//9)+'8'

def findPref9(target):
    assert target>=0
    if target==0: return ''
    if target%9==0: return '9'*(target//9)
    return str(target%9)+'9'*(target//9)

def compare(a,b):
    if a==None and b==None: return 0
    if a==None: return 1
    if b==None: return -1
    if len(a)>len(b): return 1
    if len(b)>len(a): return -1
    if a>b: return 1
    if a<b: return -1
    return 0

def solve(n,k):
    ans=None
    for d0 in range(10):
        sumLowDigitColumns=sum(((d0+d)%10) for d in range(k+1))
        HON=0 if d0+k<=9 else (10-d0)
        if HON==0:
            rem=n-sumLowDigitColumns
            if rem>=0 and rem%(k+1)==0:
                pref=findPref9(rem//(k+1))
                cur=pref+str(d0)
                if compare(cur,ans)<0:
                    ans=cur
        else:
            WON=0
            while True:
                rem=n-sumLowDigitColumns+HON-WON*HON*9-k-1
                if rem<0: break
                if rem%(k+1)==0:
                    pref=findPref(rem//(k+1))
                    cur=pref+'9'*WON+str(d0)
                    if compare(cur,ans)<0:
                        ans=cur
                WON+=1
    return -1 if ans==None else ans
TN=int(input())
for _ in range(TN):
    items=input().split()
    n=int(items[0])
    k=int(items[1])
    print(solve(n,k))
