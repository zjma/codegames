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

ll a[200000];
ll f0[200000];
ll f1[200000];
ll fa[200000];
ll fb[200000];

#define evens(ei) (a[(ei)*2])
#define odds(oi) ((oi<on)?a[(oi)*2+1]:(-INF));

int main()
{
    ll TN=scan();
    rng(TI,0,TN){
        ll n=scan();
        rng(i,0,n){
            a[i]=scan();
        }
        ll en=(n+1)/2;
        ll on=n/2;
        f0[0]=evens(0);
        fa[0]=-INF;
        fb[0]=odds(0);
        f1[0]=evens(0);
        rng(ei,1,en){
            f0[ei]=f0[ei-1]+evens(ei);
            fa[ei]=max(fa[ei-1],f0[ei-1])+odds(ei-1);
            fb[ei]=max(fb[ei-1],f0[ei-1])+odds(ei);
            f1[ei]=max(max(f0[ei-1],f1[ei-1]),max(fa[ei-1],fb[ei-1]))+evens(ei);
        }
        ll ans=max(max(f0[en-1],fa[en-1]),max(fb[en-1],f1[en-1]));
        cout<<ans<<endl;
    }
    return 0;
}
