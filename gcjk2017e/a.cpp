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

const ll N=100;
ll f[N+1][N][N][2];
ll ff[N+1];
ll g[N][N][N+1];

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        string s;cin>>s;
        ll n=s.size();
        rng(i,0,n){
            rng(j,i+1,n){
                rng(k,1,n+1-j){
                    g[i][j][k]=(k==1)?(s[i]==s[j]):(j-i>=k&&g[i][j][k-1]&&s[i+k-1]==s[j+k-1]);
                    // printf("g[%lld][%lld][%lld]=%lld\n",i,j,k,g[i][j][k]);
                }
            }
        }

        rng(i,0,n+1){
            ff[i]=INF;
        }

        rng(i,0,n+1){
            rng(j,0,n){
                rng(k,0,n){
                    rng(z,0,2){
                        f[i][j][k][z]=INF;
                    }
                }
            }
        }
        rng(i,0,n+1){
            f[i][1][0][0]=(i==0)?0:(f[i-1][1][0][1]+1);
            ff[i]=min(ff[i],f[i][1][0][0]);
            rng(j,0,i){
                rng(k,j,i){
                    ll wlen = k-j+1;
                    ll try_paste = (g[j][i-wlen][wlen])?(f[i-wlen][j][k][1]+1):INF;
                    f[i][j][k][0] = min(
                        f[i-1][j][k][1]+1,//type one
                        try_paste//paste
                    );
                    ff[i]=min(ff[i],f[i][j][k][0]);
                }
            }
            f[i][1][0][1] = min(ff[i]+1, f[i][1][0][0]);
            rng(j,0,i){
                rng(k,j,i){
                    f[i][j][k][1] = min(ff[i]+1,f[i][j][k][0]);
                }
            }
        }
        ll ans=ff[n];
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
