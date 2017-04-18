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


int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll n,p;cin>>n>>p;
        VI r(n);
        rng(i,0,n){
            cin>>r[i];
        }
        vector<vector<pair<ll,ll>>> labels(n);
        ll L=0;
        rng(i,0,n){
            rng(j,0,p){
                ll g;cin>>g;
                ll label_min=(10*g+11*r[i]-1)/(11*r[i]);
                ll label_max=10*g/(9*r[i]);
                if (label_min>label_max) continue;
                L=max(L,label_max);
                labels[i].emplace_back(label_min,label_max);
            }
            sort(labels[i].begin(),labels[i].end());
        }
        VI f(n);
        ll ans=0;
        rng(x,1,L+1){
            while(true){
                bool formed=true;
                rng(i,0,n){
                    while(f[i]<labels[i].size()&&x>labels[i][f[i]].second) ++f[i];
                    formed=formed&&(f[i]<labels[i].size()&&labels[i][f[i]].first<=x&&x<=labels[i][f[i]].second);
                }
                if (!formed) break;
                rng(i,0,n){
                    ++f[i];
                }
                ++ans;
            }
        }
        cout<<"Case #"<<(ti+1)<<": "<<ans<<endl;
    }
    return 0;
}
