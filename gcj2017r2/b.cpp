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

const ll N=1000;
ll car[N][N];
bool incar[N][N];
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll c=scan();
        ll m=scan();
        VVI car(m,VI(n,-1));
        VVI incar(m,VI(c,0));
        VI ctr(n);
        ll ans0=0;
        vector<pair<ll,ll>> pb(m);
        rng(i,0,m){
            ll p=scan()-1;
            ll b=scan()-1;
            pb[i]=make_pair(p,b);
        }
        sort(pb.begin(),pb.end());
        rng(i,0,m){
            ll p=pb[i].first;
            ll b=pb[i].second;
            ctr[p]++;
            ll reck=-1,recj=-1;
            rng(j,0,ans0){
                if (incar[j][b]==1) continue;
                ll k=p;
                while (k>=0&&car[j][k]>=0){
                    --k;
                }
                if (k>reck){
                    reck=k;recj=j;
                }
            }
            if (reck<0){
                car[ans0][p]=b;
                incar[ans0][b]=1;
                ++ans0;
            }else{
                car[recj][reck]=b;
                incar[recj][b]=1;
            }
        }
        ll ans1=0;
        rng(i,0,n){
            ans1+=min(ctr[i],ans0);
        }
        printf("Case #%lld: %lld %lld\n",ti+1,ans0,m-ans1);
    }
    return 0;
}
