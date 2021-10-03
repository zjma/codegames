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

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI a(n);
        ll allZeros=1;
        ll firstOneIdx=INF;
        rng(i,0,n){
            a[i]=scan();
            if (a[i]==1) {
                firstOneIdx=min(firstOneIdx,i);
                allZeros=0;
            }
        }
        if (allZeros){
            rng(i,0,n){
                cout<<i+1<<" ";
            }
            cout<<n+1<<endl;
        }else{
            rng(i,0,n){
                if (i==firstOneIdx){
                    cout<<n+1<<" ";
                }
                cout<<i+1;
                if (i==n-1) cout<<endl; else cout<<" ";
            }
        }
    }
    return 0;
}
