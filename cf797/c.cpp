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

const ll N=100000;
char buf[N+1];
char ans[N+1];
ll an=0;
char f[N+1];
int main()
{
    scanstr(buf);
    ll n=strlen(buf);
    f[n]='z'+1;
    rng(i,0,n){
        ll ii=n-1-i;
        f[ii]=min(buf[ii],f[ii+1]);
    }
    stack<char> stk;
    rng(i,0,n){
        stk.push(buf[i]);
        while(!stk.empty()){
            char cc=stk.top();
            if (cc>f[i+1]) break;
            ans[an++]=cc;
            stk.pop();
        }
    }
    ans[an]=0;
    printf("%s\n",ans);
    return 0;
}
