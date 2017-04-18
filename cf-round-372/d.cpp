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

/**
 * Build adjacent lists from edges.
 *
 * \param n     vertex 0 .. n-1
 * \param froms edge.from
 * \param tos   edge.to
 *
 * \assume fromes.len==tos.len
 *
 * \return v2e0 first edge
 * \return e2n  edge.next
 */
void buildadjlist(ll n,
    const vector<ll> &froms, const vector<ll> &tos,
    vector<ll> &v2e0, vector<ll> &e2n)
{
    v2e0.resize(n);
    v2e0.assign(n, -1);
    ll en = froms.size();
    e2n.resize(en);
    for (int i = 0;i < en;i++) {
        ll f = froms[i];
        ll t = tos[i];
        e2n[i] = v2e0[f];
        v2e0[f] = i;
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
void spfa(const vector<ll> &v2e0, const vector<ll> &e2t, const vector<ll> &e2c, const vector<ll> &e2n, ll n, ll s, vector<ll> &d, vector<ll> &pre,vector<ll> &prg){
    vector<bool> inq(n);
    d.assign(n, LLONG_MAX);
    pre.assign(n, -1);
    prg.assign(n, -1);
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
                pre[nxt]=crt;
                prg[nxt]=ei;
                if (!inq[nxt]){
                    q.push(nxt);
                    inq[nxt]=true;
                }
            }
            ei=e2n[ei];
        }
    }
}

void output(const vector<ll> &e2f, const vector<ll> &e2t, const vector<ll> &e2c){
    ll n=e2f.size();
    printf("YES\n");
    rng(i,0,n/2){
        printf("%lld %lld %lld\n",e2f[i*2],e2t[i*2],e2c[i*2]);
    }
}

int main()
{
    ll n,m,L,s,t;
    scanll(n);
    scanll(m);
    scanll(L);
    scanll(s);
    scanll(t);
    vector<ll> e2f;
    vector<ll> e2c;
    vector<ll> e2t;
    vector<ll> e2n;
    vector<bool> e2x;
    vector<ll> v2e0;
    rng(i,0,m){
        ll u,v,w;
        scanll(u);
        scanll(v);
        scanll(w);
        bool xxx=(w==0);
        if (w==0) w=L+1;
        e2f.push_back(u);
        e2t.push_back(v);
        e2c.push_back(w);
        e2x.push_back(xxx);
        e2f.push_back(v);
        e2t.push_back(u);
        e2c.push_back(w);
        e2x.push_back(xxx);
    }
    buildadjlist(n,e2f,e2t,v2e0,e2n);

    vector<ll> d;
    vector<ll> pre;
    vector<ll> prg;
    spfa(v2e0,e2t,e2c,e2n,n,s,d,pre,prg);
    if (d[t]<L){
        cout<<"NO"<<endl;
        return 0;
    }
    if (d[t]==L){
        output(e2f,e2t,e2c);
        return 0;
    }

    rng(i,0,2*m){
        if (e2x[i]) e2c[i]=1;
    }

    spfa(v2e0,e2t,e2c,e2n,n,s,d,pre,prg);
    if (d[t]>L) {
        cout<<"NO"<<endl;
        return 0;
    }
    if (d[t]==L){
        output(e2f,e2t,e2c);
        return 0;
    }
    set<ll> path;
    while(true){
        ll i=t;
        path.clear();
        while (i!=s){
            path.insert(prg[i]);
            i = pre[i];
        }
        ll ei;
        for (auto pi:path){
            if (e2x[pi]){ei=pi;break;}
        }
        e2c[ei]+=L-d[t];
        e2c[ei^1]+=L-d[t];
        spfa(v2e0,e2t,e2c,e2n,n,s,d,pre,prg);
        if (d[t]==L){
            output(e2f,e2t,e2c);
            return 0;
        }
    }

    return 0;
}
