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

inline ll mod(ll x) { return ((x%M) + M) % M; }
inline ll add(ll a, ll b){return mod(mod(a)+mod(b));}
inline ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
inline ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

const ll N=1000000;

ll pow2[N+1];
bool isnotprime[N+1];
ll prime[N+1];
ll pn;
bool pr[N+1];
ll pc[N+1];
ll b[N+1];
ll c[N+1];
ll g[N+1];
ll f[N+1];

int main()
{
    // VI pow2(N+1);
    pow2[0]=1;
    rng(i,1,N+1){
        pow2[i]=mul(pow2[i-1],2);
    }

    // VI isnotprime(N+1, 1);
    // VI prime;
    isnotprime[0]=isnotprime[1]=1;
    rng(i,2,N+1){
        if (!isnotprime[i]){
            prime[pn++]=i;
            for(ll j=i*i;j<=N;j+=i){
                isnotprime[j]=1;
            }
        }
    }
    // ll pn=prime.size();

    // VI pr(N+1);
    // VI pc(N+1);
    pr[1]=true;
    pc[1]=0;
    rng(i,0,pn){
        ll j=1;
        ll jj=prime[i];
        while(jj<=N){
            if (pr[j]){
                pr[jj]=true;
                pc[jj]=pc[j]+1;
            }
            ++j;
            jj+=prime[i];
        }
    }

    // VI b(N+1);
    ll n=scan();
    rng(i,0,n){
        ll x=scan();
        ++b[x];
    }

    // VI c(N+1);
    rng(i,2,N+1){
        for(ll j=i;j<=N;j+=i){
            c[i]+=b[j];
        }
    }

    // VI g(N+1);
    rng(i,1,N+1){
        g[i]=mul(c[i],pow2[c[i]-1]);
    }

    // VI f(N+1);
    rng(i,2,N+1){
        f[i]=g[i];
        for(ll j=2;j*i<=N;++j){
            if (pr[j]){
                if (pc[j]%2==0){
                    f[i]=add(f[i],g[j*i]);
                }else{
                    f[i]=sub(f[i],g[j*i]);
                }
            }
        }
    }

    ll ans=0;
    rng(i,2,N+1){
        ans=add(ans,mul(i,f[i]));
    }

    cout<<ans<<endl;
    return 0;
}
