import sys
import subprocess
from random import randint

M=1000000007
def solve(s):
    n=len(s)
    stk=[]
    for c in s:
        cv=ord(c)-48
        while len(stk)>0 and stk[-1]<cv:
            stk.pop()
        stk.append(cv)
    stk+=[0 for _ in range(n-len(stk))]
    ans=0
    for v in stk:
        ans=(ans*10+v)%M
    return ans

def getlines(s):
    prelines=["#include <cassert>"]
    func1lines=[
        "long long GetNumberLength() {return "+str(len(s))+"LL;}"
    ]
    func2pres=[
        "long long GetDigit(long long i) {",
        "switch ((int)i) {",
    ]
    func2posts=[
        "default: assert(0);}}"
    ]
    caselines=["case {0}: return {1}LL;".format(i,c) for i,c in enumerate(s)]
    func2lines=func2pres+caselines+func2posts
    return prelines+func1lines+func2lines

def convert_s_to_file(s,filename):
    with open(filename,"w") as f:
        lines=getlines(s)
        lines=[line+"\n" for line in lines]
        f.writelines(lines)

def runwithcpp(s):
    convert_s_to_file(s,"fuckb.h")
    cppout=subprocess.check_output(["bash","drun","weird_editor","fuckb.h","10"])
    cppres=int(cppout.split()[2])
    return cppres

def genrandomdigits(L):
    assert(L>=2)
    digits=[randint(1,9)]+[randint(0,9) for _ in range(L-1)]
    return "".join([str(d) for d in digits])

def main():
    for ti in range(1000):
        s=genrandomdigits(20)
        print("Case {0}: {1}".format(ti,s))
        anspy=solve(s)
        anscpp=runwithcpp(s)
        print("pyresult: {0}".format(anspy))
        print("cpresult: {0}".format(anscpp))
        print
        sys.stdout.flush()
        if anspy!=anscpp:
            print "FUCK"
            print "FUCK"
            print "FUCK"
            return

if __name__=='__main__': main()
