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
ll scan() {ll r;scanf("%I64d",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

int main()
{
    ll n=scan();
    ll w=scan();
    ll h=scan();
    VI x(n);
    VI y(n);
    VI finalx(n);
    VI finaly(n);
    map<ll,VI> na2idxs;
    rng(i,0,n){
        ll g=scan();
        ll p=scan();
        ll t=scan();
        if (g==1){
            x[i]=p;y[i]=-t;
            finalx[i]=x[i];finaly[i]=h;
        }else{
            x[i]=-t;y[i]=p;
            finalx[i]=w;finaly[i]=y[i];
        }
        na2idxs[x[i]+y[i]].push_back(i);
    }
    VI ansx(n);
    VI ansy(n);
    for (auto pr:na2idxs){
        ll tn=pr.second.size();
        vector<pair<ll,ll>> starts(tn);
        vector<pair<ll,ll>> ends(tn);
        rng(i,0,tn){
            ll idx=pr.second[i];
            starts[i]=make_pair(x[idx],idx);
            ends[i]=make_pair(finalx[idx]-finaly[idx],idx);
        }
        sort(starts.begin(),starts.end());
        sort(ends.begin(),ends.end());
        rng(i,0,tn){
            ll sii=starts[i].second;
            ll eii=ends[i].second;
            ansx[sii]=finalx[eii];
            ansy[sii]=finaly[eii];
        }
    }
    rng(i,0,n){
        printf("%I64d %I64d\n", ansx[i], ansy[i]);
    }
    return 0;
}
