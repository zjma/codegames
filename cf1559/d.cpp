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
    ll totalSetCount;
    UnionFind(ll n) : C(n), h(n),totalSetCount(n) {
        for (int i=0;i<n;i++) C[i]=i;
    }
    ll find(ll x) {
        return (C[x] == x) ? x : C[x]=find(C[x]);
    }
    void merge(ll x, ll y) {
        ll xp = find(x), yp = find(y);
	if (xp==yp) return;
    totalSetCount--;
        if (h[xp]==h[yp]) {h[xp]++;C[yp]=xp;}
	if (h[xp]<h[yp]) {C[xp]=yp;}
	if (h[xp]>h[yp]) {C[yp]=xp;}
    }
    ll getSetCount(){
        return totalSetCount;
    }
};

priority_queue<pair<ll,ll>> hp;//item: (-m2d[mi].size(), mi) for every mi
map<ll,set<ll>> m2d;
map<ll,set<ll>> d2m;
map<pair<ll,ll>,ll> repr;

pair<ll,ll> getDianaSetsToMerge(ll mi0, ll mi1){
    assert(m2d[mi0].size()>=m2d[mi1].size());
    set<ll>::iterator it=m2d[mi0].begin();
    ll di0=*it;
    ll di1=*(m2d[mi1].begin());
    if (di0==di1) di0=*(++it);
    return make_pair(di0,di1);
}

void mergeMochaSets(ll mi0, ll mi1){
    for(ll di:m2d[mi1]){
        repr[make_pair(mi0,di)]=repr[make_pair(mi1,di)];
        m2d[mi0].insert(di);
        d2m[di].erase(mi1);
        d2m[di].insert(mi0);
    }
}

void mergeDianaSets(ll di0, ll di1){
    for (ll mi:d2m[di1]){
        repr[make_pair(mi,di0)]=repr[make_pair(mi,di1)];
        d2m[di0].insert(mi);
        m2d[mi].erase(di1);
        m2d[mi].insert(di0);
    }
}

inline ll getRepr(ll mi, ll di){
    return repr[make_pair(mi,di)];
}

int main()
{
    ll n=scan();
    ll en[2];
    en[0]=scan();
    en[1]=scan();
    UnionFind uf[2] = {UnionFind(n),UnionFind(n)};
    rng(pi,0,2){
        rng(i,0,en[pi]){
            ll u=scan()-1;
            ll v=scan()-1;
            uf[pi].merge(u,v);
        }
    }
    ll mocha=(uf[0].getSetCount()<=uf[1].getSetCount())?0:1;
    rng(i,0,n){
        ll mi=uf[mocha].find(i);
        ll di=uf[1-mocha].find(i);
        repr[make_pair(mi,di)]=i;
        m2d[mi].insert(di);
        d2m[di].insert(mi);
    }
    rng(i,0,n){
        if (uf[mocha].find(i)==i){
            hp.push(make_pair(m2d[i].size(),i));
        }
    }
    ll mn=uf[mocha].getSetCount();
    cout<<mn-1<<endl;
    rng(i,0,mn-1){
        ll mi0=hp.top().second;hp.pop();
        ll mi1=hp.top().second;hp.pop();
        ll di0,di1;
        tie(di0,di1)=getDianaSetsToMerge(mi0,mi1);
        cout<<getRepr(mi0,di0)+1<<' '<<getRepr(mi1,di1)+1<<endl;
        mergeMochaSets(mi0,mi1);
        if (d2m[di0].size()<d2m[di1].size()) swap(di0,di1);
        mergeDianaSets(di0,di1);
        hp.push(make_pair(m2d[mi0].size(),mi0));
    }
    return 0;
}
