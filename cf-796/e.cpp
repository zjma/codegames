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

const ll G=1000;
const ll V=50;

ll f[2][G+1][V][V];

#define max4(a,b,c,d) (max(max((a),(b)),max((c),(d))))
int main()
{
    ll n;scanll(n);
    ll g;scanll(g);
    ll v;scanll(v);
    g=min(g,2*(n+v-1)/v);
    ll ln;scanll(ln);
    VI l(n);
    VI r(n);
    rng(i,0,ln){
        ll tmp;scanll(tmp);l[tmp-1]=1;
    }
    ll rn;scanll(rn);
    rng(i,0,rn){
        ll tmp;scanll(tmp);r[tmp-1]=1;
    }

    if (v==1){
        ll cand=0;
        rng(i,0,n){
            if (l[i]==1||r[i]==1) ++cand;
        }
        cout<<min(cand,g)<<endl;
        return 0;
    }

    rng(j,0,g+1){
        rng(lm,0,v){
            rng(rm,0,v){
                f[0][j][lm][rm]=(j>=1||lm>=1||rm>=1)?INT_MIN:0;
            }
        }
    }
    rng(i,1,n+1){
        ll ii=i&1;
        rng(j,0,g+1){
            rng(lm,0,v){
                rng(rm,0,v){
                    if (j<=1&&lm>=1&&rm>=1)
                        f[ii][j][lm][rm]=INT_MIN;
                    else if (j==0&&(lm>=1||rm>=1))
                        f[ii][j][lm][rm]=INT_MIN;
                    else if (lm==v-1&&rm==v-1)
                        f[ii][j][v-1][v-1]=f[1-ii][j-2][0][0]+(l[i-1]|r[i-1]);
                    else if (lm==v-1&&rm==0)
                        f[ii][j][v-1][0]=max(f[1-ii][j-1][0][1]+(l[i-1]|r[i-1]),f[1-ii][j-1][0][0]+l[i-1]);
                    else if (lm==v-1)
                        f[ii][j][v-1][rm]=f[1-ii][j-1][0][rm+1]+(l[i-1]|r[i-1]);
                    else if (lm==0&&rm==v-1)
                        f[ii][j][0][v-1]=max(f[1-ii][j-1][1][0]+(l[i-1]|r[i-1]),f[1-ii][j-1][0][0]+r[i-1]);
                    else if (lm==0&&rm==0)
                        f[ii][j][0][0]=max4(f[1-ii][j][1][1]+(l[i-1]|r[i-1]),f[1-ii][j][1][0]+l[i-1],f[1-ii][j][0][1]+r[i-1],f[1-ii][j][0][0]);
                    else if (lm==0)
                        f[ii][j][0][rm]=max(f[1-ii][j][1][rm+1]+(l[i-1]|r[i-1]),f[1-ii][j][0][rm+1]+r[i-1]);
                    else if (rm==v-1)
                        f[ii][j][lm][v-1]=f[1-ii][j-1][lm+1][0]+(l[i-1]|r[i-1]);
                    else if (rm==0)
                        f[ii][j][lm][0]=max(f[1-ii][j][lm+1][1]+(l[i-1]|r[i-1]),f[1-ii][j][lm+1][0]+l[i-1]);
                    else
                        f[ii][j][lm][rm]=f[1-ii][j][lm+1][rm+1]+(l[i-1]|r[i-1]);
                }
            }
        }
    }

    ll ans=0;
    ll ii=n&1;
    rng(j,0,g+1){
        rng(lm,0,v){
            rng(rm,0,v){
                ans=max(ans,f[ii][j][lm][rm]);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
