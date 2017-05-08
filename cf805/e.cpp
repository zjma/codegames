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

ll setmin(set<ll> &s){
    return *(s.begin());
}

void build(ll v, const VVI &nb, VI &met, VVI &v2sons){
    met[v]=1;
    for(auto u:nb[v]){
        if (met[u]) continue;
        v2sons[v].push_back(u);
    }
    for(auto chd:v2sons[v]){
        build(chd,nb,met,v2sons);
    }
}

void dfs(const VVI &v2sons, const vector<set<ll>> &v2ices, ll v, map<ll,ll> &coloring, set<ll> &idlecolors){
    auto myices=v2ices[v];
    for (auto pr:coloring){
        ll ice=pr.first;
        ll cid=pr.second;
        if (myices.find(ice)==myices.end()){
            idlecolors.insert(cid);
        }
    }
    for(auto ice:myices){
        if (coloring.find(ice)==coloring.end()){
            ll newcid=setmin(idlecolors);
            idlecolors.erase(newcid);
            coloring[ice]=newcid;
        }
    }
    for (auto chd:v2sons[v]){
        dfs(v2sons,v2ices,chd,coloring,idlecolors);
    }
}

int main()
{
    ll n=scan();
    ll m=scan();
    vector<set<ll>> v2ices(n);
    rng(i,0,n){
        ll t=scan();
        rng(j,0,t){
            v2ices[i].insert(scan()-1);
        }
    }
    VVI nb(n);
    rng(i,0,n-1){
        ll tx=scan()-1,ty=scan()-1;
        nb[tx].push_back(ty);
        nb[ty].push_back(tx);
    }
    VI met(n);
    VVI v2sons(n);
    build(0,nb,met,v2sons);

    map<ll,ll> coloring;

    set<ll> idlecolors;
    rng(i,0,m){
        idlecolors.insert(i);
    }

    dfs(v2sons,v2ices,0,coloring,idlecolors);

    ll tot=-1;
    rng(i,0,m){
        tot=max(tot,coloring[i]);
    }

    printf("%lld\n",tot+1);
    rng(i,0,m-1){
        printf("%lld ",coloring[i]+1);
    }
    printf("%lld\n",coloring[m-1]+1);
    return 0;
}
