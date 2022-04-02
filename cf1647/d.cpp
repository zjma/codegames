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
void dumpVI(const string &header, VI &arr){
    ll n=arr.size();
    rng(i,0,n){
        cerr<<header<<"["<<i<<"]="<<arr[i]<<endl;
    }
}
void work(){
    ll x=scan();
    ll d=scan();
    ll sqrd=d*d;
    VI bfs;
    rng(i,1,x){
        if (i*i>x) break;
        if (x%i==0){
            ll j=x/i;
            if (i%d==0&&i%sqrd>=1){
                bfs.push_back(i);
            }
            if (j!=i&&j%d==0&&j%sqrd>=1){
                bfs.push_back(j);
            }
        }
    }
    sort(bfs.begin(),bfs.end());
    // dumpVI("bfs",bfs);
    ll bfn=bfs.size();
    map<ll,ll> res;
    rng(i,0,bfn){
        ll curbf=bfs[i];
        // cerr<<"curbf="<<curbf<<endl;
        res[curbf]+=1;
        ll base=res.begin()->first;
        while(1){
            // cerr<<"base="<<base<<endl;
            ll newp=base*curbf;
            if (newp>x) break;
            res[newp]+=res[base];
            auto it=res.upper_bound(base);
            if (it==res.end()) break;
            base=it->first;
        }
    }
    if (res[x]>=2) cout<<"YES"<<endl; else cout<<"NO"<<endl;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        work();
    }
    return 0;
}
