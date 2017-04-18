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
const DOUBLE EPS=1e-6;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}



int main()
{
    ll n;scanll(n);
    ll p;scanll(p);
    VI a(n);
    VI b(n);
    ll as=0;
    ll bs=0;
    rng(i,0,n){
        scanll(a[i]);
        as+=a[i];
        scanll(b[i]);
        bs+=b[i];
    }

    if (p>=as){
        cout<<-1<<endl;
        return 0;
    }
    double tl=0,tr=((double)bs)/(as-p)+1;
    while (tl+EPS<tr){
        double tm=(tl+tr)/2;
        double es=0;
        rng(i,0,n){
            es+=max((double)0,a[i]-b[i]/tm);
        }
        if (es<=p){
            tl=tm;
        }else{
            tr=tm;
        }
    }
    cout<<tl<<endl;
    return 0;
}
