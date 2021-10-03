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
typedef vector<VVI> VVVI;
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
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

const ll N=800000;

void initVvi(VVI &A, ll rn, ll cn, ll val){
    A.resize(rn);
    rng(i,0,rn) A[i].assign(cn,val);
}

struct Graph {
    ll n;
    VI v2de0;
    VI de2dst;
    VI de2nxt;
    Graph(ll _n){
        n=_n;
        v2de0.assign(n,-1);
        de2dst.clear();
        de2nxt.clear();
    }
    void addAdj(ll v0, ll v1){
        ll newdeid=de2dst.size();
        de2dst.push_back(v1);
        de2nxt.push_back(v2de0[v0]);
        v2de0[v0]=newdeid;
    }
};

struct RectOracle {
    ll rn;
    ll cn;
    VVI presum;
    VVI presum2;
    RectOracle(VVI &rect) {
        rn=rect.size();
        cn=20;
        initVvi(presum,rn+1,cn+1,0);
        initVvi(presum2,rn+1,cn+1,0);
        rng(ri,0,rn){
            rng(ci,0,cn){
                presum[ri+1][ci+1]=presum[ri][ci+1]+presum[ri+1][ci]-presum[ri][ci]+rect[ri][ci];
                presum2[ri+1][ci+1]=presum2[ri][ci+1]+presum2[ri+1][ci]-presum2[ri][ci]+rect[ri][ci]*(ci+1);
            }
        }
    }
    ll getAreaSum(ll ri, ll ci, ll rj, ll cj){
        if (ri>rj||ci>cj) return 0;
        return presum[rj+1][cj+1]-presum[ri][cj+1]-presum[rj+1][ci]+presum[ri][ci];
    }
    ll getAreaSum2(ll ri, ll ci, ll rj, ll cj){
        if (ri>rj||ci>cj) return 0;
        return presum2[rj+1][cj+1]-presum2[ri][cj+1]-presum2[rj+1][ci]+presum2[ri][ci];
    }
};

ll n;
ll e2c[N-1];
ll S[N-1];

//adj link list
VVVI v2vecs;
VVI v2aggvec;

void vecCap(VI &V0, ll limit, VI &V1) {
    V1.assign(V0.begin(),V0.end());
    rng(i,0,19-limit){
        V1[18-i]+=V1[19-i];
        V1[19-i]=0;
    }
}

void vecIncAt(VI &V0, ll pos){
    V0[pos]++;
}

void vecAddTo(VI &V0, VI &V1){
    rng(i,0,20){
        V1[i]+=V0[i];
    }
}


void dfs1(Graph &G, ll cur, ll parent, VI &v2ans, VVI &v2aggvec, VVVI &v2vecs){
    ll totSubAns=0;
    for(ll dei=G.v2de0[cur];dei>=0;dei=G.de2nxt[dei]){
        ll nxt=G.de2dst[dei];
        if (nxt==parent) continue;
        cerr<<"cur="<<cur<<endl;
        dfs1(G,nxt,cur,v2ans,v2aggvec,v2vecs);
        cerr<<"cur="<<cur<<endl;
        totSubAns=add(totSubAns,v2ans[nxt]);
        cerr<<"cur="<<cur<<endl;
        ll ei=dei/2;
        cerr<<"cur="<<cur<<endl;
        ll cap=e2c[ei];
        cerr<<"cur="<<cur<<endl;
        VI tmp(20,0);
        cerr<<"cur="<<cur<<endl;
        vecCap(v2aggvec[nxt],cap-1,tmp);
        cerr<<"cur="<<cur<<endl;
        vecIncAt(tmp,cap-1);
        cerr<<"cur="<<cur<<endl;
        vecAddTo(tmp,v2aggvec[cur]);
        cerr<<"cur="<<cur<<endl;
        v2vecs[cur].push_back(tmp);
        cerr<<"cur="<<cur<<endl;
    }
    ll rn=v2vecs[cur].size();
    RectOracle ro(v2vecs[cur]);
    ll acrossTotal=0;
    rng(ci,0,20){
        rng(ri,0,rn){
            ll extPairableCount=1;//root
            extPairableCount=add(extPairableCount,ro.getAreaSum(ri+1,ci,rn-1,ci));//peer
            extPairableCount=add(extPairableCount,ro.getAreaSum(0,ci+1,rn-1,19)-ro.getAreaSum(ri,ci+1,ri,19));//rest
            ll acrossPairCount=mul(extPairableCount,v2vecs[cur][ri][ci]);
            ll contri=mul(acrossPairCount,(ci+1));
            acrossTotal=add(acrossTotal,contri);
        }
    }
    cerr<<"totSubAns="<<totSubAns<<endl;
    cerr<<"rn="<<rn<<endl;
    v2ans[cur]=totSubAns+acrossTotal;
}
void dfs2(Graph &G, ll cur, ll parent){

}

void testcase(ll ti){
    n=scan();
    VI e2c(n-1);
    VI de2dst(n*2-2);
    VI de2nxt(n*2-2);
    VI v2de0(n,-1);
    Graph G(n);
    rng(i,0,n-1){
        ll a=scan()-1;
        ll b=scan()-1;
        ll c=scan();
        e2c[i]=c;
        G.addAdj(a,b);
        G.addAdj(b,a);
    }
    VI v2ans(n);
    VVI v2aggvec(n,VI(20,0));
    VVVI v2vecs(n);
    cerr<<"!"<<endl;
    dfs1(G,0,-1,v2ans,v2aggvec,v2vecs);
    dfs2(G,0,-1);
    ll ans=1;
    rng(i,0,n-1){
        ans=mul(ans,S[i]);
    }
    printf("Case #%lld: %lld\n", ti+1, ans);
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        testcase(ti);
    }
    return 0;
}
