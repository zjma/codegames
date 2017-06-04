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
#include "gas_stations.h"
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

ll log2ceil(ll x){
    ll ret=0;
    while(1){
        if ((1<<(1+ret))>x) return ret;
        ++ret;
    }
}

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll N=GetNumKms();
    ll T=GetTankSize();
    ll L,R;tie(L,R)=get_interval(NODES,ME,N);
    if (L>R) return 0;
    ll VNODES=min(NODES,N);

    VI regL(VNODES);
    VI regR(VNODES);
    rng(ni,0,VNODES) tie(regL[ni],regR[ni])=get_interval(NODES,ni,N);

    VI Lstation0(VNODES);
    VI Rstation0(VNODES);
    rng(i,0,VNODES){
        Lstation0[i]=max(0LL,regL[i]-T+1);
        Rstation0[i]=max(0LL,regR[i]-T+1);
    }

    VI cmmfirst(VNODES);
    VI cmmlast(VNODES);
    rng(i,0,VNODES){
        cmmfirst[i]=Rstation0[i];
        cmmlast[i]=regL[i]-1;
    }
    VI cmmblk_first(VNODES);
    rng(i,0,VNODES){
        ll j=0;
        while(j<i){
            if (cmmfirst[i]<=regL[j]&&regR[j]<=cmmlast[i]){
                break;
            }
            ++j;
        }
        cmmblk_first[i]=j;
    }
    VI a(R-L+1);
    ll submin=INF;
    rng(i,L,R+1) {
        a[i-L]=GetGasPrice(i);
        submin=min(submin,a[i-L]);
    }
    PutLL(0,submin);
    Send(0);

    if (ME==0){
        VI sub(VNODES);
        rng(i,0,VNODES){
            Receive(i);
            sub[i]=GetLL(i);
        }
        VI cmm(VNODES,INF);
        rng(i,0,VNODES){
            ll j=cmmblk_first[i];
            while(1){
                if (j>=i) break;
                cmm[i]=min(cmm[i],sub[j]);
                ++j;
            }
        }
        rng(i,0,VNODES){
            PutLL(i,cmm[i]);
            Send(i);
        }
    }

    Receive(0);
    ll mycmm=GetLL(0);
    ll ans=0;
    deque<pair<ll,ll>> q;
    rng(i,Lstation0[ME],regL[cmmblk_first[ME]]){
        ll a0i=GetGasPrice(i);
        while(1){
            if (q.empty()) break;
            ll price,idx;tie(price,idx)=q.back();
            if (price<a0i) break;
            q.pop_back();
        }
        q.emplace_back(a0i,i);
    }
    rng(i,L,R+1){
        ll earliest=max(0LL,i-T+1);
        while(1){
            if (q.empty()) break;
            ll price,idx;tie(price,idx)=q.front();
            if (idx>=earliest) break;
            q.pop_front();
        }
        while(1){
            if (q.empty()) break;
            ll price,idx;tie(price,idx)=q.back();
            if (price<a[i-L]) break;
            q.pop_back();
        }
        q.emplace_back(a[i-L],i);

        ll sel=min(q.front().first,mycmm);
        ans+=sel;
    }
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll ans=0;
        rng(i,0,VNODES){
            Receive(i);
            ans+=GetLL(i);
        }
        cout<<ans<<endl;
    }
    return 0;
}
