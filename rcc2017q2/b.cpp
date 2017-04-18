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


ll gcd(ll a, ll b){
    if (b==0) return a;
    return gcd(b,a%b);
}

ll lcm(ll a, ll b){
    return a*b/gcd(a,b);
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll a,b,c,d;
        scanll(a);
        scanll(b);
        scanll(c);
        scanll(d);
        ll x=lcm(a,c);
        ll y=gcd(b,d);
        ll z=gcd(x,y);
        cout<<x/z<<' '<<y/z<<endl;
    }
    return 0;
}
