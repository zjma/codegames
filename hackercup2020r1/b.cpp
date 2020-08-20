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
ll mod(ll x, ll M) { return ((x%M) + M) % M; }
ll add(ll a, ll b, ll M){return mod(mod(a,M)+mod(b,M),M);}
ll mul(ll a, ll b, ll M){return mod(mod(a,M)*mod(b,M),M);}

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)
void dumpVI(const VI &a, const string &pfx){
    ll n=a.size();
    rng(i,0,n){
        cerr<<pfx<<"["<<i<<"]="<<a[i]<<endl;
    }
}


//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}
void readArr(ll n, ll k, VI &Arr){
    rng(i,0,k) Arr[i]=scan();
    ll A=scan();
    ll B=scan();
    ll C=scan();
    ll D=scan();
    rng(i,k,n){
        Arr[i]=add(add(mul(A,Arr[i-2],D),mul(B,Arr[i-1],D),D),C,D)+1;
    }
}

bool willWork(const ll timeLimit, const ll S, const VI &P, const VI &Q){
    ll qn=Q.size();
    ll pn=P.size();
    ll pi=0;
    VI firstAssignment(pn,-1);
    rng(qi,0,qn){
        while(pi<pn){
            ll qi_earliest=(firstAssignment[pi]<0)?qi:firstAssignment[pi];
            ll maxTaskPos=Q[qi];
            ll minTaskPos=Q[qi_earliest];
            ll taskCount=qi-qi_earliest+1;
            ll minTime=taskCount*S+(maxTaskPos-minTaskPos)+min(abs(P[pi]-maxTaskPos),abs(P[pi]-minTaskPos));
            if (minTime<=timeLimit) break;
            pi+=1;
        }
        if (pi>=pn) return false;
        if (firstAssignment[pi]<0) firstAssignment[pi]=qi;
    }
    return true;
}

void testWillWork(){
    VI Q;
    Q.push_back(13);
    Q.push_back(16);
    VI P;
    P.push_back(10);
    P.push_back(20);
    ll S=100;
    assert(willWork(104,S,P,Q));
    assert(!willWork(103,S,P,Q));
}

ll solve(const ll n, const ll m, const ll S, const VI &P, const VI &Q){
    ll hi=1;
    while(!willWork(hi,S,P,Q)) hi*=2;
    ll lo=0;
    while(lo+1<hi){
        ll mi=(lo+hi)/2;
        if(willWork(mi,S,P,Q)){
            hi=mi;
        }else{
            lo=mi;
        }
    }
    return hi;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        ll m=scan();
        ll k=scan();
        ll s=scan();
        VI P(n);
        VI Q(m);
        readArr(n,k,P);
        readArr(m,k,Q);
        sort(P.begin(),P.end());
        sort(Q.begin(),Q.end());
        ll ans=solve(n,m,s,P,Q);
        cout<<"Case #"<<(ti+1)<<": "<<ans<<endl;
    }
    return 0;
}
