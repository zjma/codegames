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


int main()
{
    ll n;scanll(n);
    vector<ll> f(n);
    rng(i,0,n){
        scanll(f[i]);f[i]-=i;
    }
    priority_queue<pair<ll,ll>> dt;//height,weight
    ll cost=0;
    rng(i,0,n){
        while (true){
            ll dn=dt.size();
            if (dn==0){
                dt.emplace(f[i],1);
                break;
            }
            if (dn==1){
                ll h0,w0;tie(h0,w0)=dt.top();
                if (f[i]>=h0){
                    dt.emplace(f[i],1);
                    break;
                }
                dt.pop();
                if (w0==1){
                    cost+=h0-f[i];
                    dt.emplace(f[i],2);
                    break;
                }
                cost+=h0-f[i];
                dt.emplace(h0,w0-1);
                dt.emplace(f[i],-1);
                break;
            }
            ll h0,w0,h1,w1;
            tie(h0,w0)=dt.top();
            if (f[i]>=h0){
                dt.emplace(f[i],1);
                break;
            }
            dt.pop();
            if (w0>=2){
                cost+=h0-f[i];
                dt.emplace(h0,w0-1);
                dt.emplace(f[i],1);
                break;
            }
            tie(h1,w1)=dt.top();
            if (f[i]>h1){
                cost+=h0-f[i];
                dt.emplace(f[i],w0+1);
                break;
            }
            dt.pop();
            cost+=h0-h1;
            dt.emplace(h1,w0+w1);
        }
    }
    cout<<cost<<endl;
    return 0;
}
