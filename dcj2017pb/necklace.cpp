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
#include "necklace.h"
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

ll findnextsince(const VI &arr, ll geq){
    ll L=-1,R=arr.size();
    while (L+1<R){
        ll M=(L+R)/2;
        if (arr[M]>=geq){
            R=M;
        }else{
            L=M;
        }
    }
    if (R==arr.size()) return -1;
    return arr[R];
}

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll msglen=GetMessageLength();
    ll lacelen=GetNecklaceLength();
    ll L,R;tie(L,R)=get_interval(NODES,ME,lacelen);
    if (L>R) return 0;
    ll VNODES=min(NODES,lacelen);

    VI msg(msglen);
    rng(i,0,msglen){
        msg[i]=GetMessageElement(i);
    }
    VVI occ(10001);
    rng(i,L,R+1){
        ll c=GetNecklaceElement(i);
        occ[c].push_back(i);
    }

    VI local(msglen);
    rng(i,0,msglen){
        ll ci=i;
        ll since=L;
        while(ci<msglen){
            ll loc=findnextsince(occ[msg[ci]],since);
            if (loc<0) break;
            ++ci;
            since=loc+1;
        }
        local[i]=ci-i;
    }

    rng(i,0,msglen){
        PutLL(0,local[i]);
    }
    Send(0);

    if (ME==0){
        VVI sub(VNODES,VI(msglen));
        rng(i,0,VNODES){
            Receive(i);
            rng(j,0,msglen){
                sub[i][j]=GetLL(i);
            }
        }
        ll ans=0;
        rng(i,0,msglen){
            ll pos=i;
            rng(j,0,VNODES){
                pos+=sub[j][pos];
                if (pos==msglen) break;
            }
            ans=max(ans,pos-i);
        }
        cout<<ans<<endl;
    }
    return 0;
}
