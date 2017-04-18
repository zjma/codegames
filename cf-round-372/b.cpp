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
#include <cstring>
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

const ll L=60000;
char b[L];
int main()
{
    scanstr(b);
    ll n = strlen(b);
    if (n<26){
        cout<<-1<<endl;
        return 0;
    }
    vector<ll> count(26);
    ll dups = 0;
    rng(i,0,26){
        if (b[i]=='?') continue;
        if ((++count[b[i]-65])==2) ++dups;
    }
    ll i=25;
    while (true){
        if (dups==0){
            break;
        }
        if (i==n-1) {
            cout<<-1<<endl;
            return 0;
        }
        if ((--count[b[i-25]-65])==1) --dups;
        ++i;
        if ((++count[b[i]-65])==2) ++dups;
    }
    ll start=i-25;
    ll x=-1;
    rng(i,0,n){
        if (b[i]!='?') continue;
        if (i<start || i>=start+26)
            b[i]='A';
        else{
            while (count[++x]>0);
            b[i]=x+65;
        }
    }
    printf("%s\n",b);
    return 0;
}
