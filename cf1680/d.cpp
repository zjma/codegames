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

const ll MAXN=3000;
ll n;
ll pref0count[MAXN+1];
ll prefsum[MAXN+1];
ll initpref0count(VI &A){
    pref0count[0]=0;
    ll n=A.size();
    rng(i,0,n){
        ll cur=(A[i]==0)?1:0;
        pref0count[i+1]=pref0count[i]+cur;
    }
}
ll seg0count(ll i0, ll i1){
    if(i0<=i1){
        return pref0count[i1+1]-pref0count[i0];
    }else{
        return pref0count[n]-pref0count[i0]+pref0count[i1+1];
    }
}
ll initprefsum(VI &A){
    prefsum[0]=0;
    ll n=A.size();
    rng(i,0,n){
        prefsum[i+1]=prefsum[i]+A[i];
    }
}
ll segsum(ll i0, ll i1){
    if(i0<=i1){
        return prefsum[i1+1]-prefsum[i0];
    }else{
        return prefsum[n]-prefsum[i0]+prefsum[i1+1];
    }
}

ll next(ll i){
    return (i+1)%n;
}

ll prev(ll i){
    return (i+n-1)%n;
}
ll work(VI &A, ll k){
    n=A.size();
    initpref0count(A);
    initprefsum(A);
    ll ans=-1;
    rng(i,0,n){
        ll invalid=0;
        ll prevsum=0;
        ll best=0;
        rng(j,0,n){
            ll ci=(i+j)%n;
            ll cur;
            if(j==n-1){
                if(A[ci]==0){
                    if (prevsum>k){
                        invalid=1;
                        break;
                    }
                    cur=-prevsum;
                }else{
                    cur=A[ci];
                }
            }else{
                if(A[ci]==0){
                    ll nextsum=segsum(next(ci),prev(i));
                    ll next0count=seg0count(next(ci),prev(i));
                    ll lower=-next0count*k-prevsum-nextsum;
                    ll upper=next0count*k-prevsum-nextsum;
                    if(lower>k||upper<-k){
                        invalid=1;
                        break;
                    }
                    cur=min(k,upper);
                }else{
                    cur=A[ci];
                }
            }
            prevsum+=cur;
            if(prevsum<0){
                invalid=1;
                break;
            }
            if(j==n-1&&prevsum!=0){
                invalid=1;
                break;
            }
            best=max(best,prevsum);
        }
        if(!invalid){
            ans=max(ans,best);
        }
    }
    return ans;
}

int main()
{
    ll n=scan();
    ll k=scan();
    VI A(n);
    rng(i,0,n){
        A[i]=scan();
    }
    ll ans=work(A,k);
    if(ans>=0) ans++;
    printf("%lld\n", ans);
    return 0;
}
