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

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan();
    }
    VI l(n);
    VI r(n);
    rng(i,0,n){
        ll j=n-1-i;
        l[i]=(a[i]==0)?0:(i==0)?INF:(l[i-1]+1);
        r[j]=(a[j]==0)?0:(j==n-1)?INF:(r[j+1]+1);
    }

    rng(i,0,n){
        ll v=min(l[i],r[i]);
        cout<<v<<" ";
    }cout<<endl;
    return 0;
}
