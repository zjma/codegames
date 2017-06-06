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
#include "gold.h"
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
ll ToomanyBar=300000;

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

ll tryfind(ll ql, ll qr, ll dl, ll dr){
    if (ql>qr) return -1;
    char vl=Search(ql);
    if (vl=='X') return ql;
    char vr=Search(qr);
    if (vr=='X') return qr;
    if (vl=='=') return tryfind(ql+1,qr,2,dr);
    if (vr=='=') return tryfind(ql,qr-1,dl,2);
    if (vl=='<') return tryfind(ql+dl,qr,dl*2,dr);
    if (vr=='>') return tryfind(ql,qr-dr,dl,dr*2);
    ll qm=(ql+qr)/2;
    char vm=Search(qm);
    if (vm=='X') return qm;
    if (vm=='=') return tryfind(ql,qm-1,2,2);
    if (vm=='<') return tryfind(ql,qm,2,2);
    if (vm=='>') return tryfind(qm,qr,2,2);
    assert(0);
}

int main()
{
    ME=MyNodeId();
    NODES=NumberOfNodes();
    if (ME==0){
        ll ans=0;
        ll N=RoadLength();
        vector<pair<ll,ll>> segs;
        segs.emplace_back(0,N-1);
        while(!segs.empty()){
            ll sn=segs.size();
            ll pn=(NODES-1)/sn;
            vector<pair<ll,ll>> psegs;
            rng(i,0,sn){
                ll segl=segs[i].first;
                ll segr=segs[i].second;
                ll seglen=segr-segl+1;
                rng(pj,0,pn){
                    ll pl,pr;tie(pl,pr)=get_interval(pn,pj,seglen);
                    if (pl>pr) break;
                    psegs.emplace_back(segl+pl,segl+pr);
                }
            }

            ll ni=1;
            for (auto pr:psegs){
                PutLL(ni,0);
                PutLL(ni,pr.first);
                PutLL(ni,pr.second);
                Send(ni);
                ++ni;
            }

            segs.clear();
            rng(fi,1,ni){
                Receive(fi);
                ll toomany=GetLL(fi);
                if (toomany){
                    segs.push_back(psegs[fi-1]);
                }else{
                    ans^=GetLL(fi);
                }
            }
        }
        rng(ni,1,NODES){
            PutLL(ni,-1);
            Send(ni);
        }
        cout<<ans<<endl;
    }else{
        while(1){
            Receive(0);
            ll job=GetLL(0);
            if (job<0) return 0;
            ll L=GetLL(0);
            ll R=GetLL(0);
            queue<pair<ll,ll>> q;
            q.emplace(L,R);
            ll ans=0;
            ll found=0;
            while(!q.empty()&&found<ToomanyBar){
                ll cl,cr;tie(cl,cr)=q.front();
                q.pop();
                ll cm=tryfind(cl,cr,2,2);
                if (cm>=0){
                    ++found;
                    ans=ans^cm;
                    if (cm<cr) q.emplace(cm+1,cr);
                    if (cl<cm) q.emplace(cl,cm-1);
                }
            }

            if (found>=ToomanyBar){
                PutLL(0,1);
            }else{
                PutLL(0,0);
                PutLL(0,ans);
            }
            Send(0);
        }
    }
    return 0;
}
