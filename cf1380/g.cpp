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
const ll M = 998244353;

ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
ll power(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}
ll gcd(ll a, ll b) { for (;b>0;swap(a, b))a %= b;return a; }
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a / b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}
ll inv(ll a) {
    ll x, y;
    ll d = extended_euclid(a, M, x, y);
    if (d > 1) return -1;
    return mod(x);
}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan();
    }
    sort(a.begin(),a.end());
    VI pfs(n+1,0);
    rng(i,0,n) pfs[i+1]=add(pfs[i],a[i]);
    ll q_inv=inv(n);
    rng(i,1,n){
        ll segcount=(i<=n/2)?i:(n-i);
        ll ballcount=n-i;
        ll q=ballcount/segcount;//x1 ... x1 ... xq ... xq
        ll r=ballcount%segcount; //x(q+1) r times
        ll ans=mul(q+1,pfs[r]);
        rng(j,1,q+1){
            ll cur=mul(q+1-j,sub(pfs[r+segcount*j],pfs[r+segcount*(j-1)]));
            ans=add(ans,cur);
        }
        cout<<mul(ans,q_inv)<<endl;
    }
    cout<<0<<endl;
    return 0;
}
