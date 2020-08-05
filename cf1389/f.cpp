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

void discretize(set<ll> &s, VI &a, VI &b){
    ll n=a.size();
    map<ll,ll> v2v;
    ll sc=0;
    for(auto v:s){
        v2v[v]=sc++;
    }
    rng(i,0,n){
        a[i]=v2v[a[i]];
        b[i]=v2v[b[i]];
    }
}

struct SegTree {
    ll sl;
    ll sr;
    ll val;
    ll base;
    ll pending;
    SegTree *cl;
    SegTree *cr;
};

SegTree *segtree_new(ll sl, ll sr, ll bv){
    SegTree *result=new SegTree();
    result->sl=sl;
    result->sr=sr;
    result->val=result->base=bv;
    result->pending=0;
    result->cl=result->cr=NULL;
    return result;
}

bool segtree_trysplit(SegTree *root){
    if (root==NULL||root->sl==root->sr||root->cl) return false;
    ll sep=(root->sl+root->sr)/2;
    root->cl=segtree_new(root->sl,sep,root->base);
    root->cr=segtree_new(sep+1,root->sr,root->base);
    return true;
}
void segtree_update(SegTree*,ll,ll,ll);
void segtree_pushdown_pending(SegTree *root){
    if (root==NULL) return;
    segtree_update(root->cl,root->sl,root->sr,root->pending);
    segtree_update(root->cr,root->sl,root->sr,root->pending);
    root->pending=0;
}

ll segtree_get(SegTree *root, ll ql, ll qr){
    if (root==NULL||ql>root->sr||qr<root->sl||ql>qr) return -INF;
    if (ql<=root->sl&&qr>=root->sr) return root->val;
    segtree_trysplit(root);
    segtree_pushdown_pending(root);
    return max(segtree_get(root->cl,ql,qr),segtree_get(root->cr,ql,qr));
}

void segtree_update(SegTree *root, ll ql, ll qr, ll diff){
    if (root==NULL||qr<root->sl||ql>root->sr) return;
    if (ql<=root->sl&&qr>=root->sr){
        root->val+=diff;
        root->pending+=diff;
        return;
    }
    segtree_trysplit(root);
    segtree_pushdown_pending(root);
    segtree_update(root->cl,ql,qr,diff);
    segtree_update(root->cr,ql,qr,diff);
    root->val=max(root->cl->val,root->cr->val);
}

void segtree_dump(SegTree *root){
    if (root==NULL) return;
    cerr<<"["<<root->sl<<","<<root->sr<<"] : "<<root->val<<endl;
    segtree_dump(root->cl);
    segtree_dump(root->cr);
}

void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->cl);
    segtree_free(root->cr);
    delete root;
}

void dumpVI(VI &arr){
    for (ll a:arr){
        cerr<<a<<',';
    }
    cerr<<endl;
}

int main()
{
    ll n=scan();
    VI l(n);
    VI r(n);
    VI t(n);
    set<ll> positionSet;
    positionSet.insert(-INF);
    rng(i,0,n){
        l[i]=scan();
        r[i]=scan();
        t[i]=scan()-1;
        positionSet.insert(l[i]);
        positionSet.insert(r[i]);
    }
    ll pn=positionSet.size();
    discretize(positionSet,l,r);
    map<ll,map<ll,VI>> pos2starts;
    rng(i,0,n) pos2starts[t[i]][r[i]].push_back(l[i]);
    SegTree *tree[2]={segtree_new(0,pn-1,0),segtree_new(0,pn-1,0)};
    rng(p,0,pn){
        rng(c,0,2){
            VI &starts=pos2starts[c][p];
            if (!starts.empty()){
                sort(starts.begin(),starts.end());
                ll stn=starts.size();
                ll bst=0;
                rng(sti,0,stn){
                    ll crt=segtree_get(tree[1-c],0,starts[sti]-1)+stn-sti;
                    bst=max(bst,crt);
                }
                segtree_update(tree[c],p,p,bst);
                rng(sti,0,stn){
                    segtree_update(tree[1-c],0,starts[sti]-1,1);
                }
            }
        }
    }
    ll ans=max(segtree_get(tree[0],0,pn-1),segtree_get(tree[1],0,pn-1));
    cout<<ans<<endl;
    return 0;
}
