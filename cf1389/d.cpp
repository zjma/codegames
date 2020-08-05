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

ll solve(ll n, ll k, ll al0, ll ar0, ll bl0, ll br0){
    ll ans=INF;
    ll minr=min(ar0,br0);
    ll maxr=max(ar0,br0);
    ll minl=min(al0,bl0);
    ll maxl=max(al0,bl0);
    ll initial_shared=max(0ll,minr-maxl);
    ll eventual_shared=maxr-minl;
    ll cap_shared=eventual_shared-initial_shared;
    ll initial_gap=max(0ll,eventual_shared-(ar0-al0)-(br0-bl0));
    ll k1=k-initial_shared*n;
    if (k1<=0) return 0;
    rng(vcount,1,n+1){
        ll cost1=(k1<=vcount*cap_shared)?k1:(k1+k1-vcount*cap_shared);
        ll cost=initial_gap*vcount+cost1;
        ans=min(ans,cost);
    }
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll k=scan();
        ll al=scan();
        ll ar=scan();
        ll bl=scan();
        ll br=scan();
        cout<<solve(n,k,al,ar,bl,br)<<endl;
    }
    return 0;
}
