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
ll const N=200000;
ll f[N];
int main()
{
    ll n=scan();
    ll m=scan();
    ll ans=n;
    rng(i,0,m){
        ll u=scan()-1;
        ll v=scan()-1;
        if (u>v) swap(u,v);
        f[u]++;
        if (f[u]==1){
            ans--;
        }
    }
    ll qn=scan();
    rng(i,0,qn){
        ll cmd=scan();
        if (cmd==3){
            cout<<ans<<endl;
        }else{
            ll u=scan()-1;
            ll v=scan()-1;
            if (u>v) swap(u,v);
            if (cmd==1){
                f[u]++;
                if (f[u]==1){
                    ans--;
                }
            }else{
                f[u]--;
                if (f[u]==0){
                    ans++;
                }
            }
        }
    }
    return 0;
}
