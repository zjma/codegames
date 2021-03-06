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
ll scan() {ll r;scanf("%I64d",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan()%2;
    }
    VI f1(n+1);
    VI f0(n+1);
    f0[0]=1;
    rng(i,1,n+1){
        ll found1=0;
        ll found0=0;
        rng(k,0,i){
            found1=found1||f0[k]&&(i-k)%2==1&&a[k];
            found0=found0||f1[k]&&(i-k)%2==1&&a[k];
        }
        f1[i]=a[i-1]&&found1;
        f0[i]=a[i-1]&&found0;
    }
    if (f1[n])
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    return 0;
}
