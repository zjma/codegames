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


ll dist(ll a, ll b){
    return (a<b)?(b-a):(a-b);
}

int main()
{
    ll n;scanll(n);
    ll girli;scanll(girli);--girli;
    ll money;scanll(money);
    VI a(n);
    rng(i,0,n){
        scanll(a[i]);
    }
    
    ll ansi=-1;
    rng(i,0,n){
        if (a[i]==0||a[i]>money) continue;
        if (ansi<0||dist(ansi,girli)>dist(i,girli)) ansi=i;
    }
    cout<<(dist(ansi,girli)*10)<<endl;
    return 0;
}
