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
void scanll(ll &x) {int r;scanf("%d",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


int main()
{
    ll l1,r1,l2,r2,k;
    scanll(l1);
    scanll(r1);
    scanll(l2);
    scanll(r2);
    scanll(k);
    ll l=max(l1,l2);
    ll r=min(r1,r2);
    if (l>r){
        cout<<0<<endl;
    }else if (l<=k && k<=r){
        cout<<(r-l)<<endl;
    }else{
        cout<<(r-l+1)<<endl;
    }
    return 0;
}
