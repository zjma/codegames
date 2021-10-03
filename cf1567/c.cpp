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

ll v[10];
ll dfs(ll cur, ll n){
    if (cur==n) return 1;
    ll dmax=min(9ll,v[cur]);
    ll dmin=max(0ll,v[cur]-9);
    ll ansNotCarriedTo=dfs(cur+1,n)*(dmax-dmin+1);
    ll ansCarriedTo=0;
    if (v[cur]>=1&&cur+2<n){
        v[cur+2]+=10;
        v[cur]--;
        ll dmax2=min(9ll,v[cur]);
        ll dmin2=max(0ll,v[cur]-9);
        ansCarriedTo=dfs(cur+1,n)*(dmax2-dmin2+1);
        v[cur+2]-=10;
        v[cur]++;
    }
    ll ans=ansNotCarriedTo+ansCarriedTo;
    return ans;
}

char buf[20];
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        scanstr(buf);
        ll n=0;
        for(;buf[n]!=0;n++){
            v[n]=buf[n]-48;
        }
        ll ans=dfs(0,n)-2;
        cout<<ans<<endl;
    }
    return 0;
}
