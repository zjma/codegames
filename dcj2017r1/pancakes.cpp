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
#include "pancakes.h"
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
    ll n=GetStackSize();
    ll p=GetNumDiners();
    ll L,R;tie(L,R)=get_my_inverval(n);
    if (L>R) return 0;
    NODES=min(NODES,n);
    VI cakes;
    rng(i,L,R+1){
        cakes.push_back(GetStackItem(i));
    }
    ll ans=0;
    ll lastserved=p;
    if (ME>=1){
        Receive(ME-1);
        ans=GetLL(ME-1);
        lastserved=GetLL(ME-1);
    }
    for (auto cake:cakes){
        if (cake>=lastserved){
            lastserved=cake;
        }else{
            ans++;
            lastserved=cake;
        }
    }
    if (ME==NODES-1){
        cout<<ans<<endl;
    }else{
        PutLL(ME+1,ans);
        PutLL(ME+1,lastserved);
        Send(ME+1);
    }
    return 0;
}
