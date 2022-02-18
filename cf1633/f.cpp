// template.cpp : Defines the entry point for the console application.
//
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


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void heavyLightPartitionDfs(VVI &v2chds, VI &v2size, ll prt, ll cur, ll fromHeavyEdge, VI &v2p, VI &v2poffset, VVI &p2vs, VI &p2prt){
    ll curpid=-1;
    if (fromHeavyEdge){
        curpid=v2p[prt];
        v2poffset[cur]=v2poffset[prt]+1;
    }else{
        p2vs.emplace_back();
        curpid=p2vs.size()-1;
        v2poffset[cur]=0;
        p2prt.push_back((prt<0)?(-1):v2p[prt]);
    }
    v2p[cur]=curpid;
    p2vs[curpid].push_back(cur);
    ll foundHeavyEdge=0;
    for(ll chd:v2chds[cur]){
        if (v2size[chd]*2>=v2size[cur]){
            foundHeavyEdge=1;
            heavyLightPartitionDfs(v2chds,v2size,cur,chd,1,v2p,v2poffset,p2vs,p2prt);
        }else{
            heavyLightPartitionDfs(v2chds,v2size,cur,chd,0,v2p,v2poffset,p2vs,p2prt);
        }
    }
}

ll heavyLightPartition(VVI &v2chds, VI &v2size, ll root, VI &v2p, VI &v2poffset, VVI &p2vs, VI &p2prt){
    ll vn=v2chds.size();
    v2p.resize(vn,-1);
    v2poffset.resize(vn,-1);
    p2vs.clear();
    p2prt.clear();
    heavyLightPartitionDfs(v2chds,v2size,-1,root,0,v2p,v2poffset,p2vs,p2prt);
    return p2vs.size();
}

void dfs(VVI &v2nxts,VVI &v2es, ll prt, ll p2cei, ll cur, VVI &v2chds, VI &v2prt, VI &v2size, VI &v2pei){
    v2prt[cur]=prt;
    v2pei[cur]=p2cei;
    ll nxtcount=v2nxts[cur].size();
    rng(i,0,nxtcount){
        ll c2nei=v2es[cur][i];
        ll nxt=v2nxts[cur][i];
        if(nxt==prt) continue;
        v2chds[cur].push_back(nxt);
        dfs(v2nxts,v2es,cur,c2nei,nxt,v2chds,v2prt,v2size,v2pei);
        v2size[cur]+=v2size[nxt];
    }
    v2size[cur]++;
}

struct SegOracle {
    VI masks;
    VI values;
    void init(VI &val){
        ll n=val.size();
        masks.resize(n,0);
        values.assign(val.begin(),val.end());
    }
    void flip(ll preflen){
        rng(i,0,preflen) masks[i]=1-masks[i];
    }
    ll sumX(){
        ll n=masks.size(),ans=0;
        rng(i,0,n) ans+=masks[i];
        return ans;
    }
    ll sumVX(){
        ll n=masks.size(),ans=0;
        rng(i,0,n) ans+=masks[i]*values[i];
        return ans;
    }
    void appendActEis(VI &eis){
        ll n=values.size();
        rng(i,0,n){
            if (masks[i]==1&&values[i]>=1) eis.push_back(values[i]);
        }
    }
};

void dumpVI(string s, VI &arr){
    ll n=arr.size();
    rng(i,0,n)
        cerr<<s<<"["<<i<<"]="<<arr[i]<<endl;
}
int main()
{
    ll n=scan();
    VI e2f(n-1),e2t(n-1);
    VVI v2es(n);
    VVI v2nxts(n);
    rng(i,0,n-1){
        ll v0=scan()-1;
        ll v1=scan()-1;
        e2f[i]=v0;
        e2t[i]=v1;
        v2es[v0].push_back(i);
        v2es[v1].push_back(i);
        v2nxts[v0].push_back(v1);
        v2nxts[v1].push_back(v0);
    }

    VVI v2chds(n);
    VI v2size(n);
    VI v2prt(n);
    VI v2pei(n);
    dfs(v2nxts,v2es,-1,-1,0,v2chds,v2prt,v2size,v2pei);
    // dumpVI("v2size",v2size);
    // rng(i,0,n) dumpVI("v2chds["+to_string(i)+"]",v2chds[i]);
    // dumpVI("v2pei",v2pei);
    VI v2p(n);
    VI v2poffset(n);
    VVI p2vs;
    VI p2prt;
    ll pn=heavyLightPartition(v2chds, v2size, 0, v2p, v2poffset, p2vs, p2prt);
    // dumpVI("v2p",v2p);
    // dumpVI("v2poffset",v2poffset);
    // dumpVI("p2prt",p2prt);
    // rng(pi,0,pn) dumpVI("p2vs["+to_string(pi)+"]",p2vs[pi]);
    vector<SegOracle> p2seg(pn);
    rng(pi,0,pn){
        ll plen=p2vs[pi].size();
        VI eis(plen);
        rng(i,0,plen){
            ll curv=p2vs[pi][i];
            eis[i]=v2pei[curv]+1;
        }
        p2seg[pi].init(eis);
    }
    VI p2rsumx(pn,0);
    VI p2rsumvx(pn,0);
    ll activatedCount=1;
    p2seg[v2p[0]].flip(1);
    p2rsumx[v2p[0]]=1;
    p2rsumvx[v2p[0]]=0;
    ll lastT1Positive=0;
    while(1){
        ll cmd=scan();
        if(cmd==1){
            activatedCount++;
            ll v=scan()-1;
            ll p=v2p[v];
            ll offset=v2poffset[v];
            ll lastRecurSumXDiff=0,lastRecurSumVXDiff=0;
            while(1){
                // flipPartition(p,offset+1);
                {
                    // cerr<<"p="<<p<<",offset="<<offset<<endl;
                    ll oldSumX=p2seg[p].sumX();
                    ll oldSumVX=p2seg[p].sumVX();
                    p2seg[p].flip(offset+1);
                    ll newSumX=p2seg[p].sumX();
                    ll newSumVX=p2seg[p].sumVX();
                    // cerr<<"sumX -  old="<<oldSumX<<", new="<<newSumX<<endl;
                    // cerr<<"sumVX - old="<<oldSumVX<<", new="<<newSumVX<<endl;
                    lastRecurSumXDiff+=newSumX-oldSumX;
                    lastRecurSumVXDiff+=newSumVX-oldSumVX;
                    p2rsumx[p]+=lastRecurSumXDiff;
                    p2rsumvx[p]+=lastRecurSumVXDiff;
                }

                p=p2prt[p];
                if(p<0) break;
                offset=p2vs[p].size()-1;
            }
            // dumpVI("p2rsumx",p2rsumx);
            // dumpVI("p2rsumvx",p2rsumvx);
            if (p2rsumx[0]*2==activatedCount){
                printf("%lld\n",p2rsumvx[0]);fflush(stdout);
                lastT1Positive=1;
            }else{
                printf("0\n");fflush(stdout);
                lastT1Positive=0;
            }

        }else if(cmd==2){
            if (lastT1Positive){
                ll ten=activatedCount/2;
                VI eis;
                rng(pi,0,pn) p2seg[pi].appendActEis(eis);
                assert(ten==eis.size());
                printf("%lld ", ten);
                rng(i,0,ten-1) printf("%lld ", eis[i]);
                printf("%lld\n",eis[ten-1]);
                fflush(stdout);
            }else{
                printf("0\n");fflush(stdout);
            }
        }else{
            break;
        }
    }
    return 0;
}
