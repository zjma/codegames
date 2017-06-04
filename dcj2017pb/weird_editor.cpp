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
#include "weird_editor.h"
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
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
ll power(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}
ll ones(ll len){
    if (len==0) return 0;
    if (len%2==0){
        ll tmp=ones(len/2);
        return add(mul(tmp,power(10,len/2)),tmp);
    }
    return add(mul(ones(len-1),10),1);
}

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

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll n=GetNumberLength();
    ll L,R;tie(L,R)=get_interval(NODES,ME,n);
    if (L>R) return 0;
    ll VNODES=min(NODES,n);
    VI d(R-L+1);
    rng(i,L,R+1){
        d[i-L]=GetDigit(i);
    }
    ll search_start=0;
    ll ans=0;
    ll digits_appended=0;
    rng(ri,0,9){
        ll digit_focused=9-ri;
        if (ME==0){
            rng(ni,0,VNODES){
                PutLL(ni,search_start);
                Send(ni);
            }
        }

        Receive(0);
        search_start=GetLL(0);
        ll ctr=0;
        ll last_appear_local=-1;
        rng(i,L,R+1){
            if (d[i-L]==digit_focused&&i>=search_start){
                ++ctr;
                last_appear_local=i;
            }
        }
        PutLL(0,ctr);
        PutLL(0,last_appear_local);
        Send(0);

        if (ME==0){
            ll acc=0;
            rng(ni,0,VNODES){
                Receive(ni);
                acc+=GetLL(ni);
                search_start=max(search_start,GetLL(ni));
            }
            digits_appended+=acc;
            ans=add(mul(ans,power(10,acc)),mul(digit_focused,ones(acc)));
        }
    }

    if (ME==0){
        ans=mul(ans,power(10,n-digits_appended));
        cout<<ans<<endl;
    }
    return 0;
}
