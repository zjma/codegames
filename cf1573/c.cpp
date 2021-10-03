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

ll work(VI &v2e0, VI&e2nxt, VI&e2dst) {
    ll n=v2e0.size();
    ll en=e2nxt.size();
    VI ind(n);
    rng(i,0,en){
        ind[e2dst[i]]++;
    }
    queue<pair<ll,ll>> q;
    rng(i,0,n){
        if (ind[i]==0){
            q.push(make_pair(i,0));
        }
    }
    ll processed=0;
    VI earlistIt(n);
    while(!q.empty()){
        ll cur,dep;
        tie(cur,dep)=q.front();
        q.pop();
        processed++;
        for(ll ei=v2e0[cur];ei>=0;ei=e2nxt[ei]){
            ll nxt=e2dst[ei];
            ll newdep=(nxt>cur)?dep:(dep+1);
            ind[nxt]--;
            earlistIt[nxt]=max(earlistIt[nxt],newdep);
            if (ind[nxt]==0){
                q.push(make_pair(nxt,earlistIt[nxt]));
            }
        }
    }
    if (processed<n) return -1;
    ll ans=0;
    rng(i,0,n){
        ans=max(ans,earlistIt[i]);
    }
    return ans+1;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI v2e0(n,-1);
        VI e2nxt;
        VI e2dst;
        rng(i,0,n){
            ll k=scan();
            rng(j,0,k){
                ll a=scan()-1;//a->i
                e2dst.push_back(i);
                e2nxt.push_back(v2e0[a]);
                v2e0[a]=e2dst.size()-1;
            }
        }
        cout<<work(v2e0,e2nxt,e2dst)<<endl;
    }
    return 0;
}
