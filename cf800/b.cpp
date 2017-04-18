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
using namespace std;


//type shortcuts
typedef long long ll;
typedef vector<ll> VI;
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;


//constants
const DOUBLE EPS=1e-6;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

#define sqr(x) ((x)*(x))
//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


double p2l(ll x, ll y, ll x1, ll y1, ll x2, ll y2){
    ll a=abs(x*y1-x1*y+x1*y2-x2*y1+x2*y-x*y2);
    double bot=sqrt(sqr(x1-x2)+sqr(y1-y2));
    return a/bot;
}

int main()
{
    ll n;scanll(n);
    VI x(n);
    VI y(n);
    rng(i,0,n){
        scanll(x[i]);scanll(y[i]);
    }
    vector<double> d(n);
    rng(i,0,n){
        ll xx=x[i],yy=y[i];
        ll nxx=x[(i+1)%n],nyy=y[(i+1)%n];
        ll pxx=x[(i+n-1)%n],pyy=y[(i+n-1)%n];
        double can0=p2l(xx,yy,nxx,nyy,pxx,pyy);
        d[i]=can0/2;
    }
    double ans=d[0];
    rng(i,1,n){
        ans=min(ans,d[i]);
    }
    rng(i,0,n){
        rng(j,i+1,n){
            double dis=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
            ans=min(ans,dis/2);
        }
    }
    cout.precision(9);
    cout<<fixed<<ans<<endl;
    return 0;
}
