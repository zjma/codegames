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

ll crossed(ll p0, ll p1, ll p2, ll p3){
    ll sg00=min(p0,p1);
    ll sg01=max(p0,p1);
    ll p2t=sg00<p2&&p2<sg01;
    ll p3t=sg00<p3&&p3<sg01;
    ll res=p2t!=p3t;
    return res;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll k=scan();
        VI pair(n*2,-1);
        rng(i,0,k){
            ll x = scan()-1;
            ll y = scan()-1;
            pair[x]=y;
            pair[y]=x;
        }
        VI todo;
        rng(i,0,n*2){
            if (pair[i]>=0) continue;
            todo.push_back(i);
        }
        ll tdn=todo.size();
        rng(i,0,tdn/2){
            pair[todo[i]]=todo[i+tdn/2];
            pair[todo[i+tdn/2]]=todo[i];
        }
        ll ans=0;
        rng(i,0,n*2){
            rng(j,0,n*2){
                if (i==j||i==pair[j]) continue;
                if (crossed(i,pair[i],j,pair[j])) {
                    ans++;
                }
            }
        }
        ans/=8;
        cout<<ans<<endl;
    }
    return 0;
}
