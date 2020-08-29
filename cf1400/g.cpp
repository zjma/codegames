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
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a / b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}
ll inv(ll a) {
    ll x,y;
    ll d=extended_euclid(a,M,x,y);
    if (d>1) return -1;
    return mod(x);
}


//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

void dumpVI(const string &title, const VI &a){
    ll n=a.size();
    rng(i,0,n){
        cerr<<title<<"["<<i<<"]="<<a[i]<<endl;
    }
}

string maskToString(ll length, ll mask){
    string result;
    rng(i,0,length){
        if (mask&(1<<(length-1-i))) {
            result.push_back('1');
        }else{
            result.push_back('0');
        }
    }
    return result;
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

VI factoral;
void initFactoral(ll n){
    factoral.resize(n+1);
    factoral[0]=1;
    rng(i,0,n){
        factoral[i+1]=mul(factoral[i],i+1);
    }
}

ll choose(ll n, ll k){
    if (k<0||k>n) return 0;
    return mul(factoral[n],mul(inv(factoral[k]),inv(factoral[n-k])));
}

int main()
{
    ll n=scan();
    ll m=scan();
    initFactoral(n);
    VVI loToMers(n+1);
    VVI hiToMers(n+1);
    rng(i,0,n){
        ll lo=scan();
        ll hi=scan();
        loToMers[lo].push_back(i);
        hiToMers[hi].push_back(i);
    }
    VI e2f(m);
    VI e2t(m);
    set<ll> sp_mer_set;
    rng(i,0,m){
        e2f[i]=scan()-1;
        e2t[i]=scan()-1;
        sp_mer_set.insert(e2f[i]);
        sp_mer_set.insert(e2t[i]);
    }

    ll ver_count=0;
    VI mer_to_ver(n,-1);
    for (auto mer:sp_mer_set){
        mer_to_ver[mer]=ver_count++;
    }

    VI haterset(ver_count);
    rng(i,0,m){
        ll v0=mer_to_ver[e2f[i]];
        ll v1=mer_to_ver[e2t[i]];
        haterset[v0]|=1<<v1;
        haterset[v1]|=1<<v0;
    }

    VVI dp(1<<ver_count,VI(ver_count+1));
    rng(k,0,ver_count+1){
        if (k==0){
            rng(mask,0,1<<ver_count) dp[mask][0]=1;
        }else{
            dp[0][k]=0;
            rng(mask,1,1<<ver_count){
                ll ver_least=__builtin_ctzll(mask);
                dp[mask][k]=add(dp[mask-(1<<ver_least)][k],dp[(mask-(1<<ver_least))&(~haterset[ver_least])][k-1]);
            }
        }
    }

    ll ans=0;
    ll inGraphMask=0;
    ll individualCount=0;
    rng(mer_number,1,n+1){
        for (auto mer:loToMers[mer_number]){
            if (mer_to_ver[mer]<0){
                individualCount++;
            }else{
                inGraphMask|=(1<<mer_to_ver[mer]);
            }
        }
        rng(fromgraph_number,0,min(mer_number,ver_count)+1){
            ll fromGraphContri=dp[inGraphMask][fromgraph_number];
            ll fromIndividualContri=choose(individualCount,mer_number-fromgraph_number);
            ll cur=mul(fromGraphContri,fromIndividualContri);
            ans=add(ans,cur);
        }
        for (auto mer:hiToMers[mer_number]){
            if (mer_to_ver[mer]<0){
                individualCount--;
            }else{
                inGraphMask&=~(1<<mer_to_ver[mer]);
            }
        }
    }

    cout<<ans<<endl;
    return 0;
}
