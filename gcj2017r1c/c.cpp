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
        ll n,k;cin>>n>>k;
        double u;cin>>u;
        VD p(n);
        rng(i,0,n){
            cin>>p[i];
        }
        sort(p.begin(),p.end());
        ll m=1;
        while (m<=n&&u>EPS){
            double nextlevel=(m<n)?p[m]:1;
            double gap=m*(nextlevel-p[m-1]);
            double toconsume=min(u,gap);
            u-=toconsume;
            double eachup=toconsume/m;
            rng(i,0,m){
                p[i]+=eachup;
            }
            ++m;
        }
        double ans=1;
        rng(i,0,n){
            ans*=p[i];
        }
        cout.precision(9);
        cout<<"Case #"<<(ti+1)<<": "<<fixed<<ans<<endl;
    }
    return 0;
}
