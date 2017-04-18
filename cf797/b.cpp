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


int main()
{
    ll n;scanll(n);
    VI a(n);
    rng(i,0,n){
        scanll(a[i]);
    }
    VI f(n);
    VI g(n);
    if (a[0]%2==0){
        f[0]=-999999999999999;
        g[0]=a[0];
    }else{
        f[0]=a[0];
        g[0]=-999999999999999;
    }
    rng(i,1,n){
        if (a[i]%2!=0){
            f[i]=max(a[i],max(g[i-1]+a[i],f[i-1]));
            g[i]=max(g[i-1],f[i-1]+a[i]);
        }else{
            f[i]=max(f[i-1]+a[i],f[i-1]);
            g[i]=max(a[i],max(g[i-1]+a[i],g[i-1]));
        }
    }
    cout<<f[n-1]<<endl;
    return 0;
}
