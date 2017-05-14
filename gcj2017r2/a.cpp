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
        ll p=scan();
        VI ctr(p);
        rng(i,0,n){
            ll x=scan()%p;
            ctr[x]++;
        }
        ll ans;
        if (p==2){
            ans=ctr[0]+(ctr[1]+1)/2;
        }else if (p==3){
            ll x=min(ctr[2],ctr[1]);
            ll y=(2+max(ctr[2]-x,ctr[1]-x))/3;
            ans=ctr[0]+x+y;
        }else if (p==4){
            ll x=min(ctr[1],ctr[3]);
            ctr[1]-=x;
            ctr[3]-=x;
            if (ctr[3]>0) swap(ctr[1],ctr[3]);
            ll y=(3+ctr[1]+ctr[2]*2)/4;
            ans=ctr[0]+x+y;
        }
        cout<<"Case #"<<(ti+1)<<": "<<ans<<endl;
    }
    return 0;
}
