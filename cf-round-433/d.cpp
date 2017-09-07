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
    ll n=scan();
    VI daycost(n);
    rng(i,0,n){
        daycost[i]=scan()/100;
    }
    VVI f(n+1,VI(32,INF));
    f[0][0]=0;
    rng(i,1,n+1){
        ll bonustoday=daycost[i-1]/10;
        rng(k,1,daycost[i-1]+1){
            f[i][0]=min(f[i][0],f[i-1][k]+daycost[i-1]-k);//k by card, then a[i]-k by cash
        }
        rng(x,0,32){
            if (x>=bonustoday) f[i][x]=min(f[i][x],f[i-1][x-bonustoday]+daycost[i-1]);//all by cash
            if (x+daycost[i-1]<32) f[i][x]=min(f[i][x],f[i-1][x+daycost[i-1]]);//all by card
        }
    }
    ll ans=INF;
    rng(i,0,32){
        ans=min(ans,f[n][i]);
    }
    ans*=100;
    cout<<ans<<endl;
    return 0;
}
