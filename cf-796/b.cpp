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



int main()
{
    ll n;scanll(n);
    ll m;scanll(m);
    ll k;scanll(k);
    VI hole(n);
    rng(i,0,m){
        ll x;scanll(x);--x;
        hole[x]=1;
    }
    ll p=0;
    rng(i,0,k){
        ll x,y;scanll(x);scanll(y);--x;--y;
        if (hole[p]==1) continue;
        if (p==x){
            p=y;
        }else if(p==y){
            p=x;
        }
    }
    cout<<p+1<<endl;
    return 0;
}
