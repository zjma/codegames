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

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll m=scan();
        VVI f(n,VI(m));
        ll r0=(m+1)/2;
        rng(i,0,r0){
            f[0][i*2]=1;
        }
        ll c1=(n-1)/2;
        rng(i,0,c1){
            f[2+i*2][m-1]=1;
        }
        ll r1=(m-1)/2;
        rng(i,0,r1){
            f[n-1][m-3-i*2]=1;
        }
        ll c0=(n-3)/2;
        rng(i,0,c0){
            f[n-3-i*2][0]=1;
        }
        rng(i,0,n){
            rng(j,0,m){
                cout<<f[i][j];
            }
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}
