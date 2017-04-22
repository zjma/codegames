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

string solve(ll r, ll y, ll b, ll ry, ll yb, ll rb){
    if (yb>r||rb>y||ry>b) return "IMPOSSIBLE";
    if (ry==b){
        if (r||y||rb||yb) return "IMPOSSIBLE";
        string ret;
        rng(i,0,b){
            ret+="OB";
        }
        return ret;
    }
    ll newa=a-2*
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll n;scanll(n);
        ll a;scanll(a);
        ll ab;scanll(ab);
        ll b;scanll(b);
        ll bc;scanll(bc);
        ll c;scanll(c);
        ll ca;scanll(ca);

    }
    return 0;
}
