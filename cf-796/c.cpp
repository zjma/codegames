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
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;


//constants
const DOUBLE EPS=1e-9;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

const ll N=3000000;
VI e2t;
VI e2f;
VI v2e0;
VI e2n;

vector<VI> children;
ll strength[N];
ll chdcount[N];
ll treestren[N];
ll treestrenexr[N];
vector<VI> f;
vector<VI> gr;
vector<VI> gl;
ll ans[N];

void buildadjlist(ll n,
    const vector<ll> &froms, const vector<ll> &tos,
    vector<ll> &v2e0, vector<ll> &e2n)
{
    v2e0.resize(n);
    v2e0.assign(n, -1);
    ll en = froms.size();
    e2n.resize(en);
    for (int i = 0;i < en;i++) {
        ll f = froms[i];
        ll t = tos[i];
        e2n[i] = v2e0[f];
        v2e0[f] = i;
    }
}



void build_children(ll self, ll parent){
    ll ei=v2e0[self];
    while(ei>=0){
        ll chd=e2t[ei];
        if (chd!=parent) children[self].push_back(chd);
        ei=e2n[ei];
    }
    chdcount[self]=children[self].size();
    rng(i,0,chdcount[self]){
        ll chd=children[self][i];
        build_children(chd,self);
    }
}

void prepare(ll self){
    rng(i,0,chdcount[self]){
        ll chd=children[self][i];
        prepare(chd);
    }
    treestrenexr[self]=0;
    rng(i,0,chdcount[self]){
        ll chd=children[self][i];
        treestrenexr[self]=max(treestrenexr[self],treestren[chd]);
    }
    treestren[self]=max(strength[self],treestrenexr[self]);
}

void preparefg(ll self){
    ll chdn=chdcount[self];
    gl[self].resize(chdn+1);
    gr[self].resize(chdn+1);
    f[self].resize(chdn);
    rng(i,0,chdn+1){
        ll chd=(i==0)?-1:children[self][i-1];
        gl[self][i]=(i==0)?0:max(gl[self][i-1],treestren[chd]);
    }
    rng(i,0,chdn+1){
        ll ii=chdn-i;
        ll chd=(i==0)?-1:children[self][ii];
        gr[self][i]=(i==0)?0:max(gr[self][i-1],treestren[chd]);
    }
    rng(i,0,chdn){
        ll chd=children[self][i];
        f[self][i]=max(gl[self][i],gr[self][chdn-i-1]);
    }
    rng(i,0,chdn){
        ll chd=children[self][i];
        preparefg(chd);
    }
}
void solve(ll self, ll parent, ll faraway){
    if (self<0) return;
    ans[self]=strength[self];
    ans[self]=max(ans[self],faraway+2);
    if (parent>=0) ans[self]=max(ans[self],strength[parent]+1);
    rng(j,0,chdcount[self]){
        ll chd=children[self][j];
        ans[self]=max(ans[self],strength[chd]+1);
        ans[self]=max(ans[self],treestrenexr[chd]+2);
    }
    rng(j,0,chdcount[self]){
        ll chd=children[self][j];
        ll newfaraway=faraway;
        newfaraway=max(newfaraway,strength[parent]);
        newfaraway=max(newfaraway,f[self][j]);
        solve(chd,self,newfaraway);
    }
}

int main()
{
    ll n;scanll(n);
    rng(i,0,n){
        scanll(strength[i]);strength[i]+=10000000000;
    }
    rng(i,0,n-1){
        ll u,v;scanll(u);scanll(v);--u;--v;
        e2f.push_back(u);
        e2t.push_back(v);
        e2f.push_back(v);
        e2t.push_back(u);
    }
    buildadjlist(n,e2f,e2t,v2e0,e2n);
    children.resize(n);
    build_children(0,-1);
    prepare(0);
    f.resize(n);
    gl.resize(n);
    gr.resize(n);
    preparefg(0);
    solve(0,-1,0);

    ll bst=ans[0];
    rng(i,0,n){
        bst=min(bst,ans[i]);
    }
    bst-=10000000000;
    cout<<bst<<endl;
    return 0;
}
