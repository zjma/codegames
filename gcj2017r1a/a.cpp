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


void solve(vector<string> &a){
    ll rn=a.size();
    ll cn=a[0].size();
    rng(i,0,rn){
        rng(j,0,cn){
            if (a[i][j]!='?'){
                ll k=j-1;
                while (k>=0&&a[i][k]=='?'){
                    a[i][k]=a[i][j];
                    --k;
                }
                k=j+1;
                while (k<cn&&a[i][k]=='?'){
                    a[i][k]=a[i][j];
                    ++k;
                }
            }
        }
    }
    rng(i,0,rn){
        if (a[i][0]!='?'){
            ll j=i-1;
            while (j>=0&&a[j][0]=='?'){
                rng(k,0,cn){
                    a[j][k]=a[i][k];
                }
                --j;
            }
            j=i+1;
            while (j<rn&&a[j][0]=='?'){
                rng(k,0,cn){
                    a[j][k]=a[i][k];
                }
                ++j;
            }
        }
    }
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll rn,cn;cin>>rn>>cn;
        vector<string> a(rn);
        rng(i,0,rn){
            cin>>a[i];
        }
        solve(a);
        cout<<"Case #"<<(ti+1)<<":"<<endl;
        rng(i,0,rn){
            cout<<a[i]<<endl;
        }
    }
    return 0;
}
