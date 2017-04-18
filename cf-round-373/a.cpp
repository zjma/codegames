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
    ll n;
    scanll(n);
    vector<ll> a(n);
    rng(i,0,n){
        scanll(a[i]);
    }
    string ans;
    if (n==1){
        ans=(a[0]==15)?"DOWN":(a[0]==0)?"UP":"-1";
    }else{
        ans=(a[n-1]==15)?"DOWN":(a[n-1]==0)?"UP":(a[n-2]<a[n-1])?"UP":"DOWN";
    }
    cout<<ans<<endl;
    return 0;
}
