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

//dump
void dumpVI(const VI &a){
    ll n=a.size();
    rng(i,0,n){
        cerr<<"v("<<i<<")="<<a[i]<<endl;
    }
}
void dumpVVI(const VVI &a){
    ll n=a.size();
    rng(i,0,n){
        ll m=a[i].size();
        rng(j,0,m){
            cerr<<"v("<<i<<","<<j<<")="<<a[i][j]<<endl;
        }
    }
}

//extra operations
ll log2floor(ll x){
    assert(x>=1);
    return 63LL-__builtin_clzll(x);
}
ll log2ceil(ll x){
    assert(x>=1);
    return (x==1)?0LL:(64LL-__builtin_clzll(x-1));
}


//Geometry (real number coordinates)
struct PT {
    double x, y;
    PT() {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y); }
    PT operator * (double c)     const { return PT(x*c, y*c); }
    PT operator / (double c)     const { return PT(x / c, y / c); }
};
double dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }
double cos_u2v(const PT& u, const PT& v) { return dot(u, v) / sqrt(dot(u,u)*dot(v,v)); }
double sin_u2v(const PT& u, const PT& v) { return cross(u, v) / sqrt(dot(u, u)*dot(v, v)); }
ostream &operator<<(ostream &os, const PT &p) {
    os << "(" << p.x << "," << p.y << ")";
}
double vector2angle(const PT &v) {return atan2(v.y, v.x);}


//union find
struct UnionFind {
    VI C;
    VI h;
    UnionFind(ll n) : C(n), h(n) {
        for (int i=0;i<n;i++) C[i]=i;
    }
    ll find(ll x) {
        return (C[x] == x) ? x : C[x]=find(C[x]);
    }
    void merge(ll x, ll y) {
        ll xp = find(x), yp = find(y);
	if (xp==yp) return;
        if (h[xp]==h[yp]) {h[xp]++;C[yp]=xp;}
	if (h[xp]<h[yp]) {C[xp]=yp;}
	if (h[xp]>h[yp]) {C[yp]=xp;}
    }
};


//euclid, modulo
ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
ll power(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}
ll gcd(ll a, ll b) { for (;b>0;swap(a, b))a %= b;return a; }
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a / b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}
// ll mod_inverse(ll a, ll n) {
//     ll x, y;
//     ll d = extended_euclid(a, n, x, y);
//     if (d > 1) return -1;
//     return mod(x, n);
// }


//Reduce 2D integer vector
pair<ll,ll> reduce_vector2d(ll dx, ll dy){
    ll g=gcd(abs(dx),abs(dy));
    dx/=g;dy/=g;
    if (dy<0) {dy=-dy;dx=-dx;}
    if (dy==0) dx=1;
    return make_pair(dx,dy);
}


//Integer discretization. Return number of values.
ll discretize(VI &x){
    set<ll> avset(x.begin(),x.end());
    map<ll,ll> vmap;ll dn=0;
    for (auto it=avset.begin();it!=avset.end();it++) vmap[*it]=dn++;
    for (ll i=0,n=x.size();i<n;i++) x[i]=vmap[x[i]];
    return dn;
}


/**
 * Two-phase simplex.
 *
 * \param   A -- m x n matrix
 * \param   b -- m-dim vector
 * \param   c -- n-dim vector
 * \return  x -- an n-dim vector for receiving solution.
 * \return  value (infinity if unbounded above, nan if infeasible)
 *
 * \assume  The problem is:
 *    maximize     c^T x
 *    subject to   Ax <= b
 *                 x >= 0
 *
 * \usage
 *      LPSolver lp=LPSolver(A,b,c);
 *      double value=lp.solve(x);
 */
