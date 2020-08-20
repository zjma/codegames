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
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)
void dumpVI(VI &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        cerr<<pfx<<"["<<i<<"]="<<a[i]<<endl;
    }
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void readArr(ll n, ll k, VI &Arr){
    rng(i,0,k){
        Arr[i]=scan();
    }
    ll A=scan();
    ll B=scan();
    ll C=scan();
    ll D=scan();
    rng(i,k,n){
        Arr[i]=(A*Arr[i-2]+B*Arr[i-1]+C)%D+1;
    }
}

ll solve(ll n, ll w, const VI &L, const VI &H){
    ll ans=1;
    ll cur=0;
    deque<tuple<ll,ll>> q;//(x,y): pos x has bar of height y
    ll lastR=0;
    rng(i,0,n){
        ll R=L[i]+w;
        while(!q.empty()&&get<0>(q.front())<L[i]) q.pop_front();
        ll old_height_at_L=q.empty()?0:get<1>(q.front());
        while(!q.empty()&&get<1>(q.back())<=H[i]) q.pop_back();
        q.emplace_back(R,H[i]);
        ll vdiff=max(0LL,H[i]-old_height_at_L)*2;
        ll hdiff=(R-max(lastR,L[i]))*2;
        lastR=R;
        cur+=hdiff+vdiff;
        ans=mul(ans,cur);
    }
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();ll k=scan();ll w=scan();
        VI L(n);
        VI H(n);
        readArr(n,k,L);
        readArr(n,k,H);
        ll ans=solve(n,w,L,H);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
