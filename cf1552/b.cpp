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

ll better(VVI &R, ll p0, ll p1){
    ll ct=0;
    rng(i,0,5){
        if (R[p0][i]<R[p1][i]) ct++;
    }
    if (ct>=3) return 1;
    return 0;
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VVI R(n,VI(5));
        rng(i,0,n){
            rng(j,0,5){
                R[i][j]=scan();
            }
        }
        ll ans=0;
        rng(i,1,n){
            if (better(R,i,ans)) ans=i;
        }
        ll nosol=0;
        rng(i,0,n){
            if (better(R,i,ans)) nosol=1;
        }
        if (nosol) cout<<-1<<endl; else cout<<(ans+1)<<endl;
    }
    return 0;
}
