import sys

def main(U):
    record=0
    for da in range(U+1):
        for db in range(U+1):
            for dc in range(U+1):
                dd=U-da-db-dc
                if dd<0: continue
                a=min(100,40+da)
                b=min(100,30+db)
                c=min(100,20+dc)
                d=min(100,10+dd)
                p4=a*b*c*d
                p3=a*b*c*(100-d)+a*b*d*(100-c)+a*d*c*(100-b)+d*b*c*(100-a)
                p2=a*b*(100-c)*(100-d)+a*c*(100-b)*(100-d)+a*d*(100-b)*(100-c)+b*c*(100-a)*(100-d)+b*d*(100-a)*(100-c)+c*d*(100-a)*(100-b)
                p1=a*(100-b)*(100-c)*(100-d)+b*(100-a)*(100-c)*(100-d)+c*(100-b)*(100-a)*(100-d)+d*(100-a)*(100-b)*(100-c)
                r=p4+p3+p2
                if r>record:
                    reca,recb,recc,recd=a,b,c,d
                    record=r
    print(reca,recb,recc,recd)

if __name__=='__main__':
    main(int(sys.argv[1]))
