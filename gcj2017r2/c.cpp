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

bool allow(ll r, ll cv, ll st){
    VI c(r);
    VI s(r);
    rng(i,0,r){
        s[i]=cv%12;cv/=12;
        c[i]=st%3;st/=3;
    }
    rng(i,0,r){
        if (c[i]==0&&s[i]>=9||c[i]==1&&s[i]!=9||c[i]==2&&s[i]<=9) return false;
    }
    VI b;
    rng(i,0,r){
        if (s[i]>=9) b.push_back(i);
    }
    ll bn=b.size();
    rng(i,0,bn-1){
        if (s[b[i]]>=10&&s[b[i+1]]>=10&&(s[b[i]]==11||s[b[i+1]]==11)) return false;
    }

}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll ans=0;
        rng(i,0,c){
            rng(k1,0,S){
                if (!allow(r,cv[i],k1)) continue;
                rng(k0,0,S){
                    if (go[k0][k1]) f[i][k1]|=f[i-1][k0];
                }
            }
        }
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
