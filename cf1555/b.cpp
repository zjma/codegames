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
        ll W=scan();
        ll H=scan();
        ll x1=scan();
        ll y1=scan();
        ll x2=scan();
        ll y2=scan();
        ll w=scan();
        ll h=scan();
        ll ans=INF;
        ll gx1=W-x2;
        ll gy1=y1;
        ll ox1=max(0ll,w-x1);
        ll oy1=max(0ll,y2-H+h);
        ll ans1=(ox1>gx1&&oy1>gy1)?INF:(ox1>gx1)?oy1:(oy1>gy1)?ox1:min(ox1,oy1);
        ans=min(ans,ans1);

        ll gx2=x1;
        ll gy2=y1;
        ll ox2=max(0ll,x2-W+w);
        ll oy2=max(0ll,y2-H+h);
        ll ans2=(ox2>gx2&&oy2>gy2)?INF:(ox2>gx2)?oy2:(oy2>gy2)?ox2:min(ox2,oy2);
        ans=min(ans,ans2);

        ll gx3=x1;
        ll gy3=H-y2;
        ll ox3=max(0ll,x2-W+w);
        ll oy3=max(0ll,h-y1);
        ll ans3=(ox3>gx3&&oy3>gy3)?INF:(ox3>gx3)?oy3:(oy3>gy3)?ox3:min(ox3,oy3);
        ans=min(ans,ans3);

        ll gx4=W-x2;
        ll gy4=H-y2;
        ll ox4=max(0ll,w-x1);
        ll oy4=max(0ll,h-y1);
        ll ans4=(ox4>gx4&&oy4>gy4)?INF:(ox4>gx4)?oy4:(oy4>gy4)?ox4:min(ox4,oy4);
        ans=min(ans,ans4);
        if (ans==INF) ans=-1;

        cout<<ans<<endl;
    }
    return 0;
}
