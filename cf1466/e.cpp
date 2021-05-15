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

ll mod(ll x) { return (x > M) ? (x%M) : x; }
ll add(ll a, ll b){return mod(a+b);}
ll mul(ll a, ll b){return mod(a*b);}
//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

#define pow2(x) (1LL<<(x))
#define getbit(x,i) (((x)>>(i))&1LL)

ll f[60];
ll X[500000];
ll pow2[60];
ll work(ll n, ll m){
    rng(k,0,m){
        f[k]=0;
        rng(i,0,n){
            f[k]+=getbit(X[i],k);
        }
        f[k]=mul(f[k],pow2[k]);
    }
    ll ans=0;
    rng(i,0,n){
        ll term1=0;
        rng(k,0,m){
            term1=add(term1,mul(getbit(X[i],k),f[k]));
        }
        ll term2=mul(n,mod(X[i]));
        rng(k,0,m){
            term2=add(term2,mul(f[k],(1-getbit(X[i],k))));
        }
        ans=add(ans,mul(term1,term2));
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    pow2[0] = 1;
    for (int i = 1; i < 60; i++) {
            pow2[i] = mul(pow2[i-1],2);
    }
    ll tn;
    cin>>tn;
    rng(ti,0,tn){
        ll n;
        cin>>n;
        ll w=0;
        rng(i,0,n){
            cin>>X[i];
            w=max(w,(64ll-__builtin_clzll(X[i])));
        }
        ll ans=work(n,w);
        cout<<ans<<endl;
    }
    return 0;
}
