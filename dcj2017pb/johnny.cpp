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
#include "johnny.h"
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


//Tarjan's strong connected components
void tarjan_dfs(ll v, ll &timer, ll &cn,
        VI &vtime, VI &rtime,
        const VI &v2e0,
        const VI &e2t, const VI &e2n,
        VI &v2c, stack<ll> &stk)
{
    stk.push(v);
    rtime[v]=vtime[v]=timer++;
    for (ll i=v2e0[v];i>=0;i=e2n[i]){
        ll w=e2t[i];
        if (vtime[w]==-1){
            tarjan_dfs(w,timer,cn,vtime,rtime,v2e0,e2t,e2n,v2c,stk);
            rtime[v]=min(rtime[v],rtime[w]);
        }else if (v2c[w]==-1)
            rtime[v]=min(rtime[v],vtime[w]);
    }
    if (vtime[v]==rtime[v]){
        while (true){
            ll pv=stk.top();
            v2c[pv]=cn;
            stk.pop();
            if (pv==v) break;
        }
        cn++;
    }
}
/**
 * Tarjan's strong connected components
 *
 * \param n     #vertices (0..n-1)
 * \param v2e0
 * \param e2t
 * \param e2n
 *
 * \return  #components, vid-cid mapping stored in v2c
 */
ll tarjan_strong(ll n,
        const VI &v2e0,
        const VI &e2t,
        const VI &e2n,
        VI &v2c)
{
    v2c.assign(n,-1);
    VI vtime(n,-1);
    VI rtime(n,-1);
    stack<ll> stk;
    ll timer=0,cn=0;
    for (ll i=0;i<n;i++){
        if (vtime[i]>=0) continue;
        tarjan_dfs(i,timer,cn,vtime,rtime,v2e0,e2t,e2n,v2c,stk);
    }
    return cn;
}

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll N=NumberOfCards();
    VI L(NODES);
    VI R(NODES);
    rng(i,0,NODES){
        tie(L[i],R[i])=get_interval(NODES,i,N);
    }
    if (L[ME]>R[ME]) return 0;
    ll VNODES=min(NODES,N);
    VI localdeg(R[ME]-L[ME]+1);
    rng(i,L[ME],R[ME]+1){
        rng(j,0,N){
            if (IsBetter(i,j)) ++localdeg[i-L[ME]];
        }
    }
    rng(i,L[ME],R[ME]+1){
        PutLL(0,localdeg[i-L[ME]]);
    }
    Send(0);

    if (ME==0){
        VI odeg(N);
        rng(i,0,VNODES){
            Receive(i);
            rng(j,L[i],R[i]+1){
                odeg[j]=GetLL(i);
            }
        }
        sort(odeg.begin(),odeg.end());
        VI dps(N);
        rng(i,0,N){
            dps[i]=(i==0)?odeg[i]:(dps[i-1]+odeg[i]);
        }
        ll mycount=0;
        rng(i,0,N-1){
            ++mycount;
            if (odeg[i]>=mycount) continue;
            if (odeg[i+1]<=mycount-1) continue;
            if (dps[N-1]-dps[i]==mycount*(N-mycount)+(N-mycount)*(N-mycount-1)/2){
                cout<<(N-mycount)<<endl;
                return 0;
            }
        }
        cout<<"IMPOSSIBLE"<<endl;
    }
    return 0;
}
