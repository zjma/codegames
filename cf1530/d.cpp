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

ll popany(set<ll> &s) {
    ll res = *s.begin();
    s.erase(res);
    return res;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll k=scan();
        VI a(k);
        vector<set<ll>> prevs(k);
        rng(i,0,k){
            a[i]=scan()-1;
            prevs[a[i]].insert(i);
        }
        set<ll> ds;
        rng(i,0,k){
            if (prevs[i].empty()) ds.insert(i);
        }
        ll ans=0;
        rng(i,0,k){
            ll j=i;
            while (ds.find(j)==ds.end()&&prevs[a[j]].size()>=2) {
                ans++;
                ll newNs=popany(ds);
                ll oldNs=a[j];
                a[j]=newNs;
                prevs[newNs].insert(j);
                prevs[oldNs].erase(j);
                j=newNs;
            }
        }
        cout<<(k-ans)<<endl;
        rng(i,0,k){
            cout<<(a[i]+1);
            if (i==k-1) cout<<endl; else cout<<' ';
        }
    }
    return 0;
}
