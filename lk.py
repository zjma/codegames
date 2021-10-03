class Node:
    def __init__(self, val):
        self.val = val
        self.nxt = None


def lklistToArrayList(head):
    result=[]
    while head:
        result.append(head.val)
        head=head.nxt
    return result

def arrayList2Lklist(arr):
    fakeHead=Node(-1)
    pre=fakeHead
    for val in arr:
        cur=Node(val)
        pre.nxt=cur
        pre=cur
    return fakeHead.nxt

def reverseAll(preHead,head,tail,postTail):
    pre = postTail
    cur = head
    while cur!=postTail:
        nxt = cur.nxt
        cur.nxt = pre
        pre = cur
        cur = nxt
    if preHead:
        preHead.nxt = tail

def reverseK(head,k):
    segCount=0
    fake = Node(-1)
    fake.nxt = head
    lastSegTail = fake
    newHead = fake
    cur = head
    while cur:
        nxt = cur.nxt
        segCount+=1
        if segCount==1:
            curSegHead=cur
        if segCount==k:
            reverseAll(lastSegTail,curSegHead,cur,nxt)
            lastSegTail = curSegHead
            segCount=0
        cur = nxt
    return newHead.nxt

def test():
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),3))==[3,2,1,4,5]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),2))==[2,1,4,3,5]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),1))==[1,2,3,4,5]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),5))==[5,4,3,2,1]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),6))==[1,2,3,4,5]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1,2,3,4,5]),6))==[1,2,3,4,5]
    assert lklistToArrayList(reverseK(arrayList2Lklist([1]),1))==[1]
    assert lklistToArrayList(reverseK(arrayList2Lklist([]),2))==[]
test()
