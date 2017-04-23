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
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}


void floyd(ll n, const VVI &e, VVI &dist){
    dist.resize(n);
    rng(i,0,n){
        dist[i].resize(n);
    }
    rng(i,0,n){
        rng(j,0,n){
            dist[i][j]=(i==j)?0:e[i][j];
        }
    }
    rng(k,0,n){
        rng(i,0,n){
            rng(j,0,n){
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

void floydInpDouble(ll n, const VVD &e, VVD &dist){
    dist.resize(n);
    rng(i,0,n){
        dist[i].resize(n);
    }
    rng(i,0,n){
        rng(j,0,n){
            dist[i][j]=(i==j)?0:e[i][j];
        }
    }
    rng(k,0,n){
        rng(i,0,n){
            rng(j,0,n){
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll n;scanll(n);
        ll q;scanll(q);
        VI e(n);
        VI s(n);
        rng(i,0,n){
            scanll(e[i]);
            scanll(s[i]);
        }
        VVI d(n,VI(n));
        rng(i,0,n){
            rng(j,0,n){
                scanll(d[i][j]);
                if (d[i][j]==-1) d[i][j]=INF;
            }
        }

        VI u(q);
        VI v(q);
        rng(i,0,q){
            scanll(u[i]);--u[i];
            scanll(v[i]);--v[i];
        }

        VVI dist;
        floyd(n,d,dist);

        VVD f(n,VD(n));
        rng(i,0,n){
            rng(j,0,n){
                f[i][j]=(dist[i][j]>e[i])?INFD:(dist[i][j]/(double)s[i]);
            }
        }
        VVD g;
        floydInpDouble(n,f,g);

        VD ans(q);
        rng(qi,0,q){
            ans[qi]=g[u[qi]][v[qi]];
        }
        cout.precision(9);
        cout<<"Case #"<<(ti+1)<<":";
        rng(qi,0,q){
            cout<<" "<<fixed<<ans[qi];
        }cout<<endl;
    }
    return 0;
}
