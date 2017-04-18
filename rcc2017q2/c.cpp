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
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll n;scanll(n);
        VI a(n);
        VI ki(n,-1);
        VI lkhead;
        VI lktail;
        VI lklen;
        rng(i,0,n){
            scanll(a[i]);
            a[i]--;
        }
        rng(i,0,n){
            if (a[i]==-1) continue;
            ll l0=ki[i];
            ll l1=ki[a[i]];

        }

        cout<<ans<<endl;

    }
    return 0;
}
