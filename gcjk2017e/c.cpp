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
    ll tn=scan();
    rng(ti,0,tn){
        ll x0,y0,z0,x1,y1,z1,x2,y2,z2;
        cin>>x0>>y0>>z0>>x1>>y1>>z1>>x2>>y2>>z2;
        assert(y0==0);
        assert(z0==0);
        assert(y1==0);
        assert(z1==0);
        assert(y2==0);
        assert(z2==0);
        ll xl=min(x0,min(x1,x2));
        ll xr=max(x0,max(x1,x2));
        double ans=(xr-xl)/6.;
        printf("Case #%lld: %.9f\n",ti+1,ans);
    }
    return 0;
}
