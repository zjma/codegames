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

void buildadjlist(ll n,
    const VI &froms, const VI &tos,
    VI &v2e0, VI &e2n)
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


double calc(int me, int parent, const VI &firstedge, const VI &e2to, const VI &e2next){
    ll ei=firstedge[me];
    double tmp=0;
    ll childcount=0;
    while(ei>=0){
        ll neighbor=e2to[ei];
        if (neighbor!=parent){
            tmp+=1+calc(neighbor, me, firstedge, e2to, e2next);
            ++childcount;
        }
        ei=e2next[ei];
    }
    if (childcount==0) return 0;
    return tmp/childcount;
}

int main()
{
    ll n=scan();

    VI e2from(n*2-2);
    VI e2to(n*2-2);
    VI e2next(n*2-2);
    VI firstedge(n);

    rng(i,0,n-1){
        ll x=scan()-1;
        ll y=scan()-1;
        e2from[i*2]=x;
        e2to[i*2]=y;
        e2from[i*2+1]=y;
        e2to[i*2+1]=x;
    }

    buildadjlist(n,e2from,e2to,firstedge,e2next);

    double ans=calc(0,-1,firstedge, e2to, e2next);
    cout.precision(9);
    cout<<fixed<<ans<<endl;
    return 0;
}
