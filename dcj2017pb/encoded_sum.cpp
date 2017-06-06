#include <message.h>
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
#include "encoded_sum.h"
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

ll mod(ll x) { return ((x%M) + M) % M; }
ll add(ll a, ll b){return mod(mod(a)+mod(b));}
ll sub(ll a, ll b){return mod(mod(a)-mod(b));}
ll mul(ll a, ll b){return mod(mod(a)*mod(b));}
ll power(ll b, ll e){
    ll ans=1;
    while (e>0){
        if (e%2) ans=mul(ans,b);
        b=mul(b,b);
        e/=2;
    }
    return mod(ans);
}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

ll ME=0;
ll NODES=0;

pair<ll,ll> get_interval(ll NODES, ll ME, ll n) {
    ll n2=n%NODES;
    ll n1=NODES-n2;
    ll l1=n/NODES;
    ll l2=l1+1;
    ll L,R;
    if (ME<n2){
        L=l2*ME;
        R=L+l2-1;
    }else{
        L=l2*n2+l1*(ME-n2);
        R=L+l1-1;
    }
    return make_pair(L,R);
}

ll updatetmp[10];
void scoreupdate(ll base[], ll delta[]){
    rng(i,0,10){
        base[i]=base[i]*10+delta[i];
        updatetmp[i]=base[i]*10+i;
    }
    sort(updatetmp,updatetmp+10);
    ll prelettr=-1;
    ll prescore=-1;
    rng(i,0,10){
        ll score=updatetmp[i]/10;
        ll lettr=updatetmp[i]%10;
        base[lettr]=(score==prescore)?base[prelettr]:i;
        prelettr=lettr;
        prescore=score;
    }
}

uint8_t cc[10000000];
// char c1[10000000];
// char c2[10000000];
ll localscore[10];
ll localtmpscore[10];
ll totalscore[10];
ll subscore[10];
ll auxscore[10];
ll finalscore[10];
int main()
{
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll N=GetLength();
    ll L,R;tie(L,R)=get_interval(NODES,ME,N);
    if (L>R) return 0;
    ll VNODES=min(NODES,N);

    rng(i,L,R+1){
        uint8_t v1=GetScrollOne(i)-65;
        uint8_t v2=GetScrollTwo(i)-65;
        cc[i-L]=v1*10+v2;
    }

    rng(i,L,R+1){
        rng(j,0,10){
            // localtmpscore[j]=((j==c1[i-L])?1:0)+((j==c2[i-L])?1:0);
            ll v1=cc[i-L]/10;
            ll v2=cc[i-L]-10*v1;;
            localtmpscore[j]=((j==v1)?1:0)+((j==v2)?1:0);
        }
        scoreupdate(localscore,localtmpscore);
    }

    rng(i,0,10){
        PutLL(0,localscore[i]);
    }
    Send(0);

    if (ME==0){
        rng(ni,0,VNODES){
            Receive(ni);
            rng(i,0,10){
                subscore[i]=GetLL(ni);
            }
            scoreupdate(totalscore,subscore);
        }

        rng(i,0,10) auxscore[i]=i;
        scoreupdate(totalscore,auxscore);


        rng(ni,0,VNODES){
            rng(i,0,10){
                PutLL(ni,totalscore[i]);
            }
            Send(ni);
        }
    }

    Receive(0);
    rng(i,0,10){
        finalscore[i]=GetLL(0);
    }

    ll ans=0;
    rng(i,L,R+1){
        ll v1=cc[i-L]/10;
        ll v2=cc[i-L]-10*v1;;
    ans=add(mul(ans,10),finalscore[v1]+finalscore[v2]);
    }
    ans=mul(ans,power(10,N-1-R));
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll ans=0;
        rng(ni,0,VNODES){
            Receive(ni);
            ans=add(ans,GetLL(ni));
        }
        cout<<ans<<endl;
    }
    return 0;
}
