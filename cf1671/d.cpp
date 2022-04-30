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
ll min3(ll a, ll b, ll c){
    return min(a,min(b,c));
}
ll work(){
    ll n=scan();
    ll x=scan();
    VI A(n);
    ll minA=INF;
    ll maxA=-INF;
    ll base=0;
    rng(i,0,n){
        A[i]=scan();
        if (i>=1) base+=abs(A[i]-A[i-1]);
        minA=min(minA,A[i]);
        maxA=max(maxA,A[i]);
    }
    ll minextra=(minA<=1)?0:min3(A[0]-1,A[n-1]-1,(minA-1)*2);
    ll maxextra=(maxA>=x)?0:min3(x-A[0],x-A[n-1],(x-maxA)*2);
    ll ans=base+minextra+maxextra;
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        cout<<work()<<endl;
    }
    return 0;
}
