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

ll ans[20][20];

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll n,m;scanll(n);scanll(m);
        vector<tuple<ll,ll,ll>> f;
        rng(i,0,n){
            rng(j,0,m){
                f.emplace_back(i+j,i,j);
            }
        }
        sort(f.begin(),f.end());
        ll q=n*m;
        for (auto tp:f){
            ll d,x,y;tie(d,x,y)=tp;
            ans[x][y]=q--;
        }
        rng(i,0,n){
            rng(j,0,m){
                cout<<ans[i][j];
                if (j==m-1)cout<<endl; else cout<<' ';
            }
        }
    }
    return 0;
}
