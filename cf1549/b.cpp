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
char buf0[N+1];
char buf1[N+1];

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        scanstr(buf0);
        scanstr(buf1);
        ll ans=0;
        rng(i,0,n){
            if (buf1[i]=='1'){
                if (buf0[i]=='0'){
                    buf0[i]=='2';
                    ans++;
                }else if (i-1>=0&&buf0[i-1]=='1') {
                    buf0[i-1]='2';
                    ans++;
                }else if(i+1<n&&buf0[i+1]=='1'){
                    buf0[i+1]='2';
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
