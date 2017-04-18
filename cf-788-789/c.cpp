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
const DOUBLE EPS=1e-9;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


ll calc(vector<ll> &d){
    ll n=d.size();
    ll ret=d[0];
    ll acc=0;
    rng(i,0,n){
        acc+=d[i];
        ret=max(ret,acc);
        if (acc<0) acc=0;
    }
    return ret;
}

int main()
{
    ll n;scanll(n);
    vector<ll> a(n);
    rng(i,0,n){
        scanll(a[i]);
    }
    vector<ll> d(n-1);
    rng(i,0,n-1){
        d[i]=a[i]-a[i+1];
        if (d[i]<0) d[i]=-d[i];
    }
    rng(i,0,n-1){
        if (i%2) d[i]=-d[i];
    }
    ll ans=calc(d);
    rng(i,0,n-1){
        d[i]=-d[i];
    }
    ans=max(ans,calc(d));
    cout<<ans<<endl;
    return 0;
}
