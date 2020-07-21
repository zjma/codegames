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
char buf[1000001];
int main()
{
    ll TN=scan();
    rng(TI,0,TN){
        scanstr(buf);
        ll cur=0;
        ll ans=0;
        ll count=0;
        while (buf[count]){
            if (buf[count]=='-'){
                cur-=1;
            }else{
                cur+=1;
            }

            if (cur<0){
                ans+=count+1;
                cur=0;
            }
            count++;
        }
        ans+=count;
        cout<<ans<<endl;
    }
    return 0;
}
