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

struct UnionFind {
    VI C;
    VI h;
    UnionFind(ll n) : C(n), h(n) {
        for (int i=0;i<n;i++) C[i]=i;
    }
    ll find(ll x) {
        return (C[x] == x) ? x : C[x]=find(C[x]);
    }
    ll merge(ll x, ll y) {
        ll xp = find(x), yp = find(y);
        if (xp==yp) return 0;
        if (h[xp]==h[yp]) {h[xp]++;C[yp]=xp;}
        if (h[xp]<h[yp]) {C[xp]=yp;}
        if (h[xp]>h[yp]) {C[yp]=xp;}
        return 1;
    }
};

ll mst(ll n, VI &e2f, VI &e2t, VI &e2w) {
    UnionFind uf(n);
    ll en=e2f.size();
    vector<pair<ll,ll>> weightIdxPairs(en);
    rng(ei,0,en) weightIdxPairs[ei]=make_pair(e2w[ei],ei);
    sort(weightIdxPairs.begin(), weightIdxPairs.end());
    ll total=0;
    rng(i,0,en){
        ll ei = weightIdxPairs[i].second;
        if (uf.merge(e2f[ei],e2t[ei])==1) {
            total+=e2w[ei];
        }
    }
    return total;
}

ll binsearch(ll l, ll r, VI &P, ll target){
    while(l+1<r){
        ll m=(l+r)/2;
        if (P[m]<=target) l=m; else r=m;
    }
    return l;
}
int main()
{
    ll n=scan(),m=scan();
    VI e2f(m),e2t(m),e2w(m),e2aw(m);
    rng(i,0,m){
        e2f[i]=scan()-1;
        e2t[i]=scan()-1;
        e2w[i]=scan();
    }
    ll p=scan(),qn=scan(),a=scan(),b=scan(),c=scan();
    VI Q(qn);
    rng(i,0,p) Q[i]=scan();
    rng(i,p,qn) Q[i]=(Q[i-1]*a+b)%c;
    set<ll> pivots;
    rng(i,0,m){
        pivots.insert(e2w[i]);
        rng(j,i+1,m){
            ll x0=(e2w[i]+e2w[j])/2;
            ll x1=(e2w[i]+e2w[j]+1)/2;
            pivots.insert(x0);
            pivots.insert(x1);
        }
    }
    pivots.insert(0);
    pivots.insert(c);

    VI P(pivots.begin(), pivots.end());
    ll pn=P.size();
    VI V(pn);
    rng(pi,0,pn){
        rng(ei,0,m) e2aw[ei]=abs(e2w[ei]-P[pi]);
        V[pi]=mst(n,e2f,e2t,e2aw);
    }
    // rng(pi,0,pn){
    //     cerr<<P[pi]<<":"<<V[pi]<<endl;
    // }
    ll ans=0;
    rng(i,0,qn){
        ll l=binsearch(0,pn-1,P,Q[i]);
        ll r=l+1;
        // cerr<<"for query "<<Q[i]<<", l="<<l<<endl;
        ll cur=(V[l]*P[r]-V[r]*P[l]+Q[i]*(V[r]-V[l]))/(P[r]-P[l]);
        // cout<<cur<<endl;
        ans^=cur;
    }
    printf("%lld\n", ans);
    return 0;
}
