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

inline ll com2(ll x){
    return (x-1)*x/2;
}


struct BIT1D {
    ll n;
    VI v;
    ll rg(ll k){return ((k^(k+1))+1)/2;}
    BIT1D (ll _n) : v(_n) {n=_n;}
    void update(ll i, ll v1){
        for (;i<n;i+=rg(i)) v[i]+=v1;
    }
    ll query(ll i){
        ll j=i-rg(i);
        return (j<0)?v[i]:(query(j)+v[i]);
    }
};

int main()
{
    ll n=scan();
    ll q=scan();
    VI mark(n);
    rng(i,0,n){
        mark[scan()-1]=i;
    }

    vector<vector<tuple<ll,ll,ll>>> keypoints(n+1);
    VVI qv(q,VI(9));
    rng(i,0,q){
        ll l=scan();
        ll d=scan();
        ll r=scan();
        ll u=scan();
        keypoints[d-1].emplace_back(l-1,i,0);
        keypoints[d-1].emplace_back(r,i,1);
        keypoints[d-1].emplace_back(n,i,2);
        keypoints[u].emplace_back(l-1,i,3);
        keypoints[u].emplace_back(r,i,4);
        keypoints[u].emplace_back(n,i,5);
        keypoints[n].emplace_back(l-1,i,6);
        keypoints[n].emplace_back(r,i,7);
        keypoints[n].emplace_back(n,i,8);
    }
    BIT1D tree(n);
    for (auto tp:keypoints[0]){
        ll hcol,qi,zi;tie(hcol,qi,zi)=tp;
        qv[qi][zi] = 0;
    }
    rng(i,0,n){
        tree.update(mark[i],1);
        for(auto tp:keypoints[i+1]){
            ll hcol,qi,zi;tie(hcol,qi,zi)=tp;
            qv[qi][zi]=(hcol<=0)?0:tree.query(hcol-1);
        }
    }

    rng(i,0,q){
        qv[i][8]=qv[i][8]-qv[i][7]-qv[i][5]+qv[i][4];
        qv[i][7]=qv[i][7]-qv[i][6]-qv[i][4]+qv[i][3];
        qv[i][6]=qv[i][6]-qv[i][3];
        qv[i][5]=qv[i][5]-qv[i][2]-qv[i][4]+qv[i][1];
        qv[i][4]=qv[i][4]-qv[i][3]-qv[i][1]+qv[i][0];
        qv[i][3]=qv[i][3]-qv[i][0];
        qv[i][2]=qv[i][2]-qv[i][1];
        qv[i][1]=qv[i][1]-qv[i][0];
        ll ans=com2(n)
            -com2(qv[i][0]+qv[i][1]+qv[i][2])
            -com2(qv[i][0]+qv[i][3]+qv[i][6])
            -com2(qv[i][2]+qv[i][5]+qv[i][8])
            -com2(qv[i][6]+qv[i][7]+qv[i][8])
            +com2(qv[i][0])+com2(qv[i][2])+com2(qv[i][6])+com2(qv[i][8]);
        cout<<ans<<endl;
    }
    return 0;
}
