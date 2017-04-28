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

ll solve(ll n, ll f){
    ll sqrtn=ll(sqrt(n));
    rng(i,f,sqrtn+1){
        if (n%i==0) return n/i;
    }
    ll ans=INF;
    rng(i,1,sqrtn+1){
        if (n%i==0){
            ll j=n/i;
            if (j>=f) ans=j;
        }
    }
    return n/ans;
}

int main()
{
    ll n=scan();
    ll k=scan();
    ll f=k*(k+1)/2;
    if (f>n){
        cout<<-1<<endl;
        return 0;
    }
    ll g=solve(n,f);cerr<<g<<endl;
    ll fs=n/g;
    rng(i,0,k-1){
        cout<<(g*(i+1))<<" ";
    }cout<<(g*(fs-k*(k-1)/2))<<endl;
    return 0;
}
