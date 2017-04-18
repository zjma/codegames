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
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

ll solve(vector<ll>& w)
{
    sort(w.begin(),w.end());
    ll n=w.size();
    ll i=n-1;
    ll j=0;
    ll ans=0;
    while(1){
        ll atleast = ceil(50.0/w[i]);
        if (i-j+1<atleast) break;
        ++ans;
        --i;
        j+=atleast-1;
        if (i<j) break;
    }
    return ans;
}

int main()
{
    ll TN;scanll(TN);
    rng(TI,0,TN){
        ll n;scanll(n);
        vector<ll> w(n);
        rng(i,0,n) scanll(w[i]);
        cout<<"Case #"<<TI+1<<": "<< solve(w) << endl;
    }
    return 0;
}
