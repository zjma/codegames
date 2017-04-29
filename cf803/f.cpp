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

ll mod(ll x, ll m) { return ((x%m) + m) % m; }
ll add(ll a, ll b, ll m){return mod(mod(a,m)+mod(b,m),m);}
ll sub(ll a, ll b, ll m){return mod(mod(a,m)-mod(b,m),m);}
ll mul(ll a, ll b, ll m){return mod(mod(a,m)*mod(b,m),m);}

const ll N=100000;
int main()
{
    ll n=scan();
    VI c(N+1);
    rng(i,0,n){
        ll rd=scan();
        ++c[rd];
    }

    VI p(N+1);
    p[0]=1;
    rng(i,1,N+1){
        p[i]=mul(p[i-1],2,M);
    }

    VI g(N+1);
    rng(i,1,N+1){
        ll t=0;
        ll j=i;
        while(j<=N){
            t=add(t,c[j],M);
            j+=i;
        }
        g[i]=sub(p[t],1,M);
    }

    VI f(N+1);
    ll i=N;
    while(i>=1){
        f[i]=g[i];
        ll j=i*2;
        while(j<=N){
            f[i]=sub(f[i],f[j],M);
            j+=i;
        }
        --i;
    }
    cout<<f[1]<<endl;
    return 0;
}
