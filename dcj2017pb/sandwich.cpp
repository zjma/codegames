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
#include "sandwich.h"
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

ll ME=0;
ll NODES=0;
void INIT() {ME=MyNodeId();NODES=NumberOfNodes();}

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
pair<ll,ll> get_my_inverval(ll n) {
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

int main()
{
    srand(time(NULL));
    INIT();
    ll n=GetN();
    ll L,R;tie(L,R)=get_my_inverval(n);
    if (L>R) return 0;
    NODES=min(NODES,n);

    VI a(R-L+1);
    VI f(R-L+1);
    ll s=0;
    rng(i,L,R+1){
        a[i-L]=GetTaste(i);
        s+=a[i-L];
    }

    ll pre=INF;
    if (ME>=1){
        Receive(ME-1);
        pre=GetLL(ME-1);
    }
    rng(i,L,R+1){
        f[i-L]=min(a[i-L],pre+a[i-L]);
        pre=f[i-L];
    }
    ll ans=f[0];
    rng(i,L,R+1) ans=min(ans,f[i-L]);

    if (ME<NODES-1){
        PutLL(ME+1,f[R-L]);
        Send(ME+1);
    }

    PutLL(0,s);
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll sum=0;
        ll ans=0;
        rng(i,0,NODES){
            Receive(i);
            sum+=GetLL(i);
            ans=min(ans,GetLL(i));
        }
        cout<<(sum-ans)<<endl;
    }
    return 0;
}
