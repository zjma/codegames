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
char buf[100001];
ll getd(ll x){
    ll r=1;
    while(x%2==0){
        x/=2;
        r*=2;
    }
    return r;
}
int main()
{
    ll n,q;
    scanll(n);scanll(q);
    ll D=(n+1)/2;
    ll x;
    rng(i,0,q){
        scanll(x);
        ll d=getd(x);
        scanstr(buf);
        ll j=0;
        while(buf[j]){
            if (buf[j]=='L'&&d>1){
                d/=2;
                x-=d;
            }
            else if (buf[j]=='R'&&d>1){
                d/=2;
                x+=d;
            }
            else if (buf[j]=='U'&&d!=D){
                d*=2;
                auto bro=x^d;
                x=(x+bro)/2;
            }
            j++;
        }
        cout<<x<<endl;
    }
    return 0;
}
