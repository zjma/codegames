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

ll rec[180001];
ll b10[]={1,10,100,1000,10000,100000,1000000,10000000};

bool dfs(ll ori, ll d, ll val, ll sum, ll hand){
    if (d==0){
        if (sum==ori) return false;
        if (rec[sum]) return true;
        return false;
    }
    ll digit=val/b10[d];
    if (dfs(ori,d-1,val-digit*b10[d],sum))
}
const ll N=200000;
char buf[N+1];
int main()
{
    ll n=scan();
    scanstr(buf);
    
    return 0;
}
