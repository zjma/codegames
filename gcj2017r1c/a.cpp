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
        ll k=scan();
        vector<pair<double,double>> raw(n);
        rng(i,0,n){
            ll r=scan();
            ll h=scan();
            double sside=PI*2*r*h;
            double stop=PI*r*r;
            raw[i]=make_pair(stop,sside);
        }
        sort(raw.begin(),raw.end());
        VD sside(n);
        VD stop(n);
        rng(i,0,n){
            tie(stop[i],sside[i])=raw[i];
        }

        double ans=0;
        rng(i,k-1,n){
            //find largestside k-1 sides
            VD tmp(i);
            rng(j,0,i){
                tmp[j]=-sside[j];
            }
            sort(tmp.begin(),tmp.end());
            double ssides=0;
            rng(j,0,k-1){
                ssides+=-tmp[j];
            }
            double crt=stop[i]+sside[i]+ssides;
            ans=max(ans,crt);
        }
        cout.precision(9);
        cout<<"Case #"<<(ti+1)<<": "<<fixed<<ans<<endl;
    }
    return 0;
}
