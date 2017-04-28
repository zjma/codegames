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

void xynext(ll n, ll &x, ll &y){
    ++y;
    if (y==n){
        ++x;
        y=x;
    }
}
int main()
{
    ll n=scan();
    ll k=scan();
    if (k>n*n){
        cout<<-1<<endl;
        return 0;
    }
    VVI a(n,VI(n,0));
    ll x=0;
    ll y=0;
    while(k>=1){
        if (k==1){
            if (x!=y){
                while(x!=y){
                    xynext(n,x,y);
                }
            }
            a[x][y]=1;
            xynext(n,x,y);
            --k;
        }else{
            if (x==y){
                a[x][y]=1;
                xynext(n,x,y);
                --k;
            }else{
                a[x][y]=a[y][x]=1;
                xynext(n,x,y);
                k-=2;
            }
        }
    }
    rng(i,0,n){
        rng(j,0,n){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
