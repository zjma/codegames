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

ll val(VI &B, VI &mask){
    ll w=B.size();
    ll ans=0;
    rng(i,0,w){
        ans+=(1<<B[i])*(1-mask[i]);
    }
    return ans;
}

ll len(ll x){
    ll ans=0;
    while(x>0){
        x/=2;
        ans++;
    }
    return max(ans,1LL);
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll m=scan();
        if (m<n) {
            cout<<0<<endl;
            continue;
        }
        ll w=max(len(n),len(m));
        ll MASK=(1<<w)-1;
        ll n2=MASK^n;
        ll aborted=0;
        ll ans=0;
        rng(i,0,w){
            ll idx=w-1-i;
            if ((n2&(1<<idx))>0){
                ans+=(1<<idx);
                if (ans<=m) continue;
                ans-=(1<<idx);
                if (ans<=m) continue;
                aborted=1;
                break;
            }
        }
        if (aborted) cout<<0<<endl; else cout<<ans<<endl;
    }
    return 0;
}
