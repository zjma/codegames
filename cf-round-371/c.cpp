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
void scanll(ll &x) {int r;scanf("%d",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


char b[10];

ll r2v(ll x){
    ll ret=0;
    ll b=1;
    rng(i,0,18){
        ll d=x%10;
        x/=10;
        ret+=(d%2)*b;
        b*=2;
    }
    return ret;
}

int main()
{
    map<ll,ll> v2c;
    ll t;scanll(t);
    ll x;
    rng(i,0,t){
        scanstr(b);
        scanll(x);
        switch(b[0]){
            case '+':
                ++v2c[r2v(x)];
                break;
            case '-':
                --v2c[r2v(x)];
                break;
            case '?':
                printf("%lld\n", v2c[r2v(x)]);
                break;
        }
    }
    return 0;
}
