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


ll solve(VI&A){
    ll n=A.size();
    VVI f(n,VI(n));
    VI prev(n,-1);
    map<ll,ll> v2lastocc;
    rng(i,0,n){
        prev[i]=v2lastocc[A[i]]-1;
        v2lastocc[A[i]]=i+1;
    }
    rng(w,0,n){
        rng(i,0,n-w){
            ll j=i+w;
            f[i][j]=(i==j)?0:f[i][j-1];
            for(ll k=prev[j];k>=i;k=prev[k]){
                f[i][j]=max(f[i][j],f[i][k]+f[k+1][j-1]+1);
            }
        }
    }
    return n-1-f[0][n-1];
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI A(n);
        rng(i,0,n) A[i]=scan();
        ll ans=solve(A);
        cout<<ans<<endl;
    }
    return 0;
}


// dp[i][j]=dp[i+1][j] / 1+dp[i+1][k-1]+dp[k][j]
// j-i-dp[i][j]=(j-i-1-dp[i+1][j])+1
//             or k-i-2-dp[i+1][k-1]+j-k-dp[k][j]+2
//
//
// dp[i][j][k]=dp[i][j-1][k]+(raw[j]==raw[j-1])?0:(raw[j]==k)?0:1
