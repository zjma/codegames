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
const ll M = 998244353;

ll add(ll x, ll y){
    return (x+y)%M;
}

ll mul(ll x, ll y){
    return (x*y)%M;
}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

#define score2(x) (((x)>=10&&(x)<=18)?(19-(x)):0)
#define score1(x) ((x)+1)
tuple<ll,ll,ll,ll,ll,ll> fab(ll lc_val, ll lc_val_no_l, ll lc_val_no_r, ll lc_val_no_lr, ll lc_digit_l, ll lc_digit_r, ll rc_val, ll rc_val_no_l, ll rc_val_no_r, ll rc_val_no_lr, ll rc_digit_l, ll rc_digit_r){
    if (lc_val>=INF) return make_tuple(rc_val,rc_val_no_l,rc_val_no_r,rc_val_no_lr,rc_digit_l,rc_digit_r);
    if (rc_val>=INF) return make_tuple(lc_val,lc_val_no_l,lc_val_no_r,lc_val_no_lr,lc_digit_l,lc_digit_r);
    ll mg_val,mg_val_no_l,mg_val_no_r,mg_val_no_lr,mg_digit_l,mg_digit_r;
    ll combined=score2(lc_digit_r*10+rc_digit_l);
    mg_val=add(mul(lc_val,rc_val),mul(mul(lc_val_no_r,rc_val_no_l),combined));
    mg_val_no_l=add(mul(lc_val_no_l,rc_val),mul(mul(lc_val_no_lr,rc_val_no_l),combined));
    mg_val_no_r=add(mul(lc_val,rc_val_no_r),mul(mul(lc_val_no_r,rc_val_no_lr),combined));
    mg_val_no_lr=add(mul(lc_val_no_l,rc_val_no_r),mul(mul(lc_val_no_lr,rc_val_no_lr),combined));
    mg_digit_l=lc_digit_l;
    mg_digit_r=rc_digit_r;
    return make_tuple(mg_val,mg_val_no_l,mg_val_no_r,mg_val_no_lr,mg_digit_l,mg_digit_r);
}

struct SegTree {
    ll sl;
    ll sr;
    ll val;
    ll val_no_l;
    ll val_no_r;
    ll val_no_lr;
    ll digit_l;
    ll digit_r;
    SegTree *cl;
    SegTree *cr;
};

SegTree *segtree_new(ll sl, ll sr){
    SegTree *result=new SegTree();
    result->sl=sl;
    result->sr=sr;
    result->val=result->val_no_l=result->val_no_r=1;
    result->val_no_lr=(sl==sr)?0:1;
    result->digit_l=result->digit_r=0;
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

tuple<ll,ll,ll,ll,ll,ll> segtree_get(SegTree *root, ll ql, ll qr){
    if (root==NULL||ql>root->sr||qr<root->sl||ql>qr) return make_tuple(INF,INF,INF,INF,INF,INF);
    if (ql<=root->sl&&qr>=root->sr) return make_tuple(root->val,root->val_no_l,root->val_no_r,root->val_no_lr,root->digit_l,root->digit_r);
    segtree_trysplit(root);
    ll lc_val,lc_val_no_l,lc_val_no_r,lc_val_no_lr,lc_digit_l,lc_digit_r;
    ll rc_val,rc_val_no_l,rc_val_no_r,rc_val_no_lr,rc_digit_l,rc_digit_r;
    tie(lc_val,lc_val_no_l,lc_val_no_r,lc_val_no_lr,lc_digit_l,lc_digit_r)=segtree_get(root->cl,ql,qr);
    tie(rc_val,rc_val_no_l,rc_val_no_r,rc_val_no_lr,rc_digit_l,rc_digit_r)=segtree_get(root->cr,ql,qr);
    return fab(lc_val,lc_val_no_l,lc_val_no_r,lc_val_no_lr,lc_digit_l,lc_digit_r,rc_val,rc_val_no_l,rc_val_no_r,rc_val_no_lr,rc_digit_l,rc_digit_r);
}

void segtree_update(SegTree *root, ll pos, ll newval){
    if (root==NULL||pos<root->sl||pos>root->sr) return;
    if (root->sl==root->sr){
        root->val=score1(newval);
        root->digit_l=root->digit_r=newval;
    }else{
        segtree_trysplit(root);
        segtree_update(root->cl,pos,newval);
        segtree_update(root->cr,pos,newval);
        tie(root->val,root->val_no_l,root->val_no_r,root->val_no_lr,root->digit_l,root->digit_r)=fab(root->cl->val,root->cl->val_no_l,root->cl->val_no_r,root->cl->val_no_lr,root->cl->digit_l,root->cl->digit_r,root->cr->val,root->cr->val_no_l,root->cr->val_no_r,root->cr->val_no_lr,root->cr->digit_l,root->cr->digit_r);
    }
}

void segtree_dump(SegTree *root){
    if (root==NULL) return;
    cerr<<"["<<root->sl<<","<<root->sr<<"] : val="<<root->val<<", valNoL="<<root->val_no_l<<", valNoR"<<root->val_no_r<<", digitL="<<root->digit_l<<", digitR="<<root->digit_r<<endl;
    segtree_dump(root->cl);
    segtree_dump(root->cr);
}

void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->cl);
    segtree_free(root->cr);
    delete root;
}

char buf[500001];
int main()
{
    ll n=scan();
    ll m=scan();
    scanstr(buf);
    SegTree *segtree=segtree_new(0,n-1);
    rng(i,0,n){
        segtree_update(segtree,i,buf[i]-48);
    }
    // segtree_dump(segtree);
    rng(i,0,m){
        ll x=scan()-1;
        ll d=scan();
        segtree_update(segtree,x,d);
        // segtree_dump(segtree);
        ll val;
        tie(val,ignore,ignore,ignore,ignore,ignore)=segtree_get(segtree,0,n-1);
        cout<<val<<endl;
    }
    return 0;
}
