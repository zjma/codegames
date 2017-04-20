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

int main()
{
    ll n;scanll(n);
    ll pn;scanll(pn);
    ll d;scanll(d);
    VI station(n);
    rng(i,0,pn){
        ll x;scanll(x);--x;
        station[x]=1;
    }

    VI e2f;
    VI e2t;
    VI e2oi;
    VI e2n;
    VI v2e0;
    rng(i,0,n-1){
        ll x,y;scanll(x);scanll(y);--x;--y;
        e2f.push_back(x);
        e2t.push_back(y);
        e2oi.push_back(i);
        e2f.push_back(y);
        e2t.push_back(x);
        e2oi.push_back(i);
    }
    buildadjlist(n,e2f,e2t,v2e0,e2n);

    VI rst(n,-1);
    queue<ll> q;
    rng(i,0,n){
        if (station[i]==1){
            q.push(i);
            rst[i]=i;
        }
    }

    VI ans(n-1);
    while (!q.empty()){
        ll self=q.front();
        q.pop();
        ll ei=v2e0[self];
        while(ei>=0){
            ll next=e2t[ei];
            if (rst[next]==-1){
                rst[next]=rst[self];
                q.push(next);
            }else if (rst[next]!=rst[self]){
                ans[e2oi[ei]]=1;
            }
            ei=e2n[ei];
        }
    }
    ll anscount=0;
    rng(i,0,n-1){
        if (ans[i]==1) anscount++;
    }
    cout<<anscount<<endl;
    rng(i,0,n-1){
        if (ans[i]) cout<<i+1<<" ";
    }cout<<endl;
    return 0;
}
