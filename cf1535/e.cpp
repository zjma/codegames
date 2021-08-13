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
const ll N=300000;
ll a[N];
ll c[N];
ll depth[N];
ll ancestorsOf[N][19];
int main()
{
    ll q=scan();
    a[0]=scan();
    c[0]=scan();
    depth[0]=0;
    rng(j,0,19) ancestorsOf[0][j]=-1;
    rng(qi,1,q+1){
        ll cmd=scan();
        if (cmd==1){
            ll parent=scan();
            a[qi]=scan();
            c[qi]=scan();
            depth[qi]=depth[parent]+1;
            ancestorsOf[qi][0]=parent;
            rng(j,1,19) {
                ancestorsOf[qi][j]=((1<<j)<=depth[qi])?ancestorsOf[ancestorsOf[qi][j-1]][j-1]:-1;
            }
        }else{
            ll v=scan();
            ll w=scan();
            ll v0=v;
            rng(j,0,19){
                ll jj=18-j;
                ll anc=ancestorsOf[v0][jj];
                if (anc>=0&&a[anc]>=1) v0=anc;
            }

            ll amount=0;
            ll cost=0;
            ll gap=depth[v]-depth[v0];
            rng(z,0,gap+1){
                int v00=v;
                rng(j,0,19){
                    ll jj=18-j;
                    ll anc=ancestorsOf[v00][jj];
                    if (anc>=0&&a[anc]>=1) v00=anc;
                }
                ll consumption=min(a[v00],w);
                amount+=consumption;
                w-=consumption;
                a[v00]-=consumption;
                cost+=consumption*c[v00];
                if (w==0) break;
            }
            cout<<amount<<' '<<cost<<endl;
        }
    }
    return 0;
}
