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


int main()
{
    ll n,k;
    scanll(n);scanll(k);
    vector<ll> a(k);
    rng(i,0,k){
        scanll(a[i]);
    }
    vector<bool> live(n,true);
    int x=0;
    int cn=n;
    rng(i,0,k){
        auto d=a[i]%cn;
        rng(j,0,d){
            while(true){
                x=(x+1)%n;
                if (live[x]) break;
            }
        }
        cout<<(x+1);
        live[x]=false;
        cn--;
        if (i!=k-1){
            cout<<' ';
            while(true){
                x=(x+1)%n;
                if (live[x]) break;
            }
        }
    }
    cout<<endl;
    return 0;
}
