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
void scanll(ll &x) {int r;scanf("%d",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

ll n;

ll ask(ll t, ll l, ll b, ll r){
    printf("? %lld %lld %lld %lld\n", t, l, b, r);
    fflush(stdout);
    ll ret;scanll(ret);
    return ret;
}

ll ask2(ll l, ll r, ll t, ll b){
    return ask(t,l,b,r);
}

bool ptLRLR(ll l0, ll l1, ll r0, ll r1){
    return r0<l1;
}

bool ptLLRR(ll l0, ll l1, ll r0, ll r1){
    return l1<=r0;
}

ll bruteL0(){
    ll L=1,R=n+1;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,M,n,n)==2){
            L=M;
        }else{
            R=M;
        }
    }
    return L;
}

ll bruteL1(){
    ll L=1,R=n+1;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,M,n,n)==0){
            R=M;
        }else{
            L=M;
        }
    }
    return R-1;
}

ll bruteR0(){
    ll L=0,R=n;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,1,n,M)==0){
            L=M;
        }else{
            R=M;
        }
    }
    return L+1;
}

ll bruteR1(){
    ll L=0,R=n;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,1,n,M)==2){
            R=M;
        }else{
            L=M;
        }
    }
    return R;
}

ll bruteT0(){
    ll L=1,R=n+1;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(M,1,n,n)==2){
            L=M;
        }else{
            R=M;
        }
    }
    return L;
}

ll bruteT1(){
    ll L=1,R=n+1;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(M,1,n,n)==0){
            R=M;
        }else{
            L=M;
        }
    }
    return R-1;
}

ll bruteB0(){
    ll L=0,R=n;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,1,M,n)==0){
            L=M;
        }else{
            R=M;
        }
    }
    return L+1;
}

ll bruteB1(){
    ll L=0,R=n;
    while (L+1<R){
        ll M=(L+R)/2;
        if (ask(1,1,M,n)==2){
            R=M;
        }else{
            L=M;
        }
    }
    return R;
}

void out(ll l0, ll r0, ll t0, ll b0, ll l1, ll r1, ll t1, ll b1){
    printf("! %lld %lld %lld %lld %lld %lld %lld %lld\n",t0,l0,b0,r0,t1,l1,b1,r1);
}

int main()
{
    scanll(n);
    ll l0,l1,r0,r1,t0,t1,b0,b1;
    l0=bruteL0();
    l1=bruteL1();
    r0=bruteR0();
    r1=bruteR1();
    t0=bruteT0();
    t1=bruteT1();
    b0=bruteB0();
    b1=bruteB1();

    if (ptLRLR(l0,l1,r0,r1)&&ptLRLR(t0,t1,b0,b1)){
        if (ask2(l0,r0,t0,b0)==1)
            out(l0,r0,t0,b0,l1,r1,t1,b1);
        else
            out(l0,r0,t1,b1,l1,r1,t0,b0);
    }else if (ptLRLR(l0,l1,r0,r1)&&ptLLRR(t0,t1,b0,b1)){
        if (ask2(l0,r0,t1,b0)==1)
            out(l0,r0,t1,b0,l1,r1,t0,b1);
        else if (ask2(l1,r1,t1,b0)==1)
            out(l1,r1,t1,b0,l0,r0,t0,b1);
        else if (ask2(l0,r0,t0,b0)==1)
            out(l0,r0,t0,b0,l1,r1,t1,b1);
        else
            out(l0,r0,t1,b1,l1,r1,t0,b0);
    }else if (ptLLRR(l0,l1,r0,r1)&&ptLRLR(t0,t1,b0,b1)){
        if (ask2(l1,r0,t0,b0)==1)
            out(l1,r0,t0,b0,l0,r1,t1,b1);
        else if (ask2(l1,r0,t1,b1)==1)
            out(l1,r0,t1,b1,l0,r1,t0,b0);
        else if (ask2(l0,r0,t0,b0)==1)
            out(l0,r0,t0,b0,l1,r1,t1,b1);
        else
            out(l0,r0,t1,b1,l1,r1,t0,b0);
    }else {
        assert(false);
    }
    return 0;
}
