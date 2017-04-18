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
using namespace std;


//type shortcuts
typedef long long ll;
typedef vector<ll> VI;
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;


//constants
const DOUBLE EPS=1e-9;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {int r;scanf("%d",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


/**
 * 1D generic segment tree. Lazy propgation & on-demand allocation.
 *
 * Allow 1 type of segmentable interval query(SUM/MAX),
 *       interval update by relative diff(each+1/each-lift-to-5), and
 *       interval update by value-setting(each-set-to-9)
 *
 * \param _l    left-most position
 * \param _r    right-most position
 * \param _v    initial element value
 * \param _fnx  query function I    (compute X+X+X+...+X)
 * \param _fab  query function II   (compute A+B)
 *
 * \usage
 *      double max_ab(double a, double b){return max(a,b);}
 *      double max_nx(int n,double x){return x;}
 *      LazySegTree1D<R> t(0,99,0.0,max_nx,max_ab);//query MAX(seg) on [0,99]
 *      tree.updres(1,6,2.2); //lift each to 2.2 on [1,6]
 *      tree.setval(0,5,1.1); //set each to 1.1 on [0,5]
 *      auto v=tree.get(2,7); // get maximum on [2,7]
 */

struct LazySegTree1D {
    vector<ll> v;
    vector<ll> opr;//0: set value; 1: update result; -1: idle
    vector<ll> opd;
    vector<ll> nxt;
    ll LEFT;
    ll RGHT;
    LazySegTree1D(ll _l, ll _r, ll _v)
        :v(1),opr(1),opd(1),nxt(1),LEFT(_l),RGHT(_r)
    {
        v[0]=(RGHT-LEFT+1)*_v;
        opr[0]=0;
        opd[0]=_v;
        nxt[0]=-1;
    }
    void _split(ll i, ll l0, ll r0){
        assert(nxt[i]==-1);
        assert(opr[i]==0);
        assert(l0<r0);
        ll n=v.size();
        nxt[i]=n;
        ll m0=(l0+r0)/2;
        v.push_back((m0-l0+1)*opd[i]);
        v.push_back((r0-m0)*opd[i]);
        opr.push_back(0);
        opr.push_back(0);
        opd.push_back(opd[i]);
        opd.push_back(opd[i]);
        nxt.push_back(-1);
        nxt.push_back(-1);
    }
    void _pushdown(ll i, ll l0, ll r0){
        if (opr[i]==-1) return;
        ll m0=(l0+r0)/2;
        if (nxt[i]==-1)
            _split(i,l0,r0);
        else if (opr[i]>=0){
            _set(nxt[i],l0,m0,l0,m0,opr[i],opd[i]);
            _set(nxt[i]+1,m0+1,r0,m0+1,r0,opr[i],opd[i]);
        }
        opr[i]=-1;
    }
    void _set(ll i, ll l0, ll r0, ll l1, ll r1, ll o1, ll v1){
        assert(l1>=l0&&r1<=r0);
        if (l0==l1&&r0==r1){
            v[i]=(r0-l0+1)*v1;
            opr[i]=0;opd[i]=v1;
            return;
        }
        ll m0=(l0+r0)/2;
        _pushdown(i,l0,r0);
        if (l1<=m0) _set(nxt[i],l0,m0,l1,min(r1,m0),o1,v1);
        if (r1>m0) _set(nxt[i]+1,m0+1,r0,max(l1,m0+1),r1,o1,v1);
        v[i]=v[nxt[i]]+v[nxt[i]+1];
    }
    ll _get(ll i, ll l0, ll r0, ll l1, ll r1){
        assert(l0<=l1&&r1<=r0);
        if (l0==l1&&r1==r0) return v[i];
        _pushdown(i,l0,r0);
        ll m0=(l0+r0)/2;
        if (r1<=m0) return _get(nxt[i],l0,m0,l1,r1);
        if (m0+1<=l1) return _get(nxt[i]+1,m0+1,r0,l1,r1);
        ll lv=_get(nxt[i],l0,m0,l1,m0);
        ll rv=_get(nxt[i]+1,m0+1,r0,m0+1,r1);
        return lv+rv;
    }
    void set(ll l1, ll r1, ll v1){_set(0,LEFT,RGHT,l1,r1,0,v1);}
    ll get(ll l1, ll r1){return _get(0,LEFT,RGHT,l1,r1);}
};


int main()
{
    ll n,q;scanll(n);scanll(q);
    LazySegTree1D tree(0,q-1,0);
    vector<vector<pair<ll,ll>>> v2sg(n);
    vector<ll> stamp;
    rng(i,0,q){
        ll tp,x;scanll(tp);scanll(x);
        if (tp==1){
            stamp.push_back(i);
            --x;
            ll sz=v2sg[x].size();
            if (sz==0){
                v2sg[x].push_back(make_pair(i,i));
            }else{
                ll f,t;tie(f,t)=v2sg[x].back();
                if (t==i-1)
                    v2sg[x][sz-1]=make_pair(f,i);
                else
                    v2sg[x].push_back(make_pair(i,i));
            }
            tree.set(i,i,1);
        }else if (tp==2){
            --x;
            for (auto pr:v2sg[x]){
                tree.set(pr.first,pr.second,0);
            }
            v2sg[x].clear();
        }else{
            ll when=stamp[x-1];
            tree.set(0,when,0);
        }
        cout<<tree.get(0,i)<<endl;
    }
    return 0;
}
