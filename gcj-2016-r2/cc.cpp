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
        ll R,C;scanll(R);scanll(C);
        vector<ll> love(2*(R+C));
        rng(i,0,R*C){
            ll x,y;scanll(x);scanll(y);--x;--y;
            love[x]=y;
            love[y]=x;
        }

        vector<ll> waiting;
        rng(i,0,2*(R+C)){waiting.push_back(i);}

        rng(z,0,(R+C)){
            ll tn = waiting.size();
            rng(i,0,tn){
                ll nxti = (i+1)%tn;
                if (love[waiting[i]]==waiting[nxti]){
                    //place some hedges
                    ll k=0;
                    rng(j,0,tn-2){
                        while (k==i||k==nxti) ++k;
                        waiting[j] = waiting[k];
                        ++k;
                    }
                    break;
                }
            }
        }

        rng(i,0,R){
            rng(j,0,C){
                cout<<ans[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}
