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
ll pow(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}

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
    INIT();
    ll n=GetNumberLength();
    ll L,R;tie(L,R)=get_my_inverval(n);
    if (L>R) return 0;
    VI mydigits;
    rng(i,L,R+1){
        mydigits.push_back(GetDigit(i));
    }
    VI lastdpos(10,-1);
    VI f(10,0);
    VI g(10,0);
    if (ME>=1){
        Receive(ME-1);
        rng(i,0,10){
            lastdpos[i]=GetLL(ME-1);
        }
        rng(i,0,10){
            f[i]=GetLL(ME-1);
        }
        rng(i,0,10){
            g[i]=GetLL(ME-1);
        }
    }
    rng(i,L,R+1){
        ll d=mydigits[i-L];
        ll rec=-1;
        ll recj=-1;
        rng(j,d,10){
            if (lastdpos[j]>rec){
                rec=lastdpos[j];
                recj=j;
            }
        }
        if (recj==-1){
            f[d]=d;
            g[d]=1;
        }else{
            ll crt=add(mul(f[recj],10),d);
            f[d]=crt;
            g[d]=g[recj]+1;
        }
        lastdpos[d]=i;
    }
    if (ME==NODES-1){
        ll x=mydigits.back();
        ll p10=pow(10LL,n-g[x]);
        ll ans=mul(f[x],p10);
        cout<<ans<<endl;
    }else{
        rng(i,0,10){
            PutLL(ME+1,lastdpos[i]);
        }
        rng(i,0,10){
            PutLL(ME+1,f[i]);
        }
        rng(i,0,10){
            PutLL(ME+1,g[i]);
        }
        Send(ME+1);
    }
    return 0;
}
