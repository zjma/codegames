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

char buf[99];

tuple<ll,ll,ll> parse(char buf[]){
    ll i=0;
    ll x=0,y=0,z=0;
    ll zsign=0;
    ll st=0;
    while(st>=0){
        switch(st){
            case 0:
                if (buf[i]=='d')
                    st=1;
                else
                    x=x*10+buf[i]-48;
                break;
            case 1:
                if (buf[i]=='-'){
                    zsign=-1;
                    st=2;
                }else if (buf[i]=='+'){
                    zsign=1;
                    st=2;
                }
                else if (buf[i]==0)
                    st=-1;
                else
                    y=y*10+buf[i]-48;
                break;
            case 2:
                if (buf[i]==0)
                    st=-1;
                else
                    z=z*10+buf[i]-48;
                break;
        }
        ++i;
    }
    return make_tuple(x,y,z*zsign);
}

map<tuple<ll,ll,ll>,double> store;

double get(ll x, ll y, ll req){
    if (req<=0) return 1;
    if (x<=0) return 0;
    auto iii=make_tuple(y,x,req);
    if (store.find(iii)==store.end()){
        double acc=0;
        rng(i,0,y) acc+=get(x-1,y,req-i-1);
        store[iii]=acc/y;
    }
    return store[iii];
}

double solve(vector<ll>& x, vector<ll>& y, vector<ll>& t)
{
    ll n = x.size();
    double ans = 0;
    rng(i,0,n) ans=max(ans,get(x[i],y[i],t[i]));
    return ans;
}


int main()
{
    ll TN;scanll(TN);
    rng(TI,0,TN){
        ll h,s;scanll(h);scanll(s);
        vector<ll> x(s);
        vector<ll> y(s);
        vector<ll> t(s);
        rng(i,0,s){
            scanstr(buf);
            ll z;
            tie(x[i],y[i],z)=parse(buf);
            t[i] = h-z;
        }
        cout<<"Case #"<<TI+1<<": "<< solve(x,y,t) << endl;
    }
    return 0;
}
