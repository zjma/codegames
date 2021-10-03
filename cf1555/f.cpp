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
#include <sys/time.h>
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

struct timeval tp;
ll ms;
//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}
ll log2floor(ll x){
    return 63LL-__builtin_clzll(x);
}

inline ll lowbit(ll x) {return x&(-x);}

void explore(VI &e2insp, VVI &v2ancs, ll &tn, VI &tin, VI &tout, VI &xr, VI &ee2to, VI &ee2nxt, VI &v2ee0, VI &e2fr, VI &e2to, VI &e2val, ll parent, ll v, ll depth, ll xval){
    if (depth>=1) {
        v2ancs[v].push_back(parent);
        for(ll i=1;i<=log2floor(depth);i++){
            v2ancs[v].push_back(v2ancs[v2ancs[v][i-1]][i-1]);
        }
    }
    xr[v]=xval;
    tin[v]=tn++;
    for(ll eei=v2ee0[v];eei>=0;eei=ee2nxt[eei]){
        if (!e2insp[eei/2]) continue;
        ll v_next=ee2to[eei];
        if (tin[v_next]>=0) continue;
        explore(e2insp,v2ancs,tn,tin,tout,xr,ee2to,ee2nxt,v2ee0,e2fr,e2to,e2val,v,v_next,depth+1,xval^e2val[eei/2]);
    }

    tout[v]=tn++;
}

struct UnionFind {
    VI C;
    VI h;
    UnionFind(ll n) : C(n), h(n) {
        rng(i,0,n) C[i]=i;
    }
    ll find(ll x) {
        return (C[x] == x) ? x : C[x]=find(C[x]);
    }
    ll merge(ll x, ll y){
        ll xp=find(x);
        ll yp=find(y);
	    if (xp==yp) return 0;
        if (h[xp]==h[yp]){
            h[xp]++;
            C[yp]=xp;
        } else if (h[xp]<h[yp]){
            C[xp]=yp;
        } else {
            C[yp]=xp;
        }
        return 1;
    }
};
struct UTree {
    VI v;
    ll vn;
    UTree(ll n):v(n),vn(n) {
    }
    ll query(ll pos){
        ll ans=0;
        while(pos>=0){
            ans+=v[pos];
            pos-=lowbit(pos+1);
        }
        return ans;
    }
    void update(ll pos, ll diff){
        while (pos<vn){
            v[pos]+=diff;
            pos+=lowbit(pos+1);
        }
    }
};
ll isParent(VI &tin, VI &tout, ll x, ll y){
    return tin[x]<=tin[y]&&tout[x]>=tout[y];
}

ll getLca(VVI &v2ancs, VI &tin, VI &tout, ll x, ll y){
    if (isParent(tin,tout,x,y)) return x;
    if (isParent(tin,tout,y,x)) return y;
    for (ll k=v2ancs[x].size()-1; k>=0; --k){
        if (k<v2ancs[x].size()&&!isParent(tin,tout,v2ancs[x][k],y)) x=v2ancs[x][k];
    }
    ll ans=v2ancs[x][0];
    return ans;
}
char *anstr[2] = {"NO","YES"};
int main()
{
    gettimeofday(&tp, NULL); ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;cerr<<ms<<endl;
    ll n=scan();
    ll q=scan();
    VI e2fr(q);
    VI e2to(q);
    VI e2val(q);
    VI e2insp(q);//in spanning tree
    VI ee2to(q*2);
    VI ee2nxt(q*2);
    VI v2ee0(n,-1);
    gettimeofday(&tp, NULL); ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;cerr<<ms<<endl;
    UnionFind uf(n);
    rng(i,0,q){
        e2fr[i]=scan()-1;
        e2to[i]=scan()-1;
        e2val[i]=scan();
        e2insp[i]=uf.merge(e2fr[i],e2to[i]);

        ee2to[i*2]=e2to[i];
        ee2nxt[i*2]=v2ee0[e2fr[i]];
        v2ee0[e2fr[i]]=i*2;
        ee2to[i*2+1]=e2fr[i];
        ee2nxt[i*2+1]=v2ee0[e2to[i]];
        v2ee0[e2to[i]]=i*2+1;
    }
    gettimeofday(&tp, NULL); ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;cerr<<ms<<endl;

    ll tn=0;
    VI tin(n,-1);
    VI tout(n,-1);
    VI xr(n);
    ll KMAX=log2floor(tn);
    VVI v2ancs(n,VI(0));

    rng(i,0,n){
        if (tin[i]<0){
            explore(e2insp,v2ancs,tn,tin,tout,xr,ee2to,ee2nxt,v2ee0,e2fr,e2to,e2val,-1,i,0,0);
        }
    }
    gettimeofday(&tp, NULL); ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;cerr<<ms<<endl;
    UTree utree(tn);
    rng(i,0,q){
        ll ans=0;
        if (e2insp[i]){
            ans=1;
        }else{
            ll u=e2fr[i];
            ll v=e2to[i];
            ll lca=getLca(v2ancs,tin,tout,u,v);
            if (utree.query(tin[u])+utree.query(tin[v])-2*utree.query(tin[lca])==0&&xr[u]^xr[v]^e2val[i]==1){
                ans=1;
                //mark used
                for(ll x=u;x!=lca;x=v2ancs[x][0]){
                    utree.update(tin[x],1);
                    utree.update(tout[x],-1);
                }
                for(ll x=v;x!=lca;x=v2ancs[x][0]){
                    utree.update(tin[x],1);
                    utree.update(tout[x],-1);
                }
            }else{
                ans=0;
            }
        }
        printf("%s\n",anstr[ans]);
    }
    gettimeofday(&tp, NULL); ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;cerr<<ms<<endl;
    return 0;
}
