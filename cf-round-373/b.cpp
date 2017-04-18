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

const int N=100001;
char b[N];
int main()
{
    ll n;
    scanll(n);
    scanstr(b);
    ll r2b1=0,b2r1=0,r2b2=0,b2r2=0;
    rng(i,0,n){
        if (i%2==0 && b[i]=='r') r2b1++;
        if (i%2==1 && b[i]=='r') r2b2++;
        if (i%2==1 && b[i]=='b') b2r1++;
        if (i%2==0 && b[i]=='b') b2r2++;
    }
    ll ans1=max(r2b1,b2r1);
    ll ans2=max(r2b2,b2r2);
    ll ans=min(ans1,ans2);
    cout<<ans<<endl;
    return 0;
}
