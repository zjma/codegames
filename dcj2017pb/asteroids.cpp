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
#include "asteroids.h"
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

ll divceil(ll a, ll b){
    return (a+b-1)/b;
}

ll max3(ll a, ll b, ll c){
    return max(a,max(b,c));
}

ll add(ll a, ll b){return (a==-INF||b==-INF)?-INF:(a+b);}

ll parseChar(char c){
    return (c=='#')?-INF:(c-48);
}

ll ME=0;
ll NODES=0;

int main()
{
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll rn=GetHeight()+1;
    ll cn=GetWidth()+2;
    ll W=max3(3,divceil(rn,50),divceil(cn,NODES));
    W=min(W,cn);
    assert(W>=3);
    ll dh=(W-1)/2;assert(dh>=1);
    ll VNODES=cn/W;assert(VNODES>=1);
    if (ME>=VNODES) return 0;
    ll L=ME*W;
    ll R=(ME==VNODES-1)?(cn-1):((ME+1)*W-1);
    // cerr<<"myL="<<L<<", myR="<<R<<endl;
    assert(R-L+1>=W);assert(R-L+1<2*W);
    ll FL=max(0LL,L-dh-1);
    ll FR=min(cn-1,R+dh+1);

    VVI a(rn,VI(FR-FL+1));
    rng(i,0,rn-1){
        rng(j,FL,FR){
            a[i][j-FL]=(j==0||j==cn-1)?-INF:parseChar(GetPosition(i,j-1));
        }
    }

    VVI f(rn,VI(FR-FL+1));
    rng(j,FL,FR+1){
        //setf(0,j,geta(0,j));
        f[0][j-FL]=a[0][j-FL];
    }
    ll h=1;
    while(h<rn){
        // Compute for the main triangle.
        ll nexth=min(h+dh,rn);
        ll crtdh=nexth-h;
        rng(i,h,nexth){
            ll di=i-h+1;
            ll LL=L+di,RR=R-di;assert(LL<=RR);
            rng(j,LL,RR+1){
                f[i][j-FL]=add(a[i][j-FL],max3(add(f[i-1][j-1-FL],a[i-1][j-FL]),f[i-1][j-FL],add(f[i-1][j+1-FL],a[i-1][j-FL])));
            }
        }

        // Tell left node if necessary.
        if (ME>0){
            rng(i,h-1,nexth-1){
                ll di=i-h+1;
                PutLL(ME-1,f[i][L+di-FL]);
                PutLL(ME-1,f[i][L+di+1-FL]);
            }
            Send(ME-1);
        }

        // Tell right node if necessary.
        if (ME<VNODES-1){
            rng(i,h-1,nexth-1){
                ll di=i-h+1;
                PutLL(ME+1,f[i][R-di-FL]);
                PutLL(ME+1,f[i][R-di-1-FL]);
            }
            Send(ME+1);
        }

        // Hear from left node if necessary.
        if (ME>0){
            Receive(ME-1);
            rng(i,h-1,nexth-1){
                ll di=i-h+1;
                f[i][L-di-1-FL]=GetLL(ME-1);
                f[i][L-di-2-FL]=GetLL(ME-1);
            }
        }

        // Hear from right node if necessary.
        if (ME<VNODES-1){
            Receive(ME+1);
            rng(i,h-1,nexth-1){
                ll di=i-h+1;
                f[i][R+di+1-FL]=GetLL(ME+1);
                f[i][R+di+2-FL]=GetLL(ME+1);
            }
        }

        rng(i,h,nexth){
            ll di=i-h+1;
            // Compute for left sub-triangle.
            ll LL=max(0LL,L-di);
            ll RR=(L+di-1);
            rng(j,LL,RR+1){
                if (j==0){
                    f[i][j-FL]=-INF;
                }else{
                    f[i][j-FL]=add(a[i][j-FL],max3(add(f[i-1][j-1-FL],a[i-1][j-FL]),f[i-1][j-FL],add(f[i-1][j+1-FL],a[i-1][j-FL])));
                }
            }
            // Compute for right sub-triangle.
            LL=R+1-di;
            RR=min(cn-1,R+di);
            rng(j,LL,RR+1){
                if (j==cn-1){
                    f[i][j-FL]=-INF;
                }else{
                    f[i][j-FL]=add(a[i][j-FL],max3(add(f[i-1][j-1-FL],a[i-1][j-FL]),f[i-1][j-FL],add(f[i-1][j+1-FL],a[i-1][j-FL])));
                }
            }
        }
        h=nexth;
    }

    ll ans=-INF;
    rng(j,L,R+1) ans=max(ans,f[rn-1][j-FL]);
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll ans=-INF;
        rng(i,0,VNODES){
            Receive(i);
            ans=max(ans,GetLL(i));
        }
        ans=max(ans,-1LL);
        cout<<ans<<endl;
    }
    return 0;
}
