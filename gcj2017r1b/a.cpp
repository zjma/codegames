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


int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll d;scanll(d);
        ll n;scanll(n);
        VI k(n);
        VI s(n);
        rng(i,0,n){
            scanll(k[i]);
            scanll(s[i]);
        }
        double anst=0;
        rng(i,0,n){
            double tt=(double(d-k[i]))/s[i];
            anst=max(anst,tt);
        }
        double ans=d/anst;
        cout.precision(9);
        cout<<"Case #"<<(ti+1)<<": "<<fixed<<ans<<endl;
    }
    return 0;
}
