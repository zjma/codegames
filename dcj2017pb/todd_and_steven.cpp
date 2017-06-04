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

ll GetValue(ll who, ll idx){
    return (who==0)?GetToddValue(idx):GetStevenValue(idx);
}

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll on=GetToddLength();
    ll en=GetStevenLength();

    if (ME==0){
        vector<tuple<ll,ll,ll>> sample;
        ll oi=0,od=max(1LL,on/NODES);
        while (oi<on){
            sample.emplace_back(GetToddValue(oi),0,oi);
            oi+=od;
        }
        ll ei=0,ed=max(1LL,en/NODES);
        while (ei<en){
            sample.emplace_back(GetStevenValue(ei),1,ei);
            ei+=ed;
        }
        sort(sample.begin(),sample.end());
        ll sn=sample.size();
        VI val(sn);
        VI who(sn);
        VI idx(sn);
        rng(i,0,sn){
            tie(val[i],who[i],idx[i])=sample[i];
        }
        rng(i,0,NODES){
            ll si,sj;tie(si,sj)=get_interval(NODES,i,sn);
            if (si>sj){
                PutLL(i,-1);Send(i);
                continue;
            }
            PutLL(i,0);
            PutLL(i,who[si]);
            PutLL(i,idx[si]);
            if (sj==sn-1){
                PutLL(i,-1);
                PutLL(i,-1);
            }else{
                ll ssi,ssj;tie(ssi,ssj)=get_interval(NODES,i+1,sn);
                PutLL(i,who[ssi]);
                PutLL(i,idx[ssi]);
            }
            Send(i);
        }
    }


    Receive(0);
    ll work=GetLL(0);
    if (work<0){
        PutLL(0,0);Send(0);
    }else{
        VI total(2);total[0]=on;total[1]=en;
        VI nextidx(2);
        VI nextval(2);
        ll nextwho=GetLL(0);
        nextidx[nextwho]=GetLL(0);
        ll endwho=GetLL(0);
        ll endidx=GetLL(0);

        nextval[nextwho]=GetValue(nextwho,nextidx[nextwho]);

        // Find smallest follower in the other queue.
        ll fl=-1,flv=-1,fr=total[1-nextwho],frv=-1;
        while (fl+1<fr){
            ll fm=(fl+fr)/2;
            ll tmpv=GetValue(1-nextwho,fm);
            if (tmpv<nextval[nextwho]){
                fl=fm;flv=tmpv;
            }else{
                fr=fm;frv=tmpv;
            }
        }
        nextidx[1-nextwho]=fr;nextval[1-nextwho]=frv;

        ll ans=0;
        while(1){
            assert(nextidx[nextwho]<total[nextwho]);
            if (nextwho==endwho&&nextidx[nextwho]==endidx) break;
            ll nextrank=nextidx[0]+nextidx[1];
            ans=add(ans,nextrank^nextval[nextwho]);
            if (nextrank==total[0]+total[1]-1) break;
            nextidx[nextwho]++;
            nextval[nextwho]=(nextidx[nextwho]==total[nextwho])?-1:GetValue(nextwho,nextidx[nextwho]);
            nextwho=(nextidx[0]==total[0])?1:(nextidx[1]==total[1])?0:(nextval[0]<nextval[1])?0:1;
        }

        PutLL(0,ans);Send(0);

    }

    if (ME==0){
        ll ans=0;
        rng(i,0,NODES){
            Receive(i);
            ans=add(ans,GetLL(i));
        }
        cout<<ans<<endl;
    }
    return 0;
}
