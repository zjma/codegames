if __name__=='__main__':
    n=int(raw_input())
    if n%2==0:
        l=n//2
        print('1'*l)
    else:
        l=(n-3)//2
        ans='7'+'1'*l
        print(ans)
