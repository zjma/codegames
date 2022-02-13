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
ll ceildiv(ll a, ll b){
    return (a+b-1)/b;
}
string work(){
    ll hc=scan();
    ll dc=scan();
    ll hm=scan();
    ll dm=scan();
    ll k=scan();
    ll w=scan();
    ll a=scan();
    //exists k1, k2 such that fight(hc+k1*a, dc+k2*w, hm, dm)=win?
    //where k1+k2<=k
    //fight(h1,d1,h2,d2)==win <=> ceil(h2/d1)<=ceil(h1/d2)
    //<=> ceil(h2/(dc+w*k2))<=ceil((h1+a*k1)/d2)
    rng(k1,0,(k+1)){
        ll k2=k-k1;
        if (ceildiv(hm,(dc+w*k2))<=ceildiv(hc+a*k1,dm)) {
            return "YES";
        }
    }
    return "NO";
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        cout<<work()<<endl;
    }
    return 0;
}
