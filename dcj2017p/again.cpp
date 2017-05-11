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
#include "again.h"
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


ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}


ll ME=0;
ll NODES=0;
ll n;
void INIT() {ME=MyNodeId();NODES=NumberOfNodes();n=GetN();}

pair<ll,ll> get_my_inverval(ll n) {
    ll amt=max(1LL,(n+NODES-1)/NODES);
    ll L=ME*amt;
    ll R=min(n-1,(ME+1)*amt-1);
    if (L>R) return make_pair(-1,-2);
    return make_pair(L,R);
}


int main()
{
    INIT();
    ll mysa=0,mysb=0;
    ll i=ME;
    while (i<n){
        mysa=add(mysa,GetA(i));
        mysb=add(mysb,GetB(i));
        i+=NODES;
    }

    if (ME==0){
        VI sa(NODES);
        VI sb(NODES);
        sa[0]=mysa;
        sb[0]=mysb;

        rng(i,1,NODES){
            Receive(i);
            sa[i]=GetLL(i);
            sb[i]=GetLL(i);
        }

        ll SA=0;
        rng(i,0,NODES){
            SA=add(SA,sa[i]);
        }
        ll SB=0;
        rng(i,0,NODES){
            SB=add(SB,sb[i]);
        }

        ll ans=mul(SA,SB);
        ans=sub(ans,mul(sa[0],sb[0]));
        rng(i,1,NODES){
            ans=sub(ans,mul(sa[i],sb[NODES-i]));
        }
        cout<<ans<<endl;
    }else{
        PutLL(0,mysa);
        PutLL(0,mysb);
        Send(0);
    }
    return 0;
}
