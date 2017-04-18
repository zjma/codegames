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
void scanll(ll &x) {int r;scanf("%d",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


int main()
{
    ll n;scanll(n);
    set<ll> as;
    rng(i,0,n){
        ll x;scanll(x);
        as.insert(x);
    }
    vector<ll> bs;
    for (auto x:as){
        bs.push_back(x);
    }
    sort(bs.begin(),bs.end());
    bool ans;
    switch (bs.size()){
        case 1:
            ans=true;
            break;
        case 2:
            ans=true;
            break;
        case 3:
            ans=(bs[0]+bs[2]==2*bs[1]);
            break;
        default:
            ans=false;
    }
    if (ans) cout<<"YES"<<endl; else cout<<"NO"<<endl;
    return 0;
}
