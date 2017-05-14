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
#include "todd_and_steven.h"
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

pair<ll,ll> get_my_inverval(ll n) {
    ll amt=max(1LL,(n+NODES-1)/NODES);
    NODES=(n+amt-1)/amt;
    ll L=ME*amt;
    ll R=min(n-1,(ME+1)*amt-1);
    if (L>R) return make_pair(-1,-2);
    return make_pair(L,R);
}


int main()
{
    INIT();
    ll oddn=GetToddLength();
    ll even=GetStevenLength();
    ll n=oddn+even;
    ll L,R;tie(L,R)=get_my_inverval(n);
    if (L>R) return 0;

    ll myn=R-L+1;

    ll counter=0;
    ll ans=0;
    ll nextoddi=0;
    ll nextevei=0;
    if (ME>=1){
        Receive(ME-1);
        counter=GetLL(ME-1);
        ans=GetLL(ME-1);
        nextoddi=GetLL(ME-1);
        nextevei=GetLL(ME-1);
    }

    ll oddcand=(nextoddi>=oddn)?INF:GetToddValue(nextoddi);
    ll evecand=(nextevei>=even)?INF:GetStevenValue(nextevei);
    rng(i,0,myn){
        ll sel;
        if (oddcand>evecand){
            sel=evecand;
            ++nextevei;
            evecand=(nextevei>=even)?INF:GetStevenValue(nextevei);
        }else{
            sel=oddcand;
            ++nextoddi;
            oddcand=(nextoddi>=oddn)?INF:GetToddValue(nextoddi);
        }
        ans=add(ans,sel^counter);
        ++counter;
    }

    if (ME==NODES-1){
        cout<<ans<<endl;
    }else{
        PutLL(ME+1,counter);
        PutLL(ME+1,ans);
        PutLL(ME+1,nextoddi);
        PutLL(ME+1,nextevei);
        Send(ME+1);
    }
    return 0;
}
