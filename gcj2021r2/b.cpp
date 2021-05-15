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

ll v[1000001];
ll g[1000001];

ll f(ll x){
    if (v[x]==-1){
        if (x<=1){
            v[x]=-INF;
        }else{
            v[x]=1;
            ll k0=2;
            while (k0*k0<=x){
                if (x%k0==0){
                    v[x]=max(v[x],f(k0-1)+1);
                    v[x]=max(v[x],f(x/k0-1)+1);
                }
                k0+=1;
            }
        }
    }
    return v[x];
}

int main()
{
    rng(i,1,1000001){
        v[i]=-1;
    }
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll k0=3;
        ll ans=1;
        while(k0*k0<=n){
            if (n%k0==0){
                ans=max(ans,f(k0-1)+1);
                ans=max(ans,f(n/k0-1)+1);
            }
            k0++;
        }
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
