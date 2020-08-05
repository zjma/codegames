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
void dumpVI(VI &x){
    for(auto v:x){
        cerr<<v<<",";
    }
    cerr<<endl;
}
void tarjan_dfs(ll current, ll parent, ll &timer, ll &cn, VI &vtime, VI &rtime, VI &v2e0, VI &e2t, VI &e2n, VI &v2c, stack<ll> &stk)
{
    stk.push(current);
    rtime[current]=vtime[current]=timer++;
    for(ll e=v2e0[current];e>=0;e=e2n[e]){
        ll next=e2t[e];
        if (next==parent) continue;
        if (vtime[next]==-1){
            tarjan_dfs(next,current,timer,cn,vtime,rtime,v2e0,e2t,e2n,v2c,stk);
            rtime[current]=min(rtime[current],rtime[next]);
        }else if (v2c[next]==-1)
            rtime[current]=min(rtime[current],vtime[next]);
    }
    if (vtime[current]==rtime[current]){
        while (true){
            ll v=stk.top();
            v2c[v]=cn;
            stk.pop();
            if (v==current) break;
        }
        cn++;
    }
}

void work(const VI &v2e0, const VI &e2t, const VI &e2c, const VI &e2n,
        VI &score, VI &isSp, ll spn, ll current, ll parent, VI &spCount, VI &fio, VI &fore)
{
    fio[current]=score[current];
    spCount[current]=(isSp[current])?1:0;
    for(ll e=v2e0[current];e>=0;e=e2n[e]){
        ll next=e2t[e];
        if (next==parent) continue;
        work(v2e0,e2t,e2c,e2n,score,isSp,spn,next,current,spCount,fio,fore);
        spCount[current]+=spCount[next];
        fore[next]=(spCount[next]>0&&spCount[next]<spn)?max(0LL,fio[next]-e2c[e]):fio[next];
        fio[current]+=fore[next];
    }
}

void calc(VI &v2e0, VI &e2t, VI &e2c, VI &e2n,
        ll spn, ll current, ll parent, VI &spCount, VI &fio, VI &fore, VI &ans, ll fioParent, ll srcEdge)
{
    ll parentScore=(spCount[current]>0&&spCount[current]<spn)?max(0LL,fioParent-e2c[srcEdge]):fioParent;
    ans[current]=fio[current]+parentScore;
    for(ll e=v2e0[current];e>=0;e=e2n[e]){
        ll next=e2t[e];
        if (next==parent) continue;
        ll fioAsChild=fio[current]-fore[next]+parentScore;
        calc(v2e0,e2t,e2c,e2n,spn,next,current,spCount,fio,fore,ans,fioAsChild,e);
    }
}

int main()
{
    ll n=scan();
    ll m=scan();
    ll k=scan();
    VI c(n);
    VI w(m);
    VI isSp0(n);
    rng(i,0,k) isSp0[scan()-1]=1;
    rng(i,0,n) c[i]=scan();
    rng(i,0,m) w[i]=scan();
    VI _v2e0(n,-1);
    VI _e2f;
    VI _e2t;
    VI _e2c;
    VI _e2n;
    rng(i,0,m){
        ll x=scan()-1;
        ll y=scan()-1;
        _e2f.push_back(x);
        _e2t.push_back(y);
        _e2c.push_back(w[i]);
        _e2n.push_back(_v2e0[x]);
        _v2e0[x]=_e2f.size()-1;
        _e2f.push_back(y);
        _e2t.push_back(x);
        _e2c.push_back(w[i]);
        _e2n.push_back(_v2e0[y]);
        _v2e0[y]=_e2f.size()-1;
    }
    ll timer=0;
    ll cn=0;
    VI vtime(n,-1);
    VI rtime(n,-1);
    VI _v2c(n,-1);
    stack<ll> stk;
    tarjan_dfs(0,-1,timer,cn,vtime,rtime,_v2e0,_e2t,_e2n,_v2c,stk);

    VI v2e0(cn,-1);
    VI e2n;
    VI e2c;
    VI e2t;
    VI e2f;
    set<tuple<ll,ll>> eset;
    rng(i,0,m){
        ll cx=_v2c[_e2f[i*2]],cy=_v2c[_e2t[i*2]];
        if (cx==cy) continue;
        if (cx>cy) swap(cx,cy);
        if (eset.find(make_tuple(cx,cy))!=eset.end()) continue;
        e2n.push_back(v2e0[cx]);
        e2c.push_back(_e2c[i*2]);
        e2f.push_back(cx);
        e2t.push_back(cy);
        v2e0[cx]=e2n.size()-1;
        e2n.push_back(v2e0[cy]);
        e2c.push_back(_e2c[i*2]);
        e2t.push_back(cx);
        e2f.push_back(cy);
        v2e0[cy]=e2n.size()-1;
    }
    VI score(cn);
    VI isSp(cn);
    rng(i,0,n){
        score[_v2c[i]]+=c[i];
        isSp[_v2c[i]]|=isSp0[i];
    }

    ll spn=0;rng(i,0,cn) if (isSp[i]) spn++;
    VI spCount(cn);
    VI fio(cn);
    VI fore(cn);

    work(v2e0,e2t,e2c,e2n,score,isSp,spn,0,-1,spCount,fio,fore);
    VI ans(cn);
    calc(v2e0,e2t,e2c,e2n,spn,0,-1,spCount,fio,fore,ans,0,-1);
    rng(i,0,n-1){
        cout<<ans[_v2c[i]]<<" ";
    }
    cout<<ans[_v2c[n-1]]<<endl;
    return 0;
}
