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

int solveToEven(string &s){
    ll sn=s.size();
    ll result=0;
    rng(x,0,10){
        char cx=x+48;
        rng(y,x+1,10){
            char cy=y+48;
            ll ctr=0;
            char prev=0;
            rng(k,0,sn){
                if(s[k]==cx||s[k]==cy){
                    if (s[k]!=prev) ctr++;
                    prev=s[k];
                }
            }
            if (ctr%2==1){
                ctr--;
            }
            result=max(result,ctr);
        }
    }
    return result;
}

int solveToOdd(VVI &d2o){
    ll result=0;
    rng(i,0,10){
        result=max(result,ll(d2o[i].size()));
    }
    return result;
}

int solve(string &s){
    VVI mapDigitToOccurs(10,VI());
    ll n=s.size();
    rng(i,0,n){
        mapDigitToOccurs[s[i]-48].push_back(i);
    }
    ll ans2even = solveToEven(s);
    ll ans2odd = solveToOdd(mapDigitToOccurs);
    return s.size()-max(ans2even, ans2odd);
}

int main()
{
    ll TN=scan();
    rng(ti,0,TN){
        string s;
        cin>>s;
        cout<<solve(s)<<endl;
    }
    return 0;
}
