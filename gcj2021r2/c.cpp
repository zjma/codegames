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
ll mod_inverse(ll a) {
    ll x, y;
    ll d = extended_euclid(a, M, x, y);
    if (d > 1) return -1;
    return mod(x);
}

//extra operations
ll log2floor(ll x){
    assert(x>=1);
    return 63LL-__builtin_clzll(x);
}
ll log2ceil(ll x){
    assert(x>=1);
    return (x==1)?0LL:(64LL-__builtin_clzll(x-1));
}


struct RMQOracle {
    ll N;
    VVI f0;
    VVI f1;
    RMQOracle(const VI &a){
        N=a.size();
        ll K=log2floor(N);
        f0.resize(N);
        f1.resize(N);
        rng(i,0,N){f0[i].resize(K+1);f1[i].resize(K+1);}
        rng(i,0,N) f0[i][0]=f1[i][0]=a[i]*100000+(N-1-i);
        rng(k,1,K+1){
            ll half=1<<(k-1);
            rng(i,0,N){
                if (i+half*2<=N) f0[i][k]=min(f0[i][k-1],f0[i+half][k-1]);
                if (i-half*2+1>=0) f1[i][k]=min(f1[i][k-1],f1[i-half][k-1]);
            }
        }
    }
    ll get(ll ql, ll qr){
        assert(0<=ql);assert(ql<=qr);assert(qr<N);
        ll k=log2floor(qr-ql+1);
        return min(f0[ql][k],f1[qr][k]);
    }
};

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

ll fv[100001];
ll F(ll x){
    if (fv[x]==0){
        fv[x]=(x==0)?1:mul(F(x-1),x);
    }
    return fv[x];
}
ll C(ll n, ll x){
    ll den=mul(F(x),F(n-x));
    return mul(F(n),mod_inverse(den));
}
ll work(VI &V, RMQOracle* o, ll rdepth, ll start, ll end){
    ll n=V.size();
    if (start>end) return 1;
    ll resp = o->get(start,end);
    ll v=resp/100000;
    ll idx=n-1-resp%100000;
    if (V[idx]!=rdepth+1) return 0;
    ll sub0=work(V,o,rdepth,start,idx-1);
    ll sub1=work(V,o,rdepth+1,idx+1,end);
    ll ans=mul(C(end-start,idx-start),mul(sub0,sub1));
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI V(n);
        rng(i,0,n){
            V[i]=scan();
        }
        RMQOracle* o=new RMQOracle(V);
        ll ans=work(V,o,0,0,n-1);
        free(o);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
