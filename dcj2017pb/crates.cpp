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
#include "crates.h"
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
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

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

VI adiv;
VI adiv_acc;
VI tdiv;
VI tdiv_acc;

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll n=GetNumStacks();
    ll L,R;tie(L,R)=get_interval(NODES,ME,n);
    if (L>R) return 0;
    ll VNODES=min(n,NODES);

    VI a(R-L+1);
    ll subtot=0;
    rng(i,L,R+1){
        a[i-L]=GetStackHeight(i+1);
        subtot+=a[i-L];
    }
    PutLL(0,subtot);
    Send(0);

    if (ME==0){
        adiv.resize(VNODES);
        adiv_acc.resize(VNODES);
        rng(i,0,VNODES){
            Receive(i);
            adiv[i]=GetLL(i);
            adiv_acc[i]=(i==0)?adiv[i]:(adiv_acc[i-1]+adiv[i]);
        }
        rng(i,0,VNODES){
            PutLL(i,adiv_acc[VNODES-1]);
            Send(i);
        }
    }

    Receive(0);
    ll tot=GetLL(0);
    ll n0=tot%n;
    ll base=tot/n;
    ll lift=max(0LL,min(n0-L,R-L+1));
    ll tsubtot=base*(R-L+1)+lift;
    PutLL(0,tsubtot);
    Send(0);

    rng(i,L,R+1){
        ll ti=(i<n0)?(base+1):base;
        a[i-L]=ti-a[i-L];
    }

    if (ME==0){
        tdiv.resize(VNODES);
        tdiv_acc.resize(VNODES);
        rng(i,0,VNODES){
            Receive(i);
            tdiv[i]=GetLL(i);
            tdiv_acc[i]=(i==0)?tdiv[i]:(tdiv_acc[i-1]+tdiv[i]);
        }
        rng(i,1,VNODES){
            PutLL(i,tdiv_acc[i-1]-adiv_acc[i-1]);
            Send(i);
        }
    }

    ll ans=0;
    ll prevstillneed=0;
    if (ME){
        Receive(0);
        prevstillneed=GetLL(0);
    }
    rng(i,L,R+1){
        ans=add(ans,max(0LL,prevstillneed));
        ll crtneed=a[i-L]+prevstillneed;
        ans=add(ans,max(0LL,-crtneed));
        prevstillneed=crtneed;
    }
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll ans=0;
        rng(i,0,VNODES){
            Receive(i);
            ans=add(ans,GetLL(i));
        }
        cout<<ans<<endl;
    }
    return 0;
}
