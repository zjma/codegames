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

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

ll work(){
    ll n=scan();
    ll m=scan();
    ll k=scan();
    ll q=scan();
    VI X(q),Y(q);
    rng(i,0,q){
        X[i]=scan()-1;
        Y[i]=scan()-1;
    }
    ll ans=1;
    unordered_set<ll> OR;
    unordered_set<ll> OC;
    rng(i,0,q){
        ll j=q-1-i;
        if((OR.find(X[j])==OR.end()||OC.find(Y[j])==OC.end())&&OR.size()<n&&OC.size()<m){
            ans=mul(ans,k);
        }
        OR.insert(X[j]);
        OC.insert(Y[j]);
    }
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll ans=work();
        printf("%lld\n",ans);
    }
    return 0;
}
