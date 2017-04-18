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
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

bool wit[1001];
ll V=1000000;
int main()
{
    ll n,k;scanll(n);scanll(k);
    vector<ll> px;
    vector<ll> qx;
    bool flag=false;
    rng(i,0,k){
        ll x;
        scanll(x);
        if (wit[x]) continue;
        wit[x]=true;
        x-=n;
        if (x==0) flag=true;
        if (x<0) qx.push_back(-x);
        if (x>0) px.push_back(x);
    }
    if (flag){
        cout<<1<<endl;
        return 0;
    }
    ll pn=px.size();
    ll qn=qx.size();
    if (pn==0||qn==0){
        cout<<-1<<endl;
        return 0;
    }
    vector<ll> p(V+1,INT_MAX);
    vector<ll> q(V+1,INT_MAX);
    p[0]=0;
    rng(i,0,pn){
        rng(j,px[i],V+1){
            p[j]=min(p[j],p[j-px[i]]+1);
        }
    }
    q[0]=0;
    rng(i,0,qn){
        rng(j,qx[i],V+1){
            q[j]=min(q[j],q[j-qx[i]]+1);
        }
    }

    ll ans=INT_MAX;
    rng(i,1,V+1){
        ans=min(ans,p[i]+q[i]);
    }
    cout<<ans<<endl;
    return 0;
}
