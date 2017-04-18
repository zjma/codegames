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

const ll N=100000;
ll a[N];
ll n;

#define makekey(p,k) ((p)*1000000+(k))
map<ll,ll> ans;

ll calc(ll p, ll k){
    ll crtkey=makekey(p,k);
    if (ans.find(crtkey)==ans.end()){
        if (p+a[p-1]+k>n){
            ans[crtkey]=1;
        }else{
            ans[crtkey]=calc(p+a[p-1]+k,k)+1;
        }
    }
    return ans[crtkey];
}

int main()
{
    scanll(n);
    rng(i,0,n){
        scanll(a[i]);
    }
    ll qn;scanll(qn);
    rng(qi,0,qn){
        ll p,k;scanll(p);scanll(k);
        cout<<calc(p,k)<<endl;
    }
    return 0;
}
