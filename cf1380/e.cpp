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

static inline ll log2(ll x) {
    return sizeof(ll) * 8 - __builtin_clzll(x) - 1;
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void lcaInit(ll n, VI &lc, VI &rc, ll root, VI& path, VI &dep, VVI &anc){
    if (root<0||root>=n) return;
    ll pn=path.size();
    dep[root]=pn;
    ll pd=1;
    while(pd<=pn){
        anc[root].push_back(path[pn-pd]);
        pd*=2;
    }
    path.push_back(root);
    lcaInit(n,lc,rc,lc[root],path,dep,anc);
    lcaInit(n,lc,rc,rc[root],path,dep,anc);
    path.pop_back();
}

ll lcaQuery(ll n, VI &dep, VVI &anc, ll i0, ll i1){
    if (dep[i0]>dep[i1]) swap(i0,i1);
    while(dep[i0]<dep[i1]) i1=anc[i1][log2(dep[i1]-dep[i0])];
    while(i0!=i1){
        ll aidx=0, an=anc[i0].size();
        while(aidx<an&&anc[i0][aidx]!=anc[i1][aidx]) aidx++;
        aidx=max(aidx-1,0LL);
        i0=anc[i0][aidx];
        i1=anc[i1][aidx];
    }
    return i0;
}

int main()
{
    ll n=scan();
    ll m=scan();
    VI initial(n);
    rng(i,0,n){
        initial[i]=scan();
    }
    VI q0(m-1);
    VI q1(m-1);
    rng(i,0,m-1){
        q0[i]=scan();
        q1[i]=scan();
    }
    VI lc(m*2-1,-1);
    VI rc(m*2-1,-1);
    VI repr(m);rng(i,0,m){repr[i]=i;}
    rng(qi,0,m-1){
        ll tid0=q0[qi]-1;
        ll tid1=q1[qi]-1;
        lc[m+qi]=repr[tid0];
        rc[m+qi]=repr[tid1];
        repr[tid0]=m+qi;
    }
    VI path;
    VI dep(m*2-1);
    VVI anc(m*2-1);
    lcaInit(m*2-1,lc,rc,m*2-2,path,dep,anc);

    VI val(m*2-1,0);
    rng(i,0,n-1){
        ll tid0=initial[i]-1, tid1=initial[i+1]-1;
        ll lca=lcaQuery(m*2-1,dep,anc,tid0,tid1);
        val[lca]++;
    }

    ll ans=n-1;
    rng(i,0,m){
        ans-=val[i];
    }
    cout<<ans<<endl;
    rng(i,0,m-1){
        ans-=val[m+i];
        cout<<ans<<endl;
    }
    return 0;
}
