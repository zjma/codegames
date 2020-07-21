// template.cpp : Defines the entry point for the console application.
//
#include <climits>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <list>
#include <tuple>
#include <ctime>
#include <cassert>
#include <cstring>
using namespace std;

//type shortcuts
typedef long long ll;
typedef vector<ll> VI;
typedef vector<VI> VVI;
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef tuple<ll,ll> PII;
//constants
const ll INF=0x1fffffffffffffff;
const double INFD=1e20;
const double EPS=1e-9;
const double PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

struct Node {
    ll segLeft;
    ll segRight;
    ll base;
    ll value;
    ll pendingDiff;
    Node *leftChild;
    Node *rightChild;
};

Node* newNode(ll segLeft, ll segRight, ll base){
    Node *result = new Node();
    result->segLeft=segLeft;
    result->segRight=segRight;
    result->base=base;
    result->value=base;
    result->pendingDiff=0;
    result->leftChild=NULL;
    result->rightChild=NULL;
    return result;
}

bool ensureChildren(Node *root){
    if (root==NULL) return false;
    if (root->segLeft==root->segRight) return false;
    if (root->leftChild!=NULL) return true;
    ll separator=(root->segLeft+root->segRight)/2;
    root->leftChild=newNode(root->segLeft, separator, root->base);
    root->rightChild=newNode(separator+1, root->segRight, root->base);
    return true;
}
void update(Node *root, ll queryLeft, ll queryRight, ll diff);
void pushPending(Node *root){
    if (!ensureChildren(root)) return;
    update(root->leftChild, root->segLeft, root->segRight, root->pendingDiff);
    update(root->rightChild, root->segLeft, root->segRight, root->pendingDiff);
    root->pendingDiff=0;
}

void update(Node *root, ll queryLeft, ll queryRight, ll diff){
    if (root==NULL) return;
    if (queryLeft>queryRight) return;
    if (queryLeft>root->segRight || queryRight<root->segLeft) return;
    if (queryLeft<=root->segLeft && queryRight>=root->segRight){
        root->value+=diff;
        root->pendingDiff+=diff;
        return;
    }
    pushPending(root);
    update(root->leftChild, queryLeft, queryRight, diff);
    update(root->rightChild, queryLeft, queryRight, diff);
    root->value=max(root->leftChild->value,root->rightChild->value);
}

ll query(Node *root, ll queryLeft, ll queryRight){
    if (root==NULL) return -INF;
    if (queryLeft>queryRight) return -INF;
    if (queryLeft>root->segRight || queryRight<root->segLeft) return -INF;
    if (queryLeft<=root->segLeft && queryRight>=root->segRight) return root->value;
    pushPending(root);
    ll subLeft=query(root->leftChild,queryLeft,queryRight);
    ll subRight=query(root->rightChild,queryLeft,queryRight);
    return max(subLeft,subRight);
}

void dumpTree(Node *root){
    if (root==NULL) return;
    cout<<"val["<<root->segLeft<<","<<root->segRight<<"]="<<root->value<<endl;
    cout<<"pen["<<root->segLeft<<","<<root->segRight<<"]="<<root->pendingDiff<<endl;
    dumpTree(root->leftChild);
    dumpTree(root->rightChild);
}
int main()
{
    ll n=scan();
    ll k=scan();
    ll m=scan();
    set<PII> pawns;
    map<ll,ll> slot;
    Node *segTree=newNode(1,2*n-1,0);
    rng(i,0,2*n-1){
        update(segTree,i+1,i+1,i);
    }
    rng(i,0,m){
        ll x=scan();
        ll y=scan();
        ll b=y+abs(x-k);
        PII loc=make_tuple(x,y);
        if (pawns.find(loc)==pawns.end()){
            pawns.insert(loc);
            slot[b]++;
            update(segTree,1,b,1);
        }else{
            pawns.erase(loc);
            slot[b]--;
            if (slot[b]==0){
                slot.erase(b);
            }
            update(segTree,1,b,-1);
        }
        ll expected=0;
        if (slot.size()==0){
            expected=0;
        }else{
            ll lastSlotNumber=slot.rbegin()->first;
            expected=query(segTree,1,lastSlotNumber);
        }
        ll ans=max(0LL,expected-n);
        cout<<ans<<endl;
    }
    return 0;
}
