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
#define stderrshow(l) {for (auto e:l)cerr<<e<<" ";cerr<<endl;}

float probtie(vector<float> &a){
    ll n=a.size();
    assert(n%2==0);
    vector<vector<float>> f(n+1,vector<float>(n+1,0.));
    f[0][0]=1.;
    rng(i,1,n+1){
        rng(j,0,i+1){
            f[i][j]=f[i-1][j]*(1-a[i-1])+((j==0)?0:f[i-1][j-1]*a[i-1]);
        }
    }
    return f[n][n/2];
}

int main()
{
    ll TN;scanll(TN);
    rng(TI,1,TN+1){
        ll n,k;cin>>n>>k;
        vector<float> a(n);
        rng(i,0,n) cin>>a[i];
        sort(a.begin(),a.end());
        //stderrshow(a);{};
        float ans = 0.;
        rng(i,0,k+1){
            vector<float> sel;
            rng(j,0,i){
                sel.push_back(a[j]);
            }
            rng(j,0,k-i){
                sel.push_back(a[n-1-j]);
            }
            //stderrshow(sel);
            //for (auto d:sel) cerr<<d<<' ';cerr<<endl;
            float crt = probtie(sel);//cerr<<crt<<endl;
            ans = max(ans, crt);
        }
        printf("Case #%lld: %f\n", TI, ans);
    }
    return 0;
}
