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

const ll MAXRN = 100;
const ll MAXCN = 100;
char buf[MAXRN][MAXCN+1];

void work(){
    ll rn=scan();
    ll cn=scan();
    rng(ri,0,rn){
        scanstr(buf[ri]);
    }
    if (buf[0][0]=='1'){
        printf("-1\n");
        return;
    }
    ll ans=0;
    for(ll ri=rn-1;ri>=0;ri--){
        for (ll ci=cn-1;ci>=0;ci--){
            if (buf[ri][ci]=='1'){
                ans++;
            }
        }
    }
    printf("%lld\n", ans);
    for(ll ri=rn-1;ri>=0;ri--){
        for (ll ci=cn-1;ci>=0;ci--){
            if (buf[ri][ci]=='1'){
                if(ci==0){
                    printf("%lld %lld %lld %lld\n", ri, ci+1, ri+1,ci+1);
                }else{
                    printf("%lld %lld %lld %lld\n", ri+1, ci, ri+1,ci+1);
                }
            }
        }
    }
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        work();
    }
    return 0;
}