struct LPSolver {
    int m, n;
    VI B, N;
    VVD D;
    LPSolver(const VVD &A, const VD &b, const VD &c) :
        m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
        for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m + 1][n] = 1;
    }
    void Pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++) if (i != r)
            for (int j = 0; j < n + 2; j++) if (j != s)
                D[i][j] -= D[r][j] * D[i][s] / D[r][s];
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }
    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                    (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
            }
            if (r == -1) return false;
            Pivot(r, s);
        }
    }
    double solve(VD &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -EPS) {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<double>::infinity();
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                int s = -1;
                for (int j = 0; j <= n; j++)
                    if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
                Pivot(i, s);
            }
        }
        if (!Simplex(2)) return numeric_limits<double>::infinity();
        x = VD(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};


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
    const VI &froms, const VI &tos,
    VI &v2e0, VI &e2n)
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
void spfa(const VI &v2e0, const VI &e2t, const VI &e2c, const VI &e2n, ll n, ll s, VI &d){
    vector<bool> inq(n);
    d.assign(n, LLONG_MAX);
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


//dijkstra
void dijkstra(const VI& v2e0,
        const VI& e2t, const VI& e2c, const VI& e2n,
        ll src, VI& dist, VI& prec)
{
    ll n=v2e0.size();
    dist.resize(n);dist.assign(n,INT_MAX);
    prec.resize(n);prec.assign(n,-1);
    vector<bool> arr(n);
    ll sel=src;
    dist[sel]=0;
    while (sel>=0){
        arr[sel]=true;
        for (ll i=v2e0[sel];i>=0;i=e2n[i]){
            ll to=e2t[i];
            ll cost=e2c[i];
            if (!arr[to]&&dist[to]>dist[sel]+cost){
                dist[to]=dist[sel]+cost;
                prec[to]=sel;
            }
        }
        sel=-1;
        for (ll i=0;i<n;i++)
            if (!arr[i]&&(sel==-1||dist[i]<dist[sel])) sel=i;
    }
}


/**
 * Floyd shortest paths.
 *
 * \assume  Fully connected.
 * \assume  No negative loop.
 * \assume  No integer overflow.
 *
 * \param n #vertices
 * \param e Adj table.
 *
 * \return dist distances.
 */
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


//Tarjan's strong connected components
void tarjan_dfs(ll v, ll &timer, ll &cn,
        VI &vtime, VI &rtime,
        const VI &v2e0,
        const VI &e2t, const VI &e2n,
        VI &v2c, stack<ll> &stk)
{
    stk.push(v);
    rtime[v]=vtime[v]=timer++;
    for (ll i=v2e0[v];i>=0;i=e2n[i]){
        ll w=e2t[i];
        if (vtime[w]==-1){
            tarjan_dfs(w,timer,cn,vtime,rtime,v2e0,e2t,e2n,v2c,stk);
            rtime[v]=min(rtime[v],rtime[w]);
        }else if (v2c[w]==-1)
            rtime[v]=min(rtime[v],vtime[w]);
    }
    if (vtime[v]==rtime[v]){
        while (true){
            ll pv=stk.top();
            v2c[pv]=cn;
            stk.pop();
            if (pv==v) break;
        }
        cn++;
    }
}
/**
 * Tarjan's strong connected components
 *
 * \param n     #vertices (0..n-1)
 * \param v2e0
 * \param e2t
 * \param e2n
 *
 * \return  #components, vid-cid mapping stored in v2c
 */
ll tarjan_strong(ll n,
        const VI &v2e0,
        const VI &e2t,
        const VI &e2n,
        VI &v2c)
{
    v2c.assign(n,-1);
    VI vtime(n,-1);
    VI rtime(n,-1);
    stack<ll> stk;
    ll timer=0,cn=0;
    for (ll i=0;i<n;i++){
        if (vtime[i]>=0) continue;
        tarjan_dfs(i,timer,cn,vtime,rtime,v2e0,e2t,e2n,v2c,stk);
    }
    return cn;
}


/**
 * Ford Fulkerson max flow algorithm.
 *
 * O(E*maxflow) time.
 * Graph is represented by adjacent lists.
 *
 * \assume source!=sink.
 *
 * \param v2e0  vertex.first_edge
 * \param e2f   edge.from
 * \param e2t   edge.to
 * \param e2c   edge.cost
 * \param e2n   edge.next
 * \param s     source
 * \param t     sink
 *
 * \return  maxflow
 *
 * \usage
 *      FordFulk ff(v2e0,e2f,e2t,e2c,e2n,s,t);
 *      ll sol=ff.eval();
 */
struct FordFulk {
    const VI &v2e0;
    const VI &e2f;
    const VI &e2t;
    const VI &e2c;
    const VI &e2n;
    ll s,t;
    FordFulk(const VI &_v2e0,
        const VI &_e2f,
        const VI &_e2t,
        const VI &_e2c,
        const VI &_e2n,
        ll _s, ll _t)
        :  s(_s),t(_t),v2e0(_v2e0),e2f(_e2f),e2t(_e2t),e2c(_e2c),e2n(_e2n)
    {}
    ll _find_aug_path(const VI &v2e0,
        const VI &e2f,
        const VI &e2t,
        const VI &e2c,
        const VI &e2n,
        ll s, ll t, VI &epath)
    {
        VI q2v;
        VI q2p;
        VI q2e;
        VI q2f;
        vector<bool> inq(v2e0.size(), false);
        //BFS
        q2v.push_back(s);
        q2p.push_back(-1);
        q2e.push_back(-1);
        q2f.push_back(INT_MAX);
        inq[s] = true;
        for (ll i = 0;i<q2v.size();i++) {
            ll crt = q2v[i];
            ll f = q2f[i];
            for (ll j = v2e0[crt];j != -1;j = e2n[j]) {
                ll to = e2t[j];
                ll rem = e2c[j];
                if (inq[to]) continue;
                if (rem <= 0) continue;
                q2v.push_back(to);
                q2p.push_back(i);
                q2e.push_back(j);
                q2f.push_back(min(f, rem));
                inq[to] = true;
            }
        }
        //Get Path
        for (ll i = 0;i<q2v.size();i++) {
            if (q2v[i] != t) continue;
            stack<ll> stk;
            for (ll j = i;j>0;j = q2p[j]) {
                stk.push(q2e[j]);
            }
            while (!stk.empty()) {
                epath.push_back(stk.top());
                stk.pop();
            }
            return q2f[i];
        }
        return 0;
    }

    ll eval(){
        //Build residual graph
        ll en = e2f.size();
        map<pair<ll, ll>, ll> rsd;
        for (ll i = 0;i<en;i++) {
            ll f = e2f[i];
            ll t = e2t[i];
            rsd[make_pair(f, t)] += e2c[i];
            rsd[make_pair(t, f)] += 0;
        }
        map<pair<ll, ll>, ll> nei;
        ll ren = 0;
        for (auto er : rsd) {
            nei[er.first] = ren++;
        }
        ll rvn = v2e0.size();
        VI rv2e0(rvn, -1);
        VI re2f(ren);//from
        VI re2t(ren);//to
        VI re2c(ren);//cost
        VI re2n(ren);//next edge
        VI re2p(ren);//peer edge
        ll rei = 0;
        for (auto er : rsd) {
            ll f = er.first.first;
            ll t = er.first.second;
            ll c = er.second;
            re2f[rei] = f;
            re2t[rei] = t;
            re2c[rei] = c;
            re2p[rei] = nei[make_pair(t, f)];
            re2n[rei] = rv2e0[f];
            rv2e0[f] = rei;
            ++rei;
        }

        //FF main
        ll sol = 0;
        VI epath;
        while (true) {
            epath.clear();
            ll res = _find_aug_path(rv2e0, re2f, re2t, re2c, re2n, s, t, epath);
            if (res == 0) break;
            for (auto ei : epath) {
                re2c[ei] -= res;
                re2c[re2p[ei]] += res;
            }
            sol += res;
        }
        return sol;
    }
};


// 1D Binary indexed tree.
// Point update(by relative diff) & [0..k] interval query.
template <typename T>
struct BIT1D {
    ll n;
    vector<T> v;
    T (*fnx)(ll,T);
    T (*fab)(T,T);
    ll rg(ll k){return ((k^(k+1))+1)/2;}
    BIT1D (ll _n, T v0, T (*_fnx)(ll,T), T (*_fab)(T,T))
            :n(_n),v(_n),fnx(_fnx),fab(_fab)
    {for (ll i=0;i<n;i++) v[i]=fnx(rg(i),v0);}
    void update(ll i, T v1){
        for (;i<n;i+=rg(i)) v[i]=fab(v[i],v1);
    }
    T query(ll i){
        ll j=i-rg(i);
        return (j<0)?v[i]:(query(j)+v[i]);
    }
};


/**
 * RMQ Solver.
 * O(nlogn) preprocess, O(1) answer.
 */
struct RMQOracle {
    ll N;
    VVI f0;
    VVI f1;
    RMQOracle(const VI &a){
        N=a.size();
        ll K=log2floor(N);
        f0.resize(N);
        f1.resize(N);
        rng(i,0,N){f0[i].resize(K+1);f1[i].resize(K+1);}
        rng(i,0,N) f0[i][0]=f1[i][0]=a[i];
        rng(k,1,K+1){
            ll half=1<<(k-1);
            rng(i,0,N){
                if (i+half*2<=N) f0[i][k]=min(f0[i][k-1],f0[i+half][k-1]);
                if (i-half*2+1>=0) f1[i][k]=min(f1[i][k-1],f1[i-half][k-1]);
            }
        }
    }
    ll get(ll ql, ll qr){
        assert(0<=ql);assert(ql<=qr);assert(qr<N);
        ll k=log2floor(qr-ql+1);
        return min(f0[ql][k],f1[qr][k]);
    }
};


/**
 * 1D generic segment tree. Lazy propgation & on-demand allocation.
 *
 * Allow 1 type of segmentable interval query(SUM/MAX),
 *       interval update by relative diff(each+1/each-lift-to-5), and
 *       interval update by value-setting(each-set-to-9)
 *
 * \param _l    left-most position
 * \param _r    right-most position
 * \param _v    initial element value
 * \param _fnx  query function I    (compute X+X+X+...+X)
 * \param _fab  query function II   (compute A+B)
 *
 * \usage
 *      double max_ab(double a, double b){return max(a,b);}
 *      double max_nx(int n,double x){return x;}
 *      LazySegTree1D<R> t(0,99,0.0,max_nx,max_ab);//query MAX(seg) on [0,99]
 *      tree.updres(1,6,2.2); //lift each to 2.2 on [1,6]
 *      tree.setval(0,5,1.1); //set each to 1.1 on [0,5]
 *      auto v=tree.get(2,7); // get maximum on [2,7]
 */
template <typename T>
struct LazySegTree1D {
    vector<T> v;
    VI opr;//0: set value; 1: update result; -1: idle
    vector<T> opd;
    VI nxt;
    ll LEFT;
    ll RGHT;
    T (*fnx)(ll,T);
    T (*fab)(T,T);
    LazySegTree1D(ll _l, ll _r, T _v, T (*_fnx)(ll,T), T (*_fab)(T,T))
        :v(1),opr(1),opd(1),nxt(1),LEFT(_l),RGHT(_r),fnx(_fnx),fab(_fab)
    {
        v[0]=fnx(RGHT-LEFT+1,_v);
        opr[0]=0;
        opd[0]=_v;
        nxt[0]=-1;
    }
    void _split(ll i, ll l0, ll r0){
        assert(nxt[i]==-1);
        assert(opr[i]==0);
        assert(l0<r0);
        ll n=v.size();
        nxt[i]=n;
        ll m0=(l0+r0)/2;
        v.push_back(fnx(m0-l0+1,opd[i]));
        v.push_back(fnx(r0-m0,opd[i]));
        opr.push_back(0);
        opr.push_back(0);
        opd.push_back(opd[i]);
        opd.push_back(opd[i]);
        nxt.push_back(-1);
        nxt.push_back(-1);
    }
    void _pushdown(ll i, ll l0, ll r0){
        if (opr[i]==-1) return;
        ll m0=(l0+r0)/2;
        if (nxt[i]==-1)
            _split(i,l0,r0);
        else if (opr[i]>=0){
            _set(nxt[i],l0,m0,l0,m0,opr[i],opd[i]);
            _set(nxt[i]+1,m0+1,r0,m0+1,r0,opr[i],opd[i]);
        }
        opr[i]=-1;
    }
    void _set(ll i, ll l0, ll r0, ll l1, ll r1, ll o1, T v1){
        assert(l1>=l0&&r1<=r0);
        if (l0==l1&&r0==r1){
            if (o1==0){
                v[i]=fnx(r0-l0+1,v1);
                opr[i]=0;opd[i]=v1;
            }else if (o1==1){
                v[i]=fab(v[i],fnx(r0-l0+1,v1));
                if (opr[i]==-1){
                    opr[i]=1;opd[i]=v1;
                }else if (opr[i]==0){
                    opr[i]=0;opd[i]=fab(opd[i],v1);
                }else if (opr[i]==1){
                    opr[i]=1;opd[i]=fab(opd[i],v1);
                }
            }
            return;
        }
        ll m0=(l0+r0)/2;
        _pushdown(i,l0,r0);
        if (l1<=m0) _set(nxt[i],l0,m0,l1,min(r1,m0),o1,v1);
        if (r1>m0) _set(nxt[i]+1,m0+1,r0,max(l1,m0+1),r1,o1,v1);
        v[i]=fab(v[nxt[i]],v[nxt[i]+1]);
    }
    T _get(ll i, ll l0, ll r0, ll l1, ll r1){
        assert(l0<=l1&&r1<=r0);
        if (l0==l1&&r1==r0) return v[i];
        _pushdown(i,l0,r0);
        ll m0=(l0+r0)/2;
        if (r1<=m0) return _get(nxt[i],l0,m0,l1,r1);
        if (m0+1<=l1) return _get(nxt[i]+1,m0+1,r0,l1,r1);
        T lv=_get(nxt[i],l0,m0,l1,m0);
        T rv=_get(nxt[i]+1,m0+1,r0,m0+1,r1);
        return fab(lv,rv);
    }
    void updres(ll l1, ll r1, T v1){_set(0,LEFT,RGHT,l1,r1,1,v1);}
    void setval(ll l1, ll r1, T v1){_set(0,LEFT,RGHT,l1,r1,0,v1);}
    T get(ll l1, ll r1){return _get(0,LEFT,RGHT,l1,r1);}
};


// Suffix array (doubling) O(n*lgn*lgn)
void suffix_array(const string &s, VI &sa, VI &rank){
    ll n=s.size();
    ll ri=0;
    VVI tmprank(2,VI(n));
    vector<pair<pair<ll,ll>,ll>> kni(n);

    //Compute rank1[] rank2[], rank4[], rank8[]...
    for (ll g=1;g/2<=n-1;g*=2,ri=1-ri){
        for (ll i=0;i<n;i++){
            ll key1=(g==1)?s[i]:tmprank[ri][i];
            ll key2=(g==1)?0:(i+g/2<n)?(tmprank[ri][i+g/2]):-1;
            kni[i]=make_pair(make_pair(key1,key2),i);
        }
        sort(kni.begin(),kni.end());
        for (ll i=0,last_rank=-1;i<n;i++){
            ll this_rank=(i>0&&kni[i].first==kni[i-1].first)?last_rank:i;
            last_rank=tmprank[1-ri][kni[i].second]=this_rank;
        }
    }

    rank.resize(n);rank.assign(tmprank[ri].begin(),tmprank[ri].end());
    sa.resize(n);for (ll i=0;i<n;i++) sa[rank[i]]=i;
}


/**
 * Suffix tree, Ukkonen's algorithm.
 *
 * \usage
 *      string s="qwerty$";
 *      SuffixTree tree(7);//If len of str is know, tell it to prealloc.
 *      for (auto c:s) tree.insert(c);
 */
struct SuffixTree{
    string str;
    vector<unordered_map<ll,ll>> sta;
    vector<unordered_map<ll,ll>> end;
    vector<unordered_map<ll,ll>> nxt;
    VI suflink;
    ll capacity;
    ll node_count;
    ll act_node;
    ll act_br;
    ll act_len;
    ll todo_count;
    bool _nodehasbr(ll node, ll br){
        auto m=nxt[node];
        return m.find(br)!=m.end();
    }
    ll _newnode(){
        if (node_count<capacity){
            ll newi=node_count++;
            suflink[newi]=-1;
            sta[newi].clear();
            end[newi].clear();
            nxt[newi].clear();
            return newi;
        }
        sta.emplace_back();
        end.emplace_back();
        nxt.emplace_back();
        suflink.push_back(-1);
        ++node_count;
        ++capacity;
        return node_count-1;
    }
    ll _edgerealend(ll node, ll br){
        ll tmp=end[node][br];
        return (tmp==-1)?(str.size()-1):tmp;
    }
    ll _edgelen(ll node, ll br){
        return (br==-1)?0:(!_nodehasbr(node,br))?0:(_edgerealend(node,br)-sta[node][br]+1);
    }
    void clear(){
        node_count=0;
        act_node=0;
        act_br=-1;
        act_len=0;
        todo_count=0;
        _newnode();
    }
    SuffixTree(ll est_strlen){
        capacity=0;
        if (est_strlen>0){
            ll est_nodecnt=est_strlen*2;
            capacity=est_nodecnt;
            sta=vector<unordered_map<ll,ll>>(est_nodecnt);
            end=vector<unordered_map<ll,ll>>(est_nodecnt);
            nxt=vector<unordered_map<ll,ll>>(est_nodecnt);
            suflink=VI(est_nodecnt,-1);
        }
        clear();
    }
    bool _tryextend(ll chr){
        if (act_len==0){
            if (!_nodehasbr(act_node,chr)) return false;
            act_br=chr;
            ++act_len;
            return true;
        }
        //here we do have pending suffixes
        if (act_len==_edgelen(act_node,act_br)){//need to see the nxt node
            ll nxtnode=nxt[act_node][act_br];
            if (!_nodehasbr(nxtnode,chr)) return false;
            act_node=nxtnode;
            act_br=chr;
            act_len=1;
            return true;
        }
        //now act_len<edgelen, we check next char in this edge
        ll start=sta[act_node][act_br];
        if (chr!=str[start+act_len]) return false;
        ++act_len;
        return true;
    }
    void _branch(ll node, ll chr){
        ll newnode=_newnode();
        sta[node][chr]=str.size()-1;
        end[node][chr]=-1;
        nxt[node][chr]=newnode;
    }
    ll _actsplit(ll chr){
        ll new0=_newnode();//for old branch
        ll new1=_newnode();// for new branch

        ll start=sta[act_node][act_br];

        sta[new0][str[start+act_len]]=start+act_len;
        end[new0][str[start+act_len]]=end[act_node][act_br];
        nxt[new0][str[start+act_len]]=nxt[act_node][act_br];
        sta[new0][chr]=str.size()-1;
        end[new0][chr]=-1;
        nxt[new0][chr]=new1;
        sta[act_node][act_br]=start;
        end[act_node][act_br]=start+act_len-1;
        nxt[act_node][act_br]=new0;

        return new0;
    }
    ll _splitorbranch(ll chr){
        if (act_br>=0&&act_len<_edgelen(act_node,act_br)) return _actsplit(chr);
        ll target_node=(act_len==0)?0:nxt[act_node][act_br];
        _branch(target_node,chr);
        return target_node;
    }
    string _edgestr(ll node, ll br){//get edge string
        ll start=sta[node][br];
        ll end=_edgerealend(node,br);
        return str.substr(start,end-start+1);
    }
    void _actsupdate(ll node, ll br, ll len){act_node=node,act_br=br,act_len=len;}
    void _actfastfwd(ll start, ll slen){//s(start,len): before the new char is inserted
        if (act_br==-1) return;
        while (true){
            ll elen=_edgelen(act_node,act_br);
            if (slen<=elen) return;
            ll new_act_node=nxt[act_node][act_br];
            ll new_act_br=str[start+elen];
            ll new_act_len=act_len-elen;
            _actsupdate(new_act_node,new_act_br,new_act_len);
            start+=elen;
            slen-=elen;
        }
    }
    bool _actsgotonextsuf(){
        if (act_len==0) return false;
        ll estart=sta[act_node][act_br];
        if (act_node==0){
            act_br=(act_len==1)?(-1):str[estart+1];
            --act_len;
            _actfastfwd(estart+1,act_len);
        }else{
            act_node=(suflink[act_node]>=0)?suflink[act_node]:0;
            _actfastfwd(estart,act_len);
        }
    }
    void insert(ll chr){
        str.push_back(chr);
        ++todo_count;
        ll prev_created=-1;
        for (ll waitlink=-1;todo_count>0;--todo_count){
            bool suffix_exists=_tryextend(chr);
            if (suffix_exists){
                waitlink=act_node;
            }else{
                waitlink=_splitorbranch(chr);
            }
            if (prev_created>=0) suflink[prev_created]=waitlink;
            prev_created=waitlink;
            if (suffix_exists) break;
            _actsgotonextsuf();
        }
    }
};


int main()
{
    srand(time(NULL));
    cout<<"IT WORKS"<<endl;
    return 0;
}
