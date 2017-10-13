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

ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void calc(ll v, VVI &v2chds, VVI &pl, VVI &pr, VI &f){
    ll chdn=v2chds[v].size();
    rng(i,0,chdn){
        calc(v2chds[v][i], v2chds, pl, pr, f);
    }
    rng(i,0,chdn+1){
        pl[v][i]=(i==0)?1:(mul(pl[v][i-1],f[v2chds[v][i-1]]));
        pr[v][i]=(i==0)?1:(mul(pr[v][i-1],f[v2chds[v][chdn-i]]));
    }
    assert(pl[v][chdn]==pr[v][chdn]);
    f[v]=(chdn==0)?1:mul(pl[v][chdn],2);
}


ll sumup(ll node, ll parent, ll parent_contri, VVI &v2chds, VI &f, VVI &pl, VVI &pr){
    ll ret=0;
    ll chdn=v2chds[node].size();
    rng(i,0,chdn){
        ll chd=v2chds[node][i];
        ll term=(parent<0&&chdn==1)?1:2;
        ll cont_to_son = mul(term,mul(mul(pl[node][i],pr[node][chdn-1-i]),parent_contri));
        ll sub=sumup(chd,node,cont_to_son,v2chds,f,pl,pr);
        ret=add(ret,sub);
    }
    ll term=(chdn==0&&parent<0)?1:2;
    ll sub=mul(term,mul(pl[node][chdn],parent_contri));
    ret=add(ret,sub);
    return ret;
}

void buildadjlist(ll n,
    const VI &froms, const VI &tos,
    VI &v2e0, VI &e2n)
{
    v2e0.resize(n);
    v2e0.assign(n, -1);
    ll en = froms.size();
    e2n.resize(en);
    for (int i = 0;i < en;i++) {
        ll f = froms[i];
        ll t = tos[i];
        e2n[i] = v2e0[f];
        v2e0[f] = i;
    }
}

void buildtree(ll node, ll parent, VI &e2to, VI &e2next, VI &v2e0, VVI &v2chds){
    ll ei=v2e0[node];
    while(ei>=0){
        ll nextnode=e2to[ei];
        if (nextnode!=parent){
            v2chds[node].push_back(nextnode);
            buildtree(nextnode, node, e2to, e2next, v2e0, v2chds);
        }
        ei=e2next[ei];
    }
}

int main()
{
    ll n=scan();
    VI e2from;
    VI e2to;
    VI v2e0;
    VI e2next;
    rng(i,0,n-1){
        ll x=scan()-1;
        ll y=scan()-1;
        e2from.push_back(x);
        e2to.push_back(y);
        e2from.push_back(y);
        e2to.push_back(x);
    }
    buildadjlist(n,e2from, e2to, v2e0, e2next);
    VVI v2chds(n);
    buildtree(0,-1,e2to,e2next,v2e0,v2chds);
    VI f(n);
    VVI pl(n);
    VVI pr(n);
    rng(i,0,n){
        pl[i].resize(v2chds[i].size()+1);
        pr[i].resize(v2chds[i].size()+1);
    }
    calc(0, v2chds, pl, pr, f);
    ll ans=sumup(0, -1, 1, v2chds, f, pl, pr);
    cout<<ans<<endl;
    return 0;
}
