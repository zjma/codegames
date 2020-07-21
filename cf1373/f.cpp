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

void dumparr(ll n, ll arr[]){
    rng(i,0,n){
        cout<<arr[i]<<",";
    }
    cout<<endl;
}
//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

const int N=1000000;
ll psb[N];
ll psa[N];
ll a[N];
ll b[N];
ll n;
bool solve(){
    psb[0]=b[0];
    psa[0]=a[0];
    rng(i,1,n){
        psb[i]=psb[i-1]+b[i];
        psa[i]=psa[i-1]+a[i];
    }
    cout<<"a=";dumparr(n,a);
    cout<<"b=";dumparr(n,b);
    cout<<"psa=";dumparr(n,psa);
    cout<<"psb=";dumparr(n,psb);
    if (psb[n-1]<psa[n-1]){
        cout<<"The total is not enough."<<endl;
        return false;
    }

    ll ub=a[n-1];
    ub=min(ub,b[n-1]);
    cout<<"ub: bound="<<b[n-1]<<endl;
    rng(i,0,n-1){
        ll tmp=b[n-1]+psb[i]-psa[i];
        printf("ub: x+a[0]+...+a[%I64d] should <= b[n-1]+b[0]+...+b[%I64d]\n", i, i);
        printf("    i.e., x <= %I64d\n", tmp);
        ub=min(ub,tmp);
    }

    ll lb=0;
    rng(w,1,n){
        ll tmpa=psa[n-1]-psa[n-1-w];
        ll tmpb=psb[n-2]-((n-2-w>=0)?psb[n-2-w]:0);
        ll tmp=tmpa-tmpb;
        printf("lb: x+b[%I64d]+...+b[n-2] should >= a[%I64d]+...+a[n-1]\n", n-w-1, n-w);
        printf("    i.e., x >= %I64d\n", tmp);
        lb=max(lb,tmp);
    }

    cout<<"x should >="<<lb<<endl;
    cout<<"x should <="<<ub<<endl;
    return lb<=ub;
}

int main()
{
    ll TN=scan();
    rng(TI,0,TN){
        n=scan();
        rng(i,0,n){
            a[i]=scan();
        }
        rng(i,0,n){
            b[i]=scan();
        }
        string result=solve()?"YES":"NO";
        cout<<result<<endl;
    }
    return 0;
}
