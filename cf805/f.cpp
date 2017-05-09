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

const ll N=100000;
ll n;
ll prnt[N];
ll ldv0[N];
ll lgst[N];
ll com[N];
ll comsize[N];
ll comroot[N];
ll comn=0;
ll helloed[N];
VI nb[N];
VI sons[N];
VI f[N];
VI bsuf[N];

void dfs(ll parent, ll v, ll ci){
    prnt[v]=parent;
    helloed[v]=1;
    com[v]=ci;

    VI sonldvs;
    for (auto nxtv:nb[v]){
        if (helloed[nxtv]) continue;
        dfs(v,nxtv,ci);
        sons[v].push_back(nxtv);
        sonldvs.push_back(ldv0[nxtv]);
    }
    ll sonn=sons[v].size();
    ll lds0=-1;
    rng(i,0,sonn){
        if (lds0<0||ldv0[lds0]<sonldvs[i]) lds0=sons[v][i];
    }
    ldv0[v]=(lds0<0)?0:(ldv0[lds0]+1);
}

void dfs2(ll v, ll prntstg){
    lgst[v]=max(ldv0[v],1+prntstg);
    ll sn=sons[v].size();
    VI tl(sn+1,-INF);
    VI tr(sn+1,-INF);
    rng(i,1,sn+1){
        tl[i]=max(tl[i-1],ldv0[sons[v][i-1]]);
        tr[i]=max(tr[i-1],ldv0[sons[v][sn-i]]);
    }
    rng(i,0,sn){
        dfs2(sons[v][i],max(0LL,1+max(prntstg,max(tl[i],tr[sn-1-i]))));
    }
}

double calc(const VI &a, const VI &b, const VI &bsuf){
    ll an=a.size();
    ll bn=b.size();
    ll bar=max(a[an-1],b[bn-1]);

    ll acc=0;
    rng(ai,0,an){
        ll bi=lower_bound(b.begin(),b.end(),bar-a[ai]-1)-b.begin();
        acc+=bar*bi+bsuf[bn-bi]+(bn-bi)*(a[ai]+1);
    }
    return acc/double(an*bn);
}

int main()
{
    n=scan();
    ll m=scan();
    ll q=scan();
    rng(i,0,m){
        ll x=scan()-1,y=scan()-1;
        nb[x].push_back(y);
        nb[y].push_back(x);
    }
    rng(i,0,n){
        if (helloed[i]) continue;
        dfs(-1,i,comn);
        comroot[comn++]=i;
    }

    rng(i,0,n){
        ++comsize[com[i]];
    }

    rng(i,0,comn){
        dfs2(comroot[i],-INF);
    }

    rng(i,0,n){
        f[com[i]].push_back(lgst[i]);
    }
    rng(i,0,comn){
        sort(f[i].begin(),f[i].end());
        ll bn=comsize[i];
        bsuf[i].resize(bn+1);
        rng(j,1,bn+1){
            bsuf[i][j]=bsuf[i][j-1]+f[i][bn-j];
        }
    }

    map<ll,double> mem;
    rng(qi,0,q){
        ll x=scan()-1,y=scan()-1;
        ll X=com[x];
        ll Y=com[y];
        if (X==Y){
            printf("-1\n");
            continue;
        }
        ll key=(X<Y)?(X*comn+Y):(Y*comn+X);
        double ans;
        if (mem.find(key)==mem.end()){
            if (comsize[X]>comsize[Y]) swap(X,Y);
            ans=calc(f[X],f[Y],bsuf[Y]);
            mem[key]=ans;
        }else{
            ans=mem[key];
        }
        printf("%.9f\n",ans);
    }
    return 0;
}
