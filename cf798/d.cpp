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
    VI a(n); rng(i,0,n) a[i]=scan();
    VI b(n); rng(i,0,n) b[i]=scan();
    vector<pair<ll,ll>> f(n);
    rng(i,0,n) f[i]=make_pair(-a[i],i);
    sort(f.begin(),f.end());
    VI c(n); rng(i,0,n) c[i]=f[i].second;

    VI ans;
    ans.push_back(c[0]);

    rng(i,0,(n-1)/2){
        ll j=i*2+1;
        if (b[c[j]]>=b[c[j+1]]){
            ans.push_back(c[j]);
        }else{
            ans.push_back(c[j+1]);
        }
    }
    if (n%2==0){
        ans.push_back(c[n-1]);
    }
    cout<<ans.size()<<endl;
    for (auto x:ans){
        cout<<(x+1)<<" ";
    }cout<<endl;
    return 0;
}
