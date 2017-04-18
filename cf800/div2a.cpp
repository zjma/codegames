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
const DOUBLE EPS=1e-6;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

char buf[200];
ll count(ll n, char buf[]){
    ll acc=0;
    rng(i,0,n-1){
        if (buf[i]=='V'&&buf[i+1]=='K') ++acc;
    }
    return acc;
}
int main()
{
    scanstr(buf);
    ll n=strlen(buf);
    ll ans=count(n,buf);
    rng(i,0,n){
        if (buf[i]=='V'){
            buf[i]='K';
            ans=max(ans,count(n,buf));
            buf[i]='V';
        }else{
            buf[i]='V';
            ans=max(ans,count(n,buf));
            buf[i]='K';
        }
    }
    cout<<ans<<endl;
    return 0;
}
