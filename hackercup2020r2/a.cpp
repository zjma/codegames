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

void readArr(VI &arr, ll n, ll k){
    rng(i,0,k){
        arr[i]=scan();
    }
    ll a=scan();
    ll b=scan();
    ll c=scan();
    ll d=scan();
    rng(i,k,n){
        arr[i]=(a*arr[i-2]+b*arr[i-1]+c)%d;
    }
}

ll sum(VI &arr){
    ll ans=0;
    for(auto x:arr) ans+=x;
    return ans;
}

ll solve(ll n, VI &S, VI &X, VI &Y){
    VI Hi(n);rng(i,0,n){Hi[i]=X[i]+Y[i];}
    ll minRequired=sum(X);
    ll maxSupported=sum(Hi);
    ll total=sum(S);
    if (total<minRequired||total>maxSupported) return -1;
    VI moveAway(n);rng(i,0,n){moveAway[i]=max(0LL,S[i]-Hi[i]);}
    VI moveIn(n);rng(i,0,n){moveIn[i]=max(0LL,X[i]-S[i]);}
    ll moveAwayTotal=sum(moveAway);
    ll moveInTotal=sum(moveIn);
    return max(moveAwayTotal,moveInTotal);
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll k=scan();
        VI S(n);
        VI X(n);
        VI Y(n);
        readArr(S,n,k);
        readArr(X,n,k);
        readArr(Y,n,k);
        ll ans=solve(n,S,X,Y);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
