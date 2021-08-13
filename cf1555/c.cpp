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
const ll MC=100000;
ll A[2][MC];
ll G[2][MC];
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll m=scan();
        rng(i,0,2){
            rng(j,0,m){
                A[i][j]=scan();
            }
        }
        G[0][0]=G[1][0]=0;
        rng(i,0,m){
            G[0][i+1]=G[0][i]+A[0][m-1-i];
            G[1][i+1]=G[1][i]+A[1][i];
        }
        ll ans=INF;
        rng(i,0,m){
            ll curBob=max(G[0][m-1-i],G[1][i]);
            ans=min(ans,curBob);
        }
        cout<<ans<<endl;
    }
    return 0;
}
