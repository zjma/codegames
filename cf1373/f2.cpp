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
ll a[N];
ll b[N];
ll n;

ll check(ll mm){
    ll carried=mm;
    rng(i,0,n){
        ll stillNeeded=max(0LL,a[i]-carried);
        if (stillNeeded>b[i]) return -1;
        carried=b[i]-stillNeeded;
    }
    if (carried<mm) return 1;
    return 0;
}

bool solve(){
    ll lo=-1;
    ll hi=min(b[n-1],a[0])+1;
    while(lo+1<hi){
        ll mm=(lo+hi)/2;
        ll cur=check(mm);
        switch(cur){
            case 0:
                return true;
            case -1:
                lo=mm;
                break;
            case 1:
                hi=mm;
                break;
        }
    }
    return false;
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
