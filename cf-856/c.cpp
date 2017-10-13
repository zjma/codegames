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
#include <string>
using namespace std;

string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

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
const ll M = 998244353;
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}
//dump
void dumpVI(VI &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        cerr<<pfx<<"["<<i<<"]="<<a[i]<<endl;
    }
}
void dumpVVI(VVI &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        string newpfx(pfx);
        newpfx+="[";
        newpfx+=to_string(i);
        newpfx+="]";
        dumpVI(a[i],newpfx);
    }
}
void dumpVVVI(vector<VVI> &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        string newpfx(pfx);
        newpfx+="[";
        newpfx+=to_string(i);
        newpfx+="]";
        dumpVVI(a[i],newpfx);
    }
}

// const ll MAXN=2000;
// int f[MAXN+1][MAXN+1][11];
// int g[MAXN+1][MAXN+1][11];

ll dlen(ll x){
    ll ret=0;
    while(x){
        x/=10;
        ++ret;
    }
    return ret;
}
#define f11sub(a,b) ((a+11-b)%11)
#define f11add(a,b) ((a+b)%11)

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI b;
        VI a;
        rng(i,0,n){
            ll x=scan();
            if (dlen(x)%2==1){
                b.push_back(x%11);
            }
            else{
                a.push_back(x%11);
            }
        }
        ll n0=a.size();
        ll n1=b.size();
        ll jsw=n1/2;
        vector<VVI> f(n1+1,VVI(jsw+1,VI(11)));
        f[0][0][0]=1;
        rng(i,1,n1+1){
            rng(k,0,jsw+1){
                ll jswrm=jsw-k;
                ll oswrm=n1-i-1-jswrm;
                rng(r,0,11){
                    ll sub0=(k==i)?0:(mul(f[i-1][k][f11sub(r,b[i-1])],(n1-jsw-i+k+1)));
                    ll sub1=(k==0)?0:(mul(f[i-1][k-1][f11add(r,b[i-1])],(jsw-k+1)));
                    f[i][k][r]=add(sub0,sub1);
                }
            }
        }
        vector<VVI> g(n0+1,VVI(n0+1,VI(11)));
        rng(i,0,11){
            g[0][0][i]=f[n1][jsw][i];
        }
        rng(i,1,n0+1){
            rng(k,0,i+1){
                rng(r,0,11){
                    ll sub0=(k==i)?0:mul(g[i-1][k][f11sub(r,a[i-1])],(i-k));
                    ll sub1=(k==0)?0:mul(g[i-1][k-1][f11add(r,a[i-1])],k);
                    g[i][k][r]=add(sub0,sub1);
                }
            }
        }
        ll ans=0;
        if (n1==0){
            ans=g[n0][0][0];
        }else{
            rng(k,0,n0+1){
                ans=add(ans,g[n0][k][0]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
