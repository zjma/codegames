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

ll gcd(ll a, ll b) { for (;b>0;swap(a, b))a %= b;return a; }

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan();
    }
    ll g=a[0];
    rng(i,1,n){
        g=gcd(g,a[i]);
    }
    if (g>1){
        cout<<"YES"<<endl<<0<<endl;
        return 0;
    }
    rng(i,0,n){
        a[i]%=2;
    }
    VI segs;
    ll acc=0;
    rng(i,0,n){
        acc+=a[i];
        if (a[i]==1&&(i+1==n||a[i+1]==0)){
            segs.push_back(acc);
            acc=0;
        }
    }
    ll ans=0;
    ll sn=segs.size();
    for(auto seg:segs){
        ans+=(seg%2==0)?(seg/2):(2+seg/2);
    }
    cout<<"YES"<<endl<<ans<<endl;
    return 0;
}
