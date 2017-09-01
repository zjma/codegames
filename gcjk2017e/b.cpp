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

ll comb3(ll n){
    return n*(n-1)*(n-2)/6;
}

ll comb2(ll n){
    return n*(n-1)/2;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        map<ll,ll> v2c;
        VI dv;
        ll tot=0;
        rng(i,0,n){
            ll x=scan();
            if (v2c[x]++==0) dv.push_back(x);
            ++tot;
        }
        ll dvn=dv.size();
        sort(dv.begin(),dv.end());
        VI dvc(dvn);
        rng(i,0,dvn){
            dvc[i]=v2c[dv[i]];
        }

        ll ans2=0;
        rng(ai,0,dvn){
            ll a=dv[ai];
            ll tmp=0;
            ll xi=dvn-1;
            for(ll bi=dvn-1; bi>ai; --bi){
                ll b=dv[bi];
                ll xbottom=(b-a+2)/2;
                while (xi>=0){
                    if (dv[xi]<xbottom) break;
                    tmp+=comb2(dvc[xi]);
                    --xi;
                }
                ll fix=0;
                if (xi<bi) fix+=comb2(dvc[bi]);
                if (xi<ai) fix+=comb2(dvc[ai]);
                ans2+=dvc[ai]*dvc[bi]*(tmp-fix);
            }
        }

        ll ans3=0;
        rng(xi,0,dvn){
            ll x=dv[xi];
            rng(ai,0,dvn){
                ll a=dv[ai];
                if (a==x) continue;
                if (a>x*3-1) continue;
                ans3+=comb3(dvc[xi])*dvc[ai];
            }
        }
        ll ans=ans2+ans3;
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
