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

bool check(ll p, ll f, ll ns, ll nw, ll cs, ll cw, ll target){
    ll target_s,target_w;
    if (cs<cw){
        target_s=min(target,ns);
        target_w=target-target_s;
    }else{
        target_w=min(target,nw);
        target_s=target-target_w;
    }
    ll demand=target_s*cs+target_w*cw;
    if (demand>p+f) return false;
    rng(xs,0,min(ns,min(target_s,p/cs))+1){
        ll xw_min=max(0ll,(demand-f-cs*xs+cw-1)/cw);
        ll xw_max=min(target_w,min(nw,(p-cs*xs)/cw));
        if (xw_min<=xw_max) return true;
    }
    return false;
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll p=scan();
        ll f=scan();
        ll ns=scan();
        ll nw=scan();
        ll cs=scan();
        ll cw=scan();
        ll v0=0,v1=ns+nw+1;
        while(v0+1<v1){
            ll vm=(v0+v1)/2;
            if (check(p,f,ns,nw,cs,cw,vm)){
                v0=vm;
            }else{
                v1=vm;
            }
        }
        cout<<v0<<endl;
    }
    return 0;
}
