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
const ll MAXN=5000;
ll x;
ll n;
ll getMax(pair<ll,ll> &cand){
    return cand.first+x*cand.second;
}
ll psum[MAXN+1];
ll getValue(pair<ll,ll> &cand, ll k){
    return cand.first+x*min(k,cand.second);
};

ll work(){
    n=scan();
    x=scan();
    psum[0]=0;
    rng(i,0,n){
        ll cur=scan();
        psum[i+1]=psum[i]+cur;
    }

    vector<pair<ll,ll>> cands;
    cands.emplace_back(0,0);
    rng(i,1,n+1){
        ll curbase=-INF;
        rng(j,i,n+1){
            curbase=max(curbase,psum[j]-psum[j-i]);
        }
        cands.emplace_back(curbase,i);
    }
    sort(cands.begin(),cands.end());

    stack<pair<ll,ll>> stk;
    for(auto &cand:cands){
        while(!stk.empty()&&getMax(stk.top())<=getMax(cand)){
            stk.pop();
        }
        stk.push(cand);
    }

    pair<ll,ll> curCand=stk.top();
    stk.pop();
    rng(i,0,n+1){
        while(!stk.empty()&&getValue(stk.top(),i)>getValue(curCand,i)){
            curCand=stk.top();
            stk.pop();
        }
        ll curans=getValue(curCand,i);
        printf("%lld", curans);
        if(i==n)printf("\n");else printf(" ");
    }
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        work();
    }
    return 0;
}
