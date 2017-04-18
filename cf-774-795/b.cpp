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


const ll N=100000;
ll ps[N];
ll pw[N];
ll fs[N];
ll fw[N];
ll psc[N+1];
ll pwc[N+1];
ll fsc[N+1];
ll fwc[N+1];

int main()
{
    ll n,m,d;scanll(n);scanll(m);scanll(d);
    vector<pair<ll,ll>> pinfo(n);
    vector<pair<ll,ll>> finfo(m);
    rng(i,0,n){
        ll s,w;
        scanll(s);scanll(w);
        pinfo[i]=make_pair(-s,w);
    }
    rng(i,0,m){
        ll s,w;
        scanll(s);scanll(w);
        finfo[i]=make_pair(-s,w);
    }
    sort(pinfo.begin(),pinfo.end());
    sort(finfo.begin(),finfo.end());
    rng(i,0,n){
        ps[i]=-pinfo[i].first;
        psc[i+1]=psc[i]+ps[i];
        pw[i]=pinfo[i].second;
        pwc[i+1]=pwc[i]+pw[i];
    }
    rng(i,0,m){
        fs[i]=-finfo[i].first;
        fsc[i+1]=fsc[i]+fs[i];
        fw[i]=finfo[i].second;
        fwc[i+1]=fwc[i]+fw[i];
    }
    ll ans=0;
    rng(i,1,n+1){
        ll remw=d-pwc[i];
        if (remw<=0) continue;
        ll R=m+1;
        ll L=0;
        while (L+1<R){
            ll M=(L+R)/2;
            if (fwc[M]>remw) R=M; else L=M;
        }
        ll j=L;
        if (j==0) continue;
        ans=max(ans,psc[i]+fsc[j]);
    }
    cout<<ans<<endl;

    return 0;
}
