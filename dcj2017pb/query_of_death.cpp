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
#include "query_of_death.h"
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

VI livingNode;
ll livingtot;
void InitLivingNodes(ll NODES){
    livingtot=NODES-1;
    livingNode.resize(NODES-1);
    rng(i,1,NODES){
        livingNode[i-1]=i;
    }
}

ll GetLivingNodeNumber(){return livingtot;}

ll GetLivinigNodeId(ll vid){return livingNode[vid];}

void ReportNodeBroken(ll nid){
    ll found=false;
    rng(i,0,livingtot){
        if (found){
            livingNode[i-1]=livingNode[i];
        }else{
            found=(livingNode[i]==nid);
        }
    }
    if (found) livingtot--;
}


int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll L=GetLength();
    if (ME==0){
        InitLivingNodes(NODES);
        ll ans=0;
        ll qodl=0,qodr=L-1;
        while (qodl<qodr){
            ll qodrangelen=qodr-qodl+1;
            ll vnn=GetLivingNodeNumber();
            rng(vni,0,vnn){
                ll subl,subr;tie(subl,subr)=get_interval(vnn,vni,qodrangelen);
                ll ni=GetLivinigNodeId(vni);
                PutLL(ni,0);PutLL(ni,subl+qodl);PutLL(ni,subr+qodl);Send(ni);
            }
            ll broken_id=-1;
            ll newqodl,newqodr;
            rng(vni,0,vnn){
                ll ni=GetLivinigNodeId(vni);
                Receive(ni);
                ll ishebroken=GetLL(ni);
                ll reportedsum=GetLL(ni);
                ll subl,subr;tie(subl,subr)=get_interval(vnn,vni,qodrangelen);
                if (ishebroken){
                    broken_id=ni;
                    newqodr=qodl+subr;newqodl=qodl+subl;
                }else{
                    ans+=reportedsum;
                }
            }
            assert(broken_id>=0);
            ReportNodeBroken(broken_id);
            qodl=newqodl;qodr=newqodr;
        }
        // All done. Tell them to finish.
        rng(vni,0,GetLivingNodeNumber()){
            ll ni=GetLivinigNodeId(vni);
            PutLL(ni,-1);Send(ni);
        }
        ans+=GetValue(qodl);
        cout<<ans<<endl;
    }else{
        while(1){
            Receive(0);
            ll job=GetLL(0);
            if (job==-1) return 0;
            ll ql=GetLL(0);
            ll qr=GetLL(0);
            VI qd(qr-ql+1);
            rng(qi,ql,qr+1){
                qd[qi-ql]=GetValue(qi);
            }
            ll s=0;rng(qi,ql,qr+1){s+=qd[qi-ql];}

            ll broken=0;
            if (ql<=qr){
                rng(i,0,32){
                    if (GetValue(ql)!=qd[0]){
                        broken=1;break;
                    }
                }
            }

            PutLL(0,broken);
            PutLL(0,s);
            Send(0);
            if (broken) return 0;
        }
    }
    return 0;
}
