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


bool solve(ll p, ll x, ll y)
{
    PT f(x,y);
    PT c(50,50);
    PT t(50,100);
    PT u = f-c;
    PT v = t-c;
    double yy=cos_u2v(u,v);
    double xx=sin_u2v(u,v);
    double deg = atan2(yy,xx);if (deg<0) deg+=2*PI;
    bool incircle = dist2(f,c)<=2500;
    bool included = deg<2*PI*p/100;
    return incircle && included;
}

int main()
{
    ll TN;cin>>TN;
    rng(TI,0,TN){
        ll p,x,y;
        cin>>p>>x>>y;
        bool ans = solve(p,x,y);
        cout<<"Case #"<<TI+1<<": "<< ((ans)?"black":"white") << endl;
    }
    return 0;
}
