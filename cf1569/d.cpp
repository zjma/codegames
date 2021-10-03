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
typedef tuple<ll,ll,ll> L3;
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
void dump(VI &arr){
    for(auto item:arr){
        cerr<<item<<' ';
    }
    cerr<<endl;
}

ll getSubAns(map<ll,ll> &b2c){
    ll ans=0;
    ll presum=0;
    for (auto const&bc:b2c){
        ans+=bc.second*presum;
        presum+=bc.second;
    }
    return ans;
}

ll calc(vector<L3> &people, VI &xsidLeft, VI &xsidRight, VI &ysidDown, VI &ysidUp){
    ll k=people.size();
    map<ll,ll> b2c;
    ll ans=0;
    rng(i,0,k){
        ll x,y,pid;
        ll x2,y2,pid2;
        ll x0,y0,pid0;
        tie(x,y,pid)=people[i];
        tie(x2,y2,pid2)=(i<k-1)?people[i+1]:make_tuple(0ll,0ll,0ll);
        tie(x0,y0,pid0)=(i>0)?people[i-1]:make_tuple(0ll,0ll,0ll);
        if (xsidLeft[pid]<xsidRight[pid]&&ysidDown[pid]==ysidUp[pid]){
            if (i==0||xsidRight[pid0]<xsidRight[pid]){
            }
            b2c[ysidDown[pid]]++;
            if (i==k-1||xsidLeft[pid]<xsidLeft[pid2]) {
                ans+=getSubAns(b2c);
                b2c.clear();
            }
        }
    }
    return ans;
}


int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll m=scan();
        ll k=scan();
        VI x(n);
        rng(i,0,n){
            x[i]=scan();
        }
        VI y(m);
        rng(i,0,m){
            y[i]=scan();
        }
        vector<L3> pxys(k);
        vector<L3> pyxs(k);
        VI xsidLeft(k);
        VI xsidRight(k);
        VI ysidDown(k);
        VI ysidUp(k);
        rng(i,0,k){
            ll px=scan();
            ll py=scan();
            xsidRight[i]=lower_bound(x.begin(),x.end(),px)-x.begin();
            xsidLeft[i]=(x[xsidRight[i]]==px)?xsidRight[i]:(xsidRight[i]-1);
            ysidUp[i]=lower_bound(y.begin(),y.end(),py)-y.begin();
            ysidDown[i]=(y[ysidUp[i]]==py)?ysidUp[i]:(ysidUp[i]-1);
            pxys[i]=make_tuple(px,py,i);
            pyxs[i]=make_tuple(py,px,i);
        }
        sort(pxys.begin(),pxys.end());
        sort(pyxs.begin(),pyxs.end());
        ll ans=calc(pxys,xsidLeft,xsidRight,ysidDown,ysidUp)+calc(pyxs,ysidDown,ysidUp,xsidLeft,xsidRight);
        cout<<ans<<endl;
    }
    return 0;
}
