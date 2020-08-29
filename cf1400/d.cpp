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

struct SegTree {
    ll sl;
    ll sr;
    ll val;
    SegTree *cl;
    SegTree *cr;
};

SegTree *segtree_new(ll sl, ll sr){
    SegTree *result=new SegTree();
    result->sl=sl;
    result->sr=sr;
    result->val=0;
    result->cl=result->cr=NULL;
    return result;
}

bool segtree_trysplit(SegTree *root){
    if (root==NULL||root->sl==root->sr||root->cl) return false;
    ll sep=(root->sl+root->sr)/2;
    root->cl=segtree_new(root->sl,sep);
    root->cr=segtree_new(sep+1,root->sr);
    return true;
}

ll segtree_get(SegTree *root, ll pos){
    if (root==NULL||pos<root->sl||pos>root->sr) return 0;
    segtree_trysplit(root);
    SegTree *child=(root->cl&&root->cl->sr>=pos)?root->cl:root->cr;
    return root->val+segtree_get(child,pos);
}

void segtree_update(SegTree *root, ll ql, ll qr){
    if (root==NULL||ql>root->sr||qr<root->sl||ql>qr) return;
    if (ql<=root->sl&&qr>=root->sr){
        root->val++;
        return;
    }
    segtree_trysplit(root);
    segtree_update(root->cl,ql,qr);
    segtree_update(root->cr,ql,qr);
}

// void segtree_dump(SegTree *root){
//     if (root==NULL) return;
//     cerr<<"["<<root->sl<<","<<root->sr<<"] : "<<root->val<<endl;
//     segtree_dump(root->cl);
//     segtree_dump(root->cr);
// }
//
void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->cl);
    segtree_free(root->cr);
    delete root;
}


ll solve(ll n, const VI &a){
    ll ans=0;
    unordered_map<ll,VI> v2os;
    SegTree *tree=segtree_new(0,n-1);
    rng(i,0,n){
        for (ll j:v2os[a[i]]){
            ans+=segtree_get(tree,j);
        }
        for (ll j:v2os[a[i]]){
            segtree_update(tree,j+1,i-1);
        }
        v2os[a[i]].push_back(i);
    }
    segtree_free(tree);
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI a(n);
        rng(i,0,n){
            a[i]=scan();
        }
        ll ans=solve(n,a);
        cout<<ans<<endl;
    }
    return 0;
}
