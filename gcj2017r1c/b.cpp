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
        ll cn=scan();
        ll jn=scan();
        VI cbusy(1441);
        VI jbusy(1441);
        rng(i,0,cn){
            ll x=scan();
            ll y=scan();
            rng(j,x+1,y+1){
                cbusy[j]=1;
            }
        }
        rng(i,0,jn){
            ll x=scan();
            ll y=scan();
            rng(j,x+1,y+1){
                jbusy[j]=1;
            }
        }
        VVI f00(721,VI(721));
        VVI f01(721,VI(721));
        VVI f10(721,VI(721));
        VVI f11(721,VI(721));
        f00[0][1]=INF;
        f00[1][0]=(cbusy[1])?INF:0;
        f11[1][0]=INF;
        f11[0][1]=(jbusy[1])?INF:0;
        f01[0][1]=INF;
        f01[1][0]=INF;
        f10[0][1]=INF;
        f10[1][0]=INF;
        rng(tt,2,1441){
            rng(ct,0,(min(tt,(ll)720)+1)){
                ll jt=tt-ct;
                if (jt>720) continue;
                f00[ct][jt]=(ct==0)?INF:(cbusy[tt])?INF:min(f00[ct-1][jt],f01[ct-1][jt]+1);
                f10[ct][jt]=(ct==0)?INF:(cbusy[tt])?INF:min(f10[ct-1][jt],f11[ct-1][jt]+1);
                f11[ct][jt]=(jt==0)?INF:(jbusy[tt])?INF:min(f11[ct][jt-1],f10[ct][jt-1]+1);
                f01[ct][jt]=(jt==0)?INF:(jbusy[tt])?INF:min(f01[ct][jt-1],f00[ct][jt-1]+1);
            }
        }
        ll ans=INF;
        ans=min(ans,f00[720][720]);
        ans=min(ans,f11[720][720]);
        ans=min(ans,f01[720][720]+1);
        ans=min(ans,f10[720][720]+1);
        cout<<"Case #"<<(ti+1)<<": "<<ans<<endl;
    }
    return 0;
}
