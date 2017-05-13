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

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


ll ME=0;
ll NODES=0;
void INIT() {ME=MyNodeId();NODES=NumberOfNodes();}

pair<ll,ll> get_my_inverval(ll n) {
    ll amt=max(1LL,(n+NODES-1)/NODES);
    ll L=ME*amt;
    ll R=min(n-1,(ME+1)*amt-1);
    if (L>R) return make_pair(-1,-2);
    return make_pair(L,R);
}


int main()
{
    INIT();
    ll n=GetLength();
    ll L,R;tie(L,R)=get_my_inverval(n);
    if (L>R) return 0;
    NODES=min(NODES,n);
    VI s1(R-L+1);
    VI s2(R-L+1);
    rng(i,L,R+1){
        s1[i-L]=GetScrollOne(i)-65;
        s2[i-L]=GetScrollTwo(i)-65;
    }

    VI ass(10,-1);
    VI competefor(10,-1);
    VI rival(10,-1);
    ll nextava=9;
    ll ans=0;

    if (ME>=1){
        Receive(ME-1);
        rng(i,0,10){
            ass[i]=GetLL(ME-1);
        }
        rng(i,0,10){
            competefor[i]=GetLL(ME-1);
        }
        rng(i,0,10){
            rival[i]=GetLL(ME-1);
        }
        nextava=GetLL(ME-1);
        ans=GetLL(ME-1);
    }

    //deal with my segment
    rng(i,L,R+1){
        ll c1=s1[i-L];
        ll c2=s2[i-L];
        ll fuck=-1;
        if (ass[c1]>=0&&ass[c2]>=0){

        }else if (ass[c1]>=0&&ass[c2]<0){
            if (competefor[c2]>=0){
                ass[c2]=competefor[c2];
                ass[rival[c2]]=ass[c2]-1;
            }else{
                ass[c2]=nextava--;
            }
        }else if (ass[c1]<0&&ass[c2]>=0){
            if (competefor[c1]>=0){
                ass[c1]=competefor[c1];
                ass[rival[c1]]=ass[c1]-1;
            }else{
                ass[c1]=nextava--;
            }
        }else{
            if (competefor[c1]<0&&competefor[c2]<0){
                if (c1==c2){
                    ass[c1]=nextava--;
                }else{
                    competefor[c1]=competefor[c2]=nextava;
                    rival[c1]=c2;rival[c2]=c1;
                    fuck=nextava*2-1;
                    nextava-=2;
                }
            }else if(competefor[c1]>=0&&competefor[c2]<0){
                ass[c1]=competefor[c1];
                ass[rival[c1]]=ass[c1]-1;
                ass[c2]=nextava--;
            }else if(competefor[c1]<0&&competefor[c2]>=0){
                ass[c2]=competefor[c2];
                ass[rival[c2]]=ass[c2]-1;
                ass[c1]=nextava--;
            }else{
                if (c1==c2){
                    ass[c1]=competefor[c1];
                    ass[rival[c1]]=ass[c1]-1;
                }else if (rival[c1]==c2){
                    fuck=competefor[c1]*2-1;
                }else{
                    ass[c1]=competefor[c1];
                    ass[rival[c1]]=ass[c1]-1;
                    ass[c2]=competefor[c2];
                    ass[rival[c2]]=ass[c2]-1;
                }
            }
        }
        ll crt=(ass[c1]>=0&&ass[c2]>=0)?(ass[c1]+ass[c2]):fuck;
        ans=add(mul(ans,10),crt);
    }

    if (ME==NODES-1){
        cout<<ans<<endl;
    }else{
        rng(i,0,10){
            PutLL(ME+1,ass[i]);
        }
        rng(i,0,10){
            PutLL(ME+1,competefor[i]);
        }
        rng(i,0,10){
            PutLL(ME+1,rival[i]);
        }
        PutLL(ME+1,nextava);
        PutLL(ME+1,ans);
        Send(ME+1);
    }

    return 0;
}
