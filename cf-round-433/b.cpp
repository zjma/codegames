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

const ll MAXDAY=1000000;
const ll MAXCITY=100000;
int main()
{
    ll n=scan();
    ll m=scan();
    ll k=scan();
    vector<vector<pair<ll,ll>>> day2gotkts(MAXDAY+1);
    vector<vector<pair<ll,ll>>> day2leavetkts(MAXDAY+1);
    rng(i,0,m){
        ll d=scan();
        ll f=scan();
        ll t=scan();
        ll c=scan();
        if (f==0){
            day2leavetkts[d].emplace_back(t,c);
        }else{
            day2gotkts[d].emplace_back(f,c);
        }
    }

    vector<bool> allablego(MAXDAY+1);
    VI allgocost(MAXDAY+1);
    VI city2gocost(MAXCITY+1,INF);
    ll goableCount=0;
    ll tmpallgocost=0;
    rng(i,1,MAXDAY+1){
        allablego[i]=(goableCount==n);
        allgocost[i]=tmpallgocost;
        for (auto pr:day2gotkts[i]){
            ll hcity,cost;tie(hcity,cost)=pr;
            if (city2gocost[hcity]==INF){
                ++goableCount;
                city2gocost[hcity]=cost;
                tmpallgocost+=cost;
            }else{
                tmpallgocost-=city2gocost[hcity];
                city2gocost[hcity]=min(city2gocost[hcity],cost);
                tmpallgocost+=city2gocost[hcity];
            }
        }
    }

    vector<bool> allableleave(MAXDAY+1);
    VI allleavecost(MAXDAY+1);
    VI city2leavecost(MAXCITY+1,INF);
    ll leavableCount=0;
    ll tmpallleavecost=0;
    for (ll i=MAXDAY;i>=1;--i){
        allableleave[i]=(leavableCount==n);
        allleavecost[i]=tmpallleavecost;
        for (auto pr:day2leavetkts[i]){
            ll hcity,cost;tie(hcity,cost)=pr;
            if (city2leavecost[hcity]==INF){
                ++leavableCount;
                city2leavecost[hcity]=cost;
                tmpallleavecost+=cost;
            }else{
                tmpallleavecost-=city2leavecost[hcity];
                city2leavecost[hcity]=min(city2leavecost[hcity],cost);
                tmpallleavecost+=city2leavecost[hcity];
            }
        }
    }

    ll ans=INF;
    rng(startday,1,MAXDAY+1){
        ll endday=startday+k-1;
        if (endday>MAXDAY) continue;
        if (!allablego[startday]) continue;
        if (!allableleave[endday]) continue;
        ans=min(ans,allgocost[startday]+allleavecost[endday]);
    }
    if (ans==INF) ans=-1;
    cout<<ans<<endl;
    return 0;
}
