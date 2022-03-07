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
const ll N=200000;

ll work(){
    ll n=scan();
    char buf[N+1];
    scanstr(buf);
    ll len=strlen(buf);
    ll curri=0,curci=0;
    ll firstTurnSid=INF;
    rng(i,0,len){
        if (firstTurnSid==INF&&i>=1&&buf[i]!=buf[i-1]) firstTurnSid=i;
        if(buf[i]=='D'){
            curri++;
        }else{
            curci++;
        }
    }
    ll end_diff_row=n-curri;
    ll end_diff_col=n-curci;
    ll ans=0;
    if(firstTurnSid==INF){
        ans=n;
    }else{
        rng(si,0,len){
            if(si<firstTurnSid){
                ans++;
            }else if(buf[si]=='R'){
                ans+=end_diff_row;
            }else{
                ans+=end_diff_col;
            }
        }
        ans+=end_diff_row*end_diff_col;
    }
    printf("%lld\n",ans);
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        work();
    }
    return 0;
}
