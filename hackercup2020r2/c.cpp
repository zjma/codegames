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
typedef multiset<ll> MSET;
//constants
const ll INF=0x1fffffffffffffff;
const double INFD=1e20;
const double EPS=1e-9;
const double PI = atan(1) * 4;
const ll M = 1000000007;

//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)

ll MSET_max(MSET &mset){
    if (mset.empty()) return -INF;
    return *mset.rbegin();
}
ll MSET_del_one(MSET &mset, ll val){
    auto itr=mset.find(val);
    if (itr!=mset.end()){
        mset.erase(itr);
        return 1;
    }
    return 0;
}

//scanf shortcuts
ll scan() {ll r;scanf("%lld",&r);return r;}
void scanstr(char *buf){scanf("%s",buf);}

void readArr(ll n, ll k, ll mm, VI &arr){
    rng(i,0,k){
        arr[i]=scan();
    }
    ll a=scan();
    ll b=scan();
    ll c=scan();
    rng(i,k,n){
        arr[i]=(a*arr[i-2]+b*arr[i-1]+c)%mm;
    }
}
#define msidOf(a,b) ((a)*2+(b))
ll solve(ll n, ll m, ll e, VI &X, VI &Y, VI &I, VI &W){
    ll ans=1;
    ll prevPart0Total=n;
    VI weight(n*m+n,1);
    ll totalWeight=n*m+n;
    VI segIdOf(n*m);
    VI spval(n);
    vector<MSET> msets(n*2);
    MSET part1mset;
    rng(i,0,n){
        ll j=X[i];
        ll flag=0;
        while (1){
            ll nj=(j+1)%m;
            if (j==Y[i]) flag=1;
            segIdOf[i*m+j]=flag;
            msets[msidOf(i,flag)].insert(1);
            if (nj==X[i]) break;
            j=nj;
        }
        spval[i]=min(MSET_max(msets[msidOf(i,0)]),MSET_max(msets[msidOf(i,1)]));
        part1mset.insert(spval[i]);
    }
    rng(ei,0,e){
        cerr<<"ei="<<ei<<endl;
        cerr<<"edge="<<I[ei]<<endl;
        ll part0Affected=0,part0Diff=0;
        if (I[ei]<n*m){//is inner edge
            part0Affected=1;
            ll cid=I[ei]/m;
            ll sid=segIdOf[I[ei]];
            MSET &curmset=msets[msidOf(cid,sid)];
            MSET &sibmset=msets[msidOf(cid,1-sid)];
            ll oldcurmax=MSET_max(curmset);
            ll sibmax=MSET_max(sibmset);
            MSET_del_one(curmset,weight[I[ei]]);
            curmset.insert(W[ei]);
            ll newcurmax=MSET_max(curmset);
            cerr<<"oldcurmax="<<oldcurmax<<endl;
            cerr<<"newcurmax="<<newcurmax<<endl;
            cerr<<"sibmax="<<sibmax<<endl;
            part0Diff=max(newcurmax,sibmax)-max(oldcurmax,sibmax);
            totalWeight+=W[ei]-weight[I[ei]];
            weight[I[ei]]=W[ei];
            //update part1mset
            ll newspval=min(sibmax,newcurmax);
            MSET_del_one(part1mset,spval[cid]);
            part1mset.insert(newspval);
            spval[cid]=newspval;
        }else{
            MSET_del_one(part1mset,weight[I[ei]]);
            part1mset.insert(W[ei]);
            totalWeight+=W[ei]-weight[I[ei]];
            weight[I[ei]]=W[ei];
        }
        cerr<<"totalWeight="<<totalWeight<<endl;
        ll part0Total=(part0Affected)?(prevPart0Total+part0Diff):prevPart0Total;
        ll part1Total=MSET_max(part1mset);
        ll fatEdgeTotal=part0Total+part1Total;
        ll cur=totalWeight-fatEdgeTotal;
        cerr<<"part0Total="<<part0Total<<endl;
        cerr<<"part1Total="<<part1Total<<endl;
        cerr<<"cur="<<cur<<endl;
        ans=ans*cur;
        prevPart0Total=part0Total;
    }
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();ll m=scan(); ll e=scan(); ll k=scan();
        VI X(n);
        VI Y(n);
        VI I(e);
        VI W(e);
        readArr(n,k,m,X);
        readArr(n,k,m,Y);
        readArr(e,k,n*m+n,I);
        readArr(e,k,1000000000,W);
        ll ans=solve(n,m,e,X,Y,I,W);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
