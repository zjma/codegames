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

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan();
    }

    VI smin(n+1);

    VVI f(2,VI(n+1,INF));
    ll imax=min(n,a[0]);
    rng(i,0,imax) f[1][i]=i+1;
    if (a[0]<=imax) f[1][a[0]]=a[0];

    rng(i,2,n+1){
        ll ii=i%2;
        ll cand0=INF;
        smin[0]=INF;
        rng(j,0,n)
            smin[j+1]=min(smin[j],f[1-ii][n-j]);

        rng(j,0,n+1){
            cand0=min(cand0+1,f[1-ii][j]);
            ll cand1=smin[n-j];
            ll extra=(j>=a[i-1])?0:1;
            f[ii][j]=(j>a[i-1])?INF:(min(cand0,cand1)+extra);
        }
    }
    ll ans=INF;
    rng(i,0,n+1){
        ans=min(ans,f[n%2][i]);
    }
    cout<<ans<<endl;
    return 0;
}
