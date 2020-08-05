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

ll solve(ll n, VI &a, ll k, ll z){
    VVI fr(k+1,VI(z+1,-INF));
    VVI fl(k+1,VI(z+1,-INF));
    fr[0][0]=fl[0][0]=a[0];
    rng(x,1,k+1){
        rng(y,0,z+1){
            ll cur=x-y-y;
            if (cur<0) continue;
            fr[x][y]=max(fr[x-1][y],fl[x-1][y])+a[cur];
            if (y>=1) fl[x][y]=fr[x-1][y-1]+a[cur];
        }
    }
    ll ans=0;
    rng(y,0,z+1){
        ans=max(ans,max(fr[k][y],fl[k][y]));
    }
    return ans;
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll k=scan();
        ll z=scan();
        VI a(n);
        rng(i,0,n){
            a[i]=scan();
        }
        cout<<solve(n,a,k,z)<<endl;
    }
    return 0;
}
