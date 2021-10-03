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
const ll N=2002;
char buf[N][N];
ll n;
ll rnx[N];
ll cnx[N];
ll rex[N];
ll cex[N];
ll reo[N];
ll ceo[N];
ll getAns(){
    rng(i,0,n) {
        rex[i]=cex[i]=reo[i]=ceo[i]=0;
    }

    rng(i,0,n){
        rng(j,0,n){
            if (buf[i][j]=='X'){
                rex[i]++;
                cex[j]++;
            }else if (buf[i][j]=='O'){
                reo[i]++;
                ceo[j]++;
            }
        }
    }
    ll ans=INF;
    rng(i,0,n){
        rnx[i]=(reo[i]>=1)?INF:(n-rex[i]);
        cnx[i]=(ceo[i]>=1)?INF:(n-cex[i]);
        ans=min(ans,rnx[i]);
        ans=min(ans,cnx[i]);
    }
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        n=scan();
        rng(ri,0,n){
            scanstr(buf[ri]);
        }
        ll ans=getAns();
        if (ans==INF){
            printf("Case #%lld: Impossible\n", ti+1);
            continue;
        }
        if (ans==1){
            ll ans2=0;
            rng(ri,0,n){
                rng(ci,0,n){
                    if ((rnx[ri]==1||cnx[ci]==1)&&buf[ri][ci]=='.') ans2++;
                }
            }
            printf("Case #%lld: %lld %lld\n", ti+1, ans, ans2);
            continue;
        }

        ll ans2=0;
        rng(i,0,n){
            if (rnx[i]==ans) ans2++;
            if (cnx[i]==ans) ans2++;
        }
        printf("Case #%lld: %lld %lld\n", ti+1, ans, ans2);
    }
    return 0;
}
