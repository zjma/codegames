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
const double DINF=1e20;
const double EPS=1e-9;
const double PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}



void buildadjlist(ll n, const VI &froms, const VI &tos, VI &v2e0, VI &e2n){
    v2e0.resize(n);
    v2e0.assign(n, -1);
    ll en = froms.size();
    e2n.resize(en);
    rng(i,0,en){
        ll f = froms[i];
        ll t = tos[i];
        e2n[i] = v2e0[f];
        v2e0[f] = i;
    }
}

void floyd(ll n, const VVI &e, VVI &dist){
    dist.resize(n);
    rng(i,0,n){
        dist[i].resize(n);
        dist[i].assign(n,INF);
    }
    rng(i,0,n){
        dist[i][i]=0;
    }
    rng(i,0,n){
        rng(j,0,n){
            if (e[i][j]<INF){
                dist[i][j]=e[i][j];
            }
        }
    }
    rng(i,0,n){
        rng(j,0,n){
            rng(k,0,n){
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }

}


/**
 * SPFA algorithm.
 *
 * \param v2e0
 * \param e2t
 * \param e2c
 * \param e2n
 * \param n     #vertices
 * \param s     source vertex
 *
 * \return  d   distances
 */
void spfa(const VI &v2e0, const VI &e2t, const VD &e2c, const VI &e2n, ll n, ll s, VD &d){
    vector<bool> inq(n);
    d.assign(n, DINF);
    d[s]=0;
    queue<ll> q;
    q.push(s);
    inq[s]=true;
    while(!q.empty()){
        ll crt=q.front();
        q.pop();
        inq[crt]=false;
        ll ei=v2e0[crt];
        while (ei>=0){
            ll nxt = e2t[ei];
            if (d[crt]+e2c[ei]<d[nxt]){
                d[nxt]=d[crt]+e2c[ei];
                if (!inq[nxt]){
                    q.push(nxt);
                    inq[nxt]=true;
                }
            }
            ei=e2n[ei];
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
        floyd(n,d,dist);//rng(i,0,n){rng(j,0,n){cerr<<dist[i][j]<<" ";}cerr<<endl;}

        VI e2f;
        VI e2t;
        VD e2c;
        VI v2e0;
        VI e2n;
        rng(i,0,n){
            rng(j,0,n){
                if (d[i][j]>=INF) continue;
                rng(k,0,n){
                    if (dist[k][j]>e[k]) continue;
                    double cost=((double)d[i][j])/s[k];
                    //i,k -> j,k
                    e2f.push_back(i*n+k);
                    e2t.push_back(j*n+k);
                    e2c.push_back(cost);
                    //i,k -> j,j
                    e2f.push_back(i*n+k);
                    e2t.push_back(j*n+j);
                    e2c.push_back(cost);
                }
            }
        }
        ll vn=n*n;
        buildadjlist(vn,e2f,e2t,v2e0,e2n);
        VD ans(q,DINF);
        rng(qi,0,q){
            VD d;
            ll src=u[qi]*n+u[qi];
            spfa(v2e0,e2t,e2c,e2n,vn,src,d);
            //rng(i,0,vn){cerr<<d[i]<<" ";}cerr<<endl;
            rng(i,0,n){
                ll dst=v[qi]*n+i;
                ans[qi]=min(ans[qi],d[dst]);
            }
        }
        cout.precision(9);
        cout<<"Case #"<<(ti+1)<<":";
        rng(qi,0,q){
            cout<<" "<<fixed<<ans[qi];
        }cout<<endl;
    }
    return 0;
}
