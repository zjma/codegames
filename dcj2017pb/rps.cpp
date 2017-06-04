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
#include "rps.h"
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

ll lbp2(ll x){
    ll ret=1;
    while(1){
        ll newret=ret*2;
        if (newret>x) return ret;
        ret=newret;
    }
}

ll log2(ll n){
    ll ret=0;
    while(n>1){
        ++ret;
        n/=2;
    }
    return ret;
}

pair<ll,char> battle(ll idx0, char val0, ll idx1, char val1){
    switch(val0){
        case 'P':
        switch(val1){
            case 'P':
            case 'R':
            return make_pair(idx0,'P');
            case 'S':
            return make_pair(idx1,'S');
            assert(0);
        }
        case 'R':
        switch(val1){
            case 'P':
            return make_pair(idx1,'P');
            case 'R':
            case 'S':
            return make_pair(idx0,'R');
            assert(0);
        }
        case 'S':
        switch(val1){
            case 'S':
            case 'P':
            return make_pair(idx0,'S');
            case 'R':
            return make_pair(idx1,'R');
            assert(0);
        }
        assert(0);
    }
}

pair<ll,char> tournament(const vector<char> &v, ll ql, ll qr){
    if (ql==qr){
        return make_pair(ql,v[ql]);
    }
    ll qm=(ql+qr)/2;
    ll div0winneridx;
    char div0winnerval;
    tie(div0winneridx,div0winnerval)=tournament(v,ql,qm);
    ll div1winneridx;
    char div1winnerval;
    tie(div1winneridx,div1winnerval)=tournament(v,qm+1,qr);
    return battle(div0winneridx,div0winnerval,div1winneridx,div1winnerval);
}


int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll E=GetN();
    ll n=1<<E;
    ll VNODES=lbp2(min(NODES,n));
    if (ME>=VNODES) return 0;
    ll L,R;tie(L,R)=get_interval(VNODES,ME,n);

    // Find local winner.
    vector<char> v(R-L+1);
    rng(i,L,R+1){
        v[i-L]=GetFavoriteMove(i);
    }
    char localwinnerval;
    ll localwinneridx;
    tie(localwinneridx,localwinnerval)=tournament(v,0,R-L);
    localwinneridx+=L;
    ll rounds=log2(VNODES);
    rng(ri,0,rounds){
        ll flag=1<<ri;
        ll mysib=ME^flag;
        if (ME&flag){
            PutLL(mysib,localwinneridx);
            PutChar(mysib,localwinnerval);
            Send(mysib);
            return 0;
        }else{
            Receive(mysib);
            ll sibidx=GetLL(mysib);
            char sibval=GetChar(mysib);
            tie(localwinneridx,localwinnerval)=battle(localwinneridx,localwinnerval,sibidx,sibval);
        }
    }
    cout<<localwinneridx<<endl;
    return 0;
}
