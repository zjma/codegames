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

bool isblack(ll ri, ll ci){
    return (ri+ci)%2==0;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll m=scan();
        ll k=scan();
        ll xri=scan();
        ll xci=scan();
        VI hri(k);
        VI hci(k);
        rng(i,0,k){
            hri[i]=scan();
            hci[i]=scan();
        }
        string ans=(k==1)?"N":(isblack(hri[0],hci[0])==isblack(hri[1],hci[1])&&isblack(hri[1],hci[1])!=isblack(xri,xci))?"Y":"N";
        printf("Case #%lld: %s\n",ti+1,ans);
    }
    return 0;
}
