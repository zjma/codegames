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
const ll M = 998244353;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

char buf[262145];

const ll B=1313131;

ll hash2(char root, ll sub0, ll sub1) {
    ll ans=root;
    ans=mul(ans,add(sub0,B));
    ans=mul(ans,add(sub1,B));
    return ans;
}

void calc(ll cur, ll height, ll &ans, ll &digest){
    if (height==0){
        ans=1;
        digest=hash2(buf[cur],1,1);
        return;
    }
    ll leftans,leftdigest,rightans,rightdigest;
    calc(cur*2+1,height-1,leftans,leftdigest);
    calc(cur*2+2,height-1,rightans,rightdigest);
    ans=mul(leftans,rightans);
    if (leftdigest!=rightdigest){
        ans=mul(ans,2);
    }
    digest=hash2(buf[cur],min(leftdigest,rightdigest),max(leftdigest,rightdigest));
    // cerr<<"cur="<<cur<<", ans="<<ans<<" digest="<<digest<<endl;
}

ll work(){
    ll n=scan();
    scanstr(buf);
    ll ans,digest;
    calc(0,n-1,ans,digest);
    return ans;
}

int main()
{
    cout<<work()<<endl;
    return 0;
}
