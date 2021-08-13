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
#include <cstdarg>
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

inline ll mod(ll x) { return ((x%M) + M) % M; }
inline ll add(ll a, ll b){return (a+b)%M;}
inline ll sub(ll a, ll b){return (a+M-b)%M;}
ll neg(ll x) {return mod(-x);}
inline ll mul(ll a, ll b){
    return (a*b)%M;
}
ll power(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}
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
// ll inv(ll a) {
//     return power(a,M-2);
// }
ll inv(ll a) {
    ll x, y;
    ll d = extended_euclid(a, M, x, y);
    if (d > 1) return -1;
    return mod(x);
}


const ll N=1000000;
ll f0[N*3+1];
ll f1[N*3+1];
ll fact[N*3+1];
ll invfact[N*3+1];

ll combination(ll n, ll x){
    if (x<0||x>n) return 0;
    return mul(fact[n],mul(invfact[x],invfact[n-x]));
}

int main()
{
    ll n=scan();
    f0[0]=f1[0]=n;
    fact[0]=invfact[0]=1;
    rng(x,1,n*3+1){
        fact[x]=mul(fact[x-1],x);
    }
    invfact[n*3]=inv(fact[n*3]);
    rng(x,0,n*3){
        ll y=n*3-x;
        invfact[y-1]=mul(invfact[y],y);
    }
    ll inv3=inv(3LL);
    rng(x,1,n*3+1){
        f0[x]=mul(inv3,sub(combination(n*3,x+1),add(mul(2ll,f0[x-1]),f1[x-1])));
        f1[x]=add(f0[x],f0[x-1]);
    }
    ll qn=scan();
    rng(qi,0,qn){
        ll x=scan();
        // cout<<add(f0[x],combination(n*3,x))<<endl;
        printf("%lld\n",add(f0[x],combination(n*3,x)));
    }
    return 0;
}
