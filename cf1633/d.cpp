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

ll arrmax(VI &a){
    ll r=-INF;
    rng(i,0,a.size()){
        r=max(r,a[i]);
    }
    return r;
}

VI dis(1001,INF);

ll work(){
    ll n=scan(), k=scan();
    ll k2=n*12;
    ll ak=min(k,k2);
    VI B(n), C(n);
    rng(i,0,n) B[i]=scan();
    rng(i,0,n) C[i]=scan();
    VI cost(n);
    rng(i,0,n){
        cost[i]=dis[B[i]];
    }
    VI f(ak+1,-INF);
    f[0]=0;
    rng(i,0,n){
        for(ll j=ak;j>=0;j--){
            ll lbidx=j-cost[i];
            if (lbidx>=0&&f[lbidx]!=-INF)
                f[j]=max(f[j],f[lbidx]+C[i]);
        }
    }
    return arrmax(f);
}

int main()
{
    dis[0]=0;
    dis[1]=0;
    rng(i,1,1001){
        rng(j,1,i+1){
            ll x=i+i/j;
            if (x<=1000) dis[x]=min(dis[x],dis[i]+1);
        }
    }
    ll tn=scan();
    rng(ti,0,tn){
        cout<<work()<<endl;
    }
    return 0;
}
