#include <message.h>
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
#include "asteroids.h"
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

ll max3(ll a, ll b, ll c){
    return max(max(a,b),c);
}

ll add(ll a, ll b){return (a==-INF||b==-INF)?-INF:(a+b);}

ll ME=0;
ll NODES=0;

/**
 * Distribute segment [0,n-1] to nodes [0,NODES-1] almost uniformly.
 *
 * Example 1: n=12,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-2     3-5     6-7     8-9     10-11
 * segsize  3       3       2       2       2
 *
 * Example 2: n=3,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-0     1-1     2-2     3-2     3-2
 * segsize  1       1       1       0       0
 *
 * Example 3: n=10,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-1     2-3     4-5     6-7     8-9
 * segsize  2       2       2       2       2
 *
 */
pair<ll,ll> get_interval(ll NODES, ll ME, ll n) {
    ll n2=n%NODES;
    ll n1=NODES-n2;
    ll l1=n/NODES;
    ll l2=l1+1;
    ll L,R;
    if (ME<n2){
        L=l2*ME;
        R=L+l2-1;
    }else{
        L=l2*n2+l1*(ME-n2);
        R=L+l1-1;
    }
    return make_pair(L,R);
}

ll parseChar(char c){
    return (c=='#')?(-INF):(c-48);
}

int main()
{
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll rn=GetHeight()+1;
    ll cn=GetWidth()+2;
    ll L,R;tie(L,R)=get_interval(NODES,ME,cn);

    if (ME>=1) return 0;
    VVI a(rn,VI(cn));
    rng(i,0,rn-1){
        rng(j,0,cn){
            a[i][j]=(j==0||j==cn-1)?(-INF):parseChar(GetPosition(i,j-1));
        }
    }

    VVI f(rn,VI(cn));
    rng(j,0,cn){
        f[0][j]=a[0][j];
    }
    rng(i,1,rn){
        f[i][0]=f[i][cn-1]=-INF;
        rng(j,1,cn-1){
            f[i][j]=add(max3(add(f[i-1][j-1],a[i-1][j]),f[i-1][j],add(f[i-1][j+1],a[i-1][j])),a[i][j]);
        }
    }
    ll ans=-INF;
    rng(j,0,cn){
        ans=max(ans,f[rn-1][j]);
    }
    ans=max(ans,-1LL);
    cout<<ans<<endl;
    return 0;
}
