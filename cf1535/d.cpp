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

void dump(VI &A) {
    ll n=A.size();
    cout<<'[';
    rng(i,0,n){
        cout<<A[i]<<",";
    }
    cout<<']'<<endl;
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}
char buf[262145];
char buf2[2];

#define pow2(i) (1<<(i))
#define fin(i) (n-(i))
#define fout(i) (n-(i))
#define leftOf(i) (fout(fin(i)*2+1))
#define rghtOf(i) (fout(fin(i)*2))
#define prntOf(i) (fout(fin(i)/2))
int main()
{
    ll k=scan();
    ll n=(1<<k)-1;
    VI F(n,1);
    scanstr(buf);
    rng(i,0,n){
        ll leftVal=(i<pow2(k-1))?1:F[leftOf(i)];
        ll rghtVal=(i<pow2(k-1))?1:F[rghtOf(i)];
        F[i]=(buf[i]=='0')?leftVal:(buf[i]=='1')?rghtVal:(leftVal+rghtVal);
    }
    ll q=scan();
    rng(qi,0,q){
        ll p=scan()-1;
        scanstr(buf2);
        buf[p]=buf2[0];
        while (p>=0&&p<n){
            ll leftVal=(p<pow2(k-1))?1:F[leftOf(p)];
            ll rghtVal=(p<pow2(k-1))?1:F[rghtOf(p)];
            F[p]=(buf[p]=='0')?leftVal:(buf[p]=='1')?rghtVal:(leftVal+rghtVal);
            p=prntOf(p);
        }
        cout<<F[n-1]<<endl;
    }
    return 0;
}
