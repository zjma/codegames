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

char buf[51];
ll work(){
    scanstr(buf);
    ll n=strlen(buf);
    ll failed=0;
    ll segstart=-1;
    rng(i,0,n){
        if (i==0||buf[i]!=buf[i-1]){
            segstart=i;
        }
        if (i==n-1||buf[i+1]!=buf[i]){
            ll seglen=i-segstart+1;
            if (seglen>=2){
            }else{
                failed=1;
                break;
            }
        }
    }
    if (failed) printf("NO\n"); else printf("YES\n");
    return 0;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        work();
    }
    return 0;
}
