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
const ll N=101;
char buf[N];
char getChar(char x, ll gap){
    if (gap%2){
        if (x=='R') return 'B';
        return 'R';
    }
    return x;
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        scanstr(buf);
        ll firstPaintedIdx=-1;
        rng(i,0,n){
            if (buf[i]!='?'){
                firstPaintedIdx=i;
                break;
            }
        }
        if (firstPaintedIdx>=1){
            rng(i,0,firstPaintedIdx){
                buf[i]=getChar(buf[firstPaintedIdx],firstPaintedIdx-i);
            }
        }
        rng(i,firstPaintedIdx+1,n){
            if (buf[i]=='?'){
                buf[i]=getChar(buf[i-1],1);
            }
        }
        printf("%s\n",buf);
    }
    return 0;
}
