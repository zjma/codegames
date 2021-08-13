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

const ll N=200000;
const ll K=18;
ll fl[N][K+1];
ll fr[N][K+1];
ll A[N];
ll B[N];
ll gcd(ll x, ll y){
    if (y==0) return x;
    return gcd(y,x%y);
}
ll log2floor(ll x){
    ll ans=0;
    while (x>=2){
        x/=2;
        ans++;
    }
    return ans;
}
#define p2(k) (1<<(k))
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        rng(i,0,n){
            A[i]=scan();
        }
        ll bn=n-1;
        ll klimit=log2floor(bn);
        rng(i,0,bn){
            B[i]=abs(A[i+1]-A[i]);
        }
        rng(k,0,klimit+1){
            if (k==0){
                rng(i,0,bn){
                    fl[i][0]=fr[i][0]=B[i];
                }
            }else{
                rng(i,0,bn){
                    if (i+p2(k)-1<=bn-1)
                        fl[i][k]=gcd(fl[i][k-1],fl[i+p2(k-1)][k-1]);
                    if (i-p2(k)+1>=0)
                        fr[i][k]=gcd(fr[i][k-1],fr[i-p2(k-1)][k-1]);
                }
            }
        }
        ll ans=1;
        ll li=0;
        ll wd=1;
        while(li<bn&&li+wd-1<=bn-1){
            ll curgcd=gcd(fl[li][log2floor(wd)],fr[li+wd-1][log2floor(wd)]);
            if (curgcd>=2){
                ans=max(ans,wd+1);
                wd++;
            }else{
                li++;
                wd--;
                if (wd<1) wd=1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
