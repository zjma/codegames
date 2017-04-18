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

/**
 * Build adjacent lists from edges.
 *
 * \param n     vertex 0 .. n-1
 * \param froms edge.from
 * \param tos   edge.to
 *
 * \assume fromes.len==tos.len
 *
 * \return v2e0 first edge
 * \return e2n  edge.next
 */
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

bool allconnected(ll n, VI &e2to, VI &v2e0, VI &e2nx, vector<bool> &ccl){
    ll first=-1;
    ll nwithedges=0;
    rng(i,0,n){
        if (v2e0[i]>=0||ccl[i]){
            ++nwithedges;
            first=i;
        }
    }
    vector<bool> arr(n);
    ll reached=1;
    arr[first]=true;
    queue<ll> q;
    q.push(first);
    while (!q.empty()){
        ll c=q.front();
        q.pop();
        for(int ei=v2e0[c];ei>=0;ei=e2nx[ei]){
            ll d=e2to[ei];
            if (arr[d]) continue;
            arr[d]=true;
            ++reached;
            q.push(d);
        }
    }
    return nwithedges==reached;
}

int main()
{
    ll n,m;scanll(n);scanll(m);
    ll c=0;
    vector<ll> froms;
    vector<ll> tos;
    VI v2e0;
    VI e2n;
    vector<bool> ccl(n);
    VI d(n);
    rng(i,0,m){
        ll x,y;
        scanll(x);scanll(y);
        --x;--y;
        if (x==y)
        {
            ccl[x]=true;
            ++c;
            continue;
        }
        froms.push_back(x);
        froms.push_back(y);
        tos.push_back(y);
        tos.push_back(x);
        ++d[x];++d[y];
    }
    buildadjlist(n,froms,tos,v2e0,e2n);
    if (!allconnected(n,tos,v2e0,e2n,ccl)) {
        cout<<0<<endl;
        return 0;
    }
    ll ans1=0;
    rng(i,0,n){
        ans1+=d[i]*(d[i]-1)/2;
    }
    ll ans2=c*m-c*(c+1)/2;
    ll ans=ans1+ans2;
    cout<<ans<<endl;
    return 0;
}
