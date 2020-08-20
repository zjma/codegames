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
    return (segtree_get(root->child_left,ql,qr)+segtree_get(root->child_right,ql,qr));
}

void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->child_left);
    segtree_free(root->child_right);
    delete root;
}

ll solve(ll n, const VI &L, const VI &W, const VI &H){
    set<ll> posSet;
    rng(i,0,n){
        posSet.insert(L[i]);
        posSet.insert(L[i]+W[i]);
    }
    VI positions(posSet.begin(),posSet.end());
    ll pn=positions.size();

    map<ll,ll> p2dp;
    rng(pi,0,pn) p2dp[positions[pi]]=pi;

    VI xseglen(pn+1,INF);
    rng(i,0,pn-1) xseglen[i+1]=positions[i+1]-positions[i];

    VVI events(pn,VI());
    rng(i,0,n){
        ll pi0=p2dp[L[i]];
        ll pi1=p2dp[L[i]+W[i]];
        events[pi0].push_back(i*2);
        events[pi1].push_back(i*2+1);
    }

    VI room2hcontri(n);
    VI xseg2srcroom(pn+1,-1);
    set<ll> activeIntervalSet;
    rng(pi,0,pn){
        for(ll evt:events[pi]){
            ll roomId=evt/2;
            ll isRightEdge=evt%2;
            if (isRightEdge){
                activeIntervalSet.erase(roomId);
            }else{
                activeIntervalSet.insert(roomId);
            }
        }
        if (!activeIntervalSet.empty()){
            ll srcRoomId=*activeIntervalSet.begin();
            xseg2srcroom[pi+1]=srcRoomId;
            room2hcontri[srcRoomId]+=xseglen[pi+1];
        }
    }

    SegTree *enabledSegs=segtree_new(0,pn,0);
    SegTree *leftBarSet=segtree_new(0,pn-1,0);
    SegTree *rightBarSet=segtree_new(0,pn-1,0);
    ll pre_vertical=0;
    ll pre_horizontal=0;
    ll ans=1;
    rng(i,0,n){
        ll DL=p2dp[L[i]],DR=p2dp[L[i]+W[i]];
        ll victimLeftBarCount=segtree_get(leftBarSet,DL+1,DR);
        ll victimRightBarCount=segtree_get(rightBarSet,DL,DR-1);
        ll victimBarCount=victimLeftBarCount+victimRightBarCount;
        ll newLeftBar=(segtree_get(enabledSegs,DL,DL+1)==0);
        ll newRightBar=(segtree_get(enabledSegs,DR,DR+1)==0);
        ll cur_vertical=pre_vertical+H[i]*(newLeftBar+newRightBar-victimBarCount);

        segtree_set(enabledSegs,DL+1,DR,1);
        ll cur_horizontal=pre_horizontal+room2hcontri[i]*2;
        ll cur=cur_horizontal+cur_vertical;
        ans=mul(ans,cur);

        segtree_set(leftBarSet,DL+1,DR,0);
        segtree_set(rightBarSet,DL,DR-1,0);
        if (newLeftBar) segtree_set(leftBarSet,DL,DL,1);
        if (newRightBar) segtree_set(rightBarSet,DR,DR,1);
        pre_vertical=cur_vertical;
        pre_horizontal=cur_horizontal;
    }

    segtree_free(enabledSegs);
    segtree_free(rightBarSet);
    segtree_free(leftBarSet);
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
