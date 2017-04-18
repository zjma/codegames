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

#define inrange(x) ((x)<=l&&(x)>=-l)

ll calc(ll b0, ll q, ll l, map<ll,bool> &bad){
    if (b0==0){
        if (!bad[0]) return -1;
        return 0;
    }
    if (q==0){
        if (!inrange(b0)){
            return 0;
        }
        if (bad[b0]){
            if (bad[0]) return 0;
            return -1;
        }else{
            if (bad[0]) return 1;
            return -1;
        }
    }
    if (q==1){
        if (inrange(b0)&&!bad[b0]) return -1;
        return 0;
    }
    if (q==-1){
        if (!inrange(b0)) return 0;
        if (bad[b0]&&bad[-b0]) return 0;
        return -1;
    }
    ll x=b0;
    ll ans=0;
    while (inrange(x)){
        if (!bad[x]) ++ans;
        x*=q;
    }
    return ans;
}


int main()
{
    ll b0,q,l,m;scanll(b0);scanll(q);scanll(l);scanll(m);
    map<ll,bool> bad;
    rng(i,0,m){
        ll x;        scanll(x);
        bad[x]=true;;
    }
    ll ans=calc(b0,q,l,bad);
    if (ans<0) cout<<"inf"<<endl;
    else cout<<ans<<endl;
    return 0;
}
