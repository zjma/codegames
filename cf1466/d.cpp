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



int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI w(n);
        ll total=0;
        rng(i,0,n){
            w[i]=scan();
            total+=w[i];
        }
        VI e2f(n-1);
        VI e2t(n-1);
        VI deg(n,0);

        rng(i,0,n-1){
            e2f[i]=scan()-1;
            e2t[i]=scan()-1;
            deg[e2f[i]]++;
            deg[e2t[i]]++;
        }

        VI cand;
        rng(i,0,n){
            rng(j,0,deg[i]-1){
                cand.push_back(-w[i]);
            }
        }
        sort(cand.begin(),cand.end());
        VI psum(cand.size()+1,0);
        rng(i,0,cand.size()){
            psum[i+1]=psum[i]-cand[i];
        }
        rng(i,0,n-1){
            ll ans=total+psum[i];
            cout<<ans;
            if (i==n-2) cout<<endl; else cout<<" ";
        }
    }
    return 0;
}
