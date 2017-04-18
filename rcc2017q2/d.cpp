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

const ll N=500000;
const ll LN=21;
ll lft[N];
ll rgt[N];
ll prt[N];
ll fb[N][LN];
ll fr[N][LN];
void init(){
    rng(i,0,N){
        rng(j,0,LN){
            fb[i][j]=fr[i][j]=-1;
        }
        prt[i]=-1;
    }
}

inline ll add(ll a, ll b){
    return (a+b)%M;
}

inline ll mul(ll a, ll b){
    return (a*b)%M;
}

ll getminheight(ll i){
    if (i<0) return 0;
    return min(getminheight(lft[i]),getminheight(rgt[i]))+1;
}

ll getb(ll,ll);

ll getr(ll i, ll h){
    if (i<0){
        return 0;
    }else if (h<0){
        return 0;
    }else if (fr[i][h]<0){
        ll li=lft[i];
        ll ri=rgt[i];
        fr[i][h]=mul(getb(li,h),getb(ri,h));
    }
    return fr[i][h];

}

ll getb(ll i, ll h){
    if (i<0){
        if (h==0) return 1;
        return 0;
    }else if (h<0){
        return 0;
    }else if (fb[i][h]<0){
        ll li=lft[i];
        ll ri=rgt[i];
        ll sublb=getb(li,h-1);
        ll sublr=getr(li,h-1);
        ll subrb=getb(ri,h-1);
        ll subrr=getr(ri,h-1);
        fb[i][h]=add(add(mul(sublb,subrb),mul(sublb,subrr)),add(mul(sublr,subrb),mul(sublr,subrr)));
    }
    return fb[i][h];
}

int main()
{
    init();
    ll n;scanll(n);
    rng(i,0,n){
        ll x,y;scanll(x);scanll(y);--x;--y;
        lft[i]=x;
        rgt[i]=y;
        prt[x]=prt[y]=i;
    }
    ll root=-1;
    rng(i,0,n){
        if (prt[i]<0){root=i;break;}
    }
    ll minh=getminheight(root);
    ll ans=0;
    rng(h,1,minh+1){
        ll crt=getb(root,h);
        ans=add(ans,crt);
    }
    cout<<ans<<endl;
    return 0;
}
