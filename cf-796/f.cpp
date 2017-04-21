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
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

inline ll bitof(ll i, ll v){
    return (v&(1<<i))>>i;
}

struct MinSegTree {
    vector<ll> v;
    vector<ll> opr;//0: set value; 1: updres result; -1: idle
    vector<ll> opd;
    vector<ll> nxt;
    ll LEFT;
    ll RGHT;
    MinSegTree(ll _l, ll _r, ll _v)
        :v(1),opr(1),opd(1),nxt(1),LEFT(_l),RGHT(_r)
    {
        v[0]=_v;
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
        v.push_back(opd[i]);
        v.push_back(opd[i]);
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
            if (o1==0){
                v[i]=v1;
                opr[i]=0;opd[i]=v1;
            }else if (o1==1){
                v[i]=min(v[i],v1);
                if (opr[i]==-1){
                    opr[i]=1;opd[i]=v1;
                }else if (opr[i]==0){
                    opr[i]=0;opd[i]=min(opd[i],v1);
                }else if (opr[i]==1){
                    opr[i]=1;opd[i]=min(opd[i],v1);
                }
            }
            return;
        }
        ll m0=(l0+r0)/2;
        _pushdown(i,l0,r0);
        if (l1<=m0) _set(nxt[i],l0,m0,l1,min(r1,m0),o1,v1);
        if (r1>m0) _set(nxt[i]+1,m0+1,r0,max(l1,m0+1),r1,o1,v1);
        v[i]=min(v[nxt[i]],v[nxt[i]+1]);
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
        return min(lv,rv);
    }
    void updres(ll l1, ll r1, ll v1){_set(0,LEFT,RGHT,l1,r1,1,v1);}
    void setval(ll l1, ll r1, ll v1){_set(0,LEFT,RGHT,l1,r1,0,v1);}
    ll get(ll l1, ll r1){return _get(0,LEFT,RGHT,l1,r1);}
};

struct MaxSegTree {
    vector<ll> v;
    vector<ll> opr;//0: set value; 1: updres result; -1: idle
    vector<ll> opd;
    vector<ll> nxt;
    ll LEFT;
    ll RGHT;
    MaxSegTree(ll _l, ll _r, ll _v)
        :v(1),opr(1),opd(1),nxt(1),LEFT(_l),RGHT(_r)
    {
        v[0]=_v;
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
        v.push_back(opd[i]);
        v.push_back(opd[i]);
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
            if (o1==0){
                v[i]=v1;
                opr[i]=0;opd[i]=v1;
            }else if (o1==1){
                v[i]=max(v[i],v1);
                if (opr[i]==-1){
                    opr[i]=1;opd[i]=v1;
                }else if (opr[i]==0){
                    opr[i]=0;opd[i]=max(opd[i],v1);
                }else if (opr[i]==1){
                    opr[i]=1;opd[i]=max(opd[i],v1);
                }
            }
            return;
        }
        ll m0=(l0+r0)/2;
        _pushdown(i,l0,r0);
        if (l1<=m0) _set(nxt[i],l0,m0,l1,min(r1,m0),o1,v1);
        if (r1>m0) _set(nxt[i]+1,m0+1,r0,max(l1,m0+1),r1,o1,v1);
        v[i]=max(v[nxt[i]],v[nxt[i]+1]);
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
        return max(lv,rv);
    }
    void updres(ll l1, ll r1, ll v1){_set(0,LEFT,RGHT,l1,r1,1,v1);}
    void setval(ll l1, ll r1, ll v1){_set(0,LEFT,RGHT,l1,r1,0,v1);}
    ll get(ll l1, ll r1){return _get(0,LEFT,RGHT,l1,r1);}
};

inline ll acute(ll x){
    ll t1=x|(x>>1);
    ll t2=t1|(t1>>2);
    ll t3=t2|(t2>>4);
    ll t4=t3|(t3>>8);
    ll t5=t4|(t4>>16);
    return t5;
}

int main()
{
    ll n;scanll(n);
    ll m;scanll(m);
    VI q0(m);
    VI q1(m);
    VI q2(m);
    VI q3(m);
    rng(i,0,m){
        scanll(q0[i]);
        if (q0[i]==1){
            scanll(q1[i]);--q1[i];
            scanll(q2[i]);--q2[i];
            scanll(q3[i]);
        }else{
            scanll(q1[i]);--q1[i];
            scanll(q2[i]);
        }
    }
    MinSegTree tree(0,n-1,1000000009);
    VI iv(n,-1);
    rng(i,0,m){
        if (q0[i]==1){
            tree.updres(q1[i],q2[i],q3[i]);
        }else{
            iv[q1[i]]=tree.get(q1[i],q1[i]);
        }
    }
    rng(i,0,n){
        if (iv[i]==-1) iv[i]=tree.get(i,i);
    }
    //rng(i,0,n)cerr<<iv[i]<<" ";cerr<<endl;

    MaxSegTree tree2(0,n-1,0);
    rng(i,0,n){
        tree2.setval(i,i,iv[i]);
    }

    rng(i,0,m){
        if (q0[i]==1){
            if (q3[i]!=tree2.get(q1[i],q2[i])){
                cout<<"NO"<<endl;
                return 0;
            }
        }else{
            tree2.setval(q1[i],q1[i],q2[i]);
        }
    }

    map<ll,ll> v2c;
    rng(i,0,n){
        ++v2c[iv[i]];
    }
    rng(i,0,n){
        if (iv[i]!=1000000009&&v2c[iv[i]]>=2){
            --v2c[iv[i]];
            iv[i]=acute(iv[i])>>1;
        }
    }
    if (v2c[1000000009]>=2){
        ll lastp;
        rng(i,0,n){
            if (iv[i]==1000000009){
                iv[i]=1000000000;
                lastp=i;
            }
        }
        iv[lastp]=536870911;
    }else if (v2c[1000000009]==1){
        ll bst=0;
        ll lastp=-1;
        rng(i,0,n){
            if (iv[i]!=1000000009){
                bst|=iv[i];
            }else{
                lastp=i;
            }
        }
        ll ideal=((1<<30)-1)^bst;
        ll bstcmt=0;
        ll st=0;
        rng(i,0,30){
            ll thisbit;
            bool wannathis1=bitof(29-i,ideal)==1;
            if (st==1){
                thisbit=1;
            }else if (!wannathis1){
                thisbit=0;
                st=(bitof(29-i,1000000000)==1)?1:0;
            }else{
                thisbit=bitof(29-i,1000000000);
            }
            bstcmt=bstcmt*2+thisbit;
        }
        iv[lastp]=bstcmt;
    }
    cout<<"YES"<<endl;
    rng(i,0,n){
        cout<<iv[i]<<" ";
    }cout<<endl;
    return 0;
}
