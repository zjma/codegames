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

ll mod(ll x, ll M) { return ((x%M) + M) % M; }

ll get_feat_match(ll f0, ll f1){
    return mod(-(f0+f1),3);
}

ll get_match(VI &card0, VI &card1){
    ll k=card0.size();
    ll val=0;
    rng(i,0,k){
        ll cur_dig=get_feat_match(card0[i],card1[i]);
        val=val*3+cur_dig;
    }
    return val;
}

int main()
{
    ll n=scan();
    ll k=scan();
    VVI C(n,VI(k));
    set<ll> card_set;
    rng(i,0,n){
        ll card_val=0;
        rng(j,0,k){
            C[i][j]=scan();
            card_val=card_val*3+C[i][j];
        }
        card_set.insert(card_val);
    }
    map<ll,ll> match_count_of;
    rng(i,0,n){
        rng(j,i+1,n){
            ll wanted=get_match(C[i],C[j]);
            if (card_set.find(wanted)!=card_set.end()){
                match_count_of[wanted]+=1;
            }
        }
    }

    ll ans=0;
    for(auto &kv:match_count_of){
        ans+=kv.second*(kv.second-1)/2;
    }
    printf("%lld\n", ans);
    return 0;
}
