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

const ll N=100000;
ll v[N];
ll lft[N];
ll rgt[N];
ll prnt[N];

ll ans=0;

void check(ll i, ll lb, ll rb, set<ll> &reached){
    if (i<0) return;
    if (lb<=v[i]&&v[i]<=rb){
        reached.insert(v[i]);
        check(lft[i], lb, min(rb,v[i]-1), reached);
        check(rgt[i], max(lb,v[i]+1), rb, reached);
        reached.erase(v[i]);

    }else if (reached.find(v[i])!=reached.end()){
        check(lft[i], lb, min(rb,v[i]-1), reached);
        check(rgt[i], max(lb,v[i]+1), rb, reached);
    }else{
        ++ans;
        check(lft[i], lb, min(rb,v[i]-1), reached);
        check(rgt[i], max(lb,v[i]+1), rb, reached);
    }
}

int main()
{
    ll n;scanll(n);
    rng(i,0,n){
        prnt[i]=-1;
    }
    rng(i,0,n){
        ll x,y,z;scanll(x);scanll(y);scanll(z);--y;--z;
        lft[i]=y;
        rgt[i]=z;
        prnt[y]=prnt[z]=i;
        v[i]=x;
    }
    ll root;
    rng(i,0,n){
        if (prnt[i]<0) {root=i;break;}
    }
    set<ll> reached;
    check(root, INT_MIN, INT_MAX, reached);
    cout<<ans<<endl;
    return 0;
}
