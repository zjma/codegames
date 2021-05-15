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
#include <random>
using namespace std;

//type shortcuts
typedef long long ll;
typedef vector<ll> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;
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
const ll QN=10000;
const ll PN=100;
const ll Granularity=100000;
char buf[QN+1];
int main()
{
    srand(time(NULL));
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,0.999999);
    ll tn=scan();
    ll q=scan();
    rng(ti,0,tn){
        VI qe(QN);//question easiness
        VVVI pv2qs(PN,VVI(2));// (player,verdict) mapped to question list.
        VI auc(PN); // "area under roc"
        rng(i,0,PN){
            scanstr(buf);
            rng(j,0,QN){
                ll v=buf[j]-'0';
                pv2qs[i][v].push_back(j);
                qe[j]+=v*1;
            }
        }
        rng(i,0,PN){
            rng(j,0,Granularity){
                ll wa_count=pv2qs[i][0].size();
                ll ac_count=pv2qs[i][1].size();
                if (wa_count==0||ac_count==0){
                    auc[i]++;
                }else{
                    ll k0=distribution(generator)*wa_count;
                    ll k1=distribution(generator)*ac_count;
                    if (qe[pv2qs[i][0][k0]]<qe[pv2qs[i][1][k1]]){
                        auc[i]++;
                    }
                }
            }
        }
        ll ans=0;
        rng(i,0,PN){
            if (auc[i]<auc[ans]){
                ans=i;
            }
        }
        printf("Case #%lld: %lld\n",ti+1,ans+1);
    }
    return 0;
}
