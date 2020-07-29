TN=int(input())
def solve(n,s):
    stk=[]
    for c in s:
        if stk and c!=stk[-1]:
            stk.pop()
        else:
            stk.append(c)
    return len(stk)==1
    return False
for TI in range(TN):
    n=int(input())
    s=input()
    ans='Y' if solve(n,s) else 'N'
    print(f'Case #{TI+1}: {ans}')
