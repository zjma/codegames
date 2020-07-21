def binarySearch1(lo,hi,check):
    while lo+1<hi:
        new=(lo+hi)//2
        if check(new):
            hi=new
        else:
            lo=new
    return hi

print(binarySearch1(5,7,lambda x:x>=6))
