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
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)
void dumpVI(VI &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        cerr<<pfx<<"["<<i<<"]="<<a[i]<<endl;
    }
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void readArr(ll n, ll k, VI &Arr){
    rng(i,0,k){
        Arr[i]=scan();
    }
    ll A=scan();
    ll B=scan();
    ll C=scan();
    ll D=scan();
    rng(i,k,n){
        Arr[i]=(A*Arr[i-2]+B*Arr[i-1]+C)%D+1;
    }
}

struct SegTree {
    ll seg_left;
    ll seg_right;
    ll base;
    bool pending;
    ll value;
    SegTree *child_left;
    SegTree *child_right;
};

SegTree *segtree_new(ll sl, ll sr, ll bv){
    SegTree *result=new SegTree();
    result->seg_left=sl;
    result->seg_right=sr;
    result->base=bv;
    result->value=(sr-sl+1)*bv;
    result->pending=false;
    result->child_left=result->child_right=NULL;
    return result;
}
void segtree_set(SegTree *root, ll ql, ll qr, ll newval);
void segtree_prepare_children(SegTree *root){
    if (root==NULL) return;
    if (root->seg_left!=root->seg_right&&root->child_left==NULL){
        ll sep=(root->seg_left+root->seg_right)/2;
        root->child_left=segtree_new(root->seg_left,sep,root->base);
        root->child_right=segtree_new(sep+1,root->seg_right,root->base);
    }
    if (root->pending){
        segtree_set(root->child_left,root->seg_left,root->seg_right,root->base);
        segtree_set(root->child_right,root->seg_left,root->seg_right,root->base);
        root->pending=false;
    }
}

void segtree_set(SegTree *root, ll ql, ll qr, ll newval){
    if (root==NULL||qr<root->seg_left||ql>root->seg_right) return;
    if (ql<=root->seg_left&&qr>=root->seg_right){
        root->base=newval;
        root->pending=true;
        root->value=newval*(root->seg_right-root->seg_left+1);
        return;
    }
    segtree_prepare_children(root);
    segtree_set(root->child_left,ql,qr,newval);
    segtree_set(root->child_right,ql,qr,newval);
    root->value=root->child_left->value+root->child_right->value;
}

ll segtree_get(SegTree *root, ll ql, ll qr){
    if (root==NULL||ql>root->seg_right||qr<root->seg_left||ql>qr) return 0;
    if (ql<=root->seg_left&&qr>=root->seg_right) return root->value;
    segtree_prepare_children(root);
    return segtree_get(root->child_left,ql,qr)+segtree_get(root->child_right,ql,qr);
}

void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->child_left);
    segtree_free(root->child_right);
    delete root;
}

ll solve(ll n, const VI &L, const VI &W, const VI &H){
    ll ans=1;
    ll x_min=INF, x_max=0;
    rng(i,0,n){
        x_min=min(x_min,L[i]);
        x_max=max(x_max,L[i]+W[i]);
    }
    cout<<x_min<<","<<x_max<<endl;
    SegTree *heights=segtree_new(x_min-1,x_max+1,0);
    SegTree *sum_horizontal=segtree_new(x_min-1,x_max+1,0);
    SegTree *sum_vertical=segtree_new(x_min-1,x_max+1,0);
    rng(i,0,n){
        ll R=L[i]+W[i];
        ll newLeftBar=H[i]-segtree_get(heights,L[i]-1,L[i]-1);
        ll newRightBar=H[i]-segtree_get(heights,R,R);
        segtree_set(sum_vertical,L[i]+1,R-1,0);
        segtree_set(sum_vertical,L[i],L[i],newLeftBar);
        segtree_set(sum_vertical,R,R,newRightBar);
        ll cur_vertical=segtree_get(sum_vertical,x_min-1,x_max+1);
        segtree_set(sum_horizontal,L[i],R-1,1);
        segtree_set(heights,L[i],R-1,H[i]);
        ll cur_horizontal=segtree_get(sum_horizontal,x_min-1,x_max-1)*2;
        ll cur=cur_horizontal+cur_vertical;
        ans=mul(ans,cur);
    }
    segtree_free(sum_vertical);
    segtree_free(heights);
    segtree_free(sum_horizontal);
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();ll k=scan();
        VI L(n);
        VI W(n);
        VI H(n);
        readArr(n,k,L);
        readArr(n,k,W);
        readArr(n,k,H);
        ll ans=solve(n,L,W,H);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
