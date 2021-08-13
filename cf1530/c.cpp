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

ll calcTotal(ll x){
    ll d=(x-1)/3;
    return x+d;
}

const ll N=100000;
ll psa[N+1];
ll psb[N+1];
ll n;
ll me(ll k) {
    ll needed=k-k/4;
    ll g100=k-n;
    ll oldNeeded=max(0ll,needed-g100);
    ll newNeeded=needed-oldNeeded;
    return psa[oldNeeded]+100*newNeeded;
}
ll fr(ll k) {
    ll needed=k-k/4;
    ll oldNeeded=min(n,needed);
    ll newNeeded=needed-oldNeeded;
    return psb[oldNeeded]+0*newNeeded;
}

ll work(){
    n=scan();
    VI A(n);
    VI B(n);
    rng(i,0,n){
        A[i]=scan();
    }
    rng(i,0,n){
        B[i]=scan();
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    psa[0]=psb[0]=0;
    rng(i,0,n){
        psa[i+1]=psa[i]+A[n-1-i];
        psb[i+1]=psb[i]+B[n-1-i];
    }
    ll l=-1,r=5*n;
    while(l+1<r){
        ll m=(l+r)/2;
        if (me(n+m)>=fr(n+m)) {
            r=m;
        }else{
            l=m;
        }
    }
    return r;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll ans=work();
        cout<<ans<<endl;
    }
    return 0;
}
