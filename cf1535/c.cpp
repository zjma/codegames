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

ll sum(VI &A) {
    ll ans=0;
    ll n=A.size();
    rng(i,0,n){
        ans+=A[i];
    }
    return ans;
}

void dump(VI &A) {
    ll n=A.size();
    cout<<'[';
    rng(i,0,n){
        cout<<A[i]<<",";
    }
    cout<<']'<<endl;
}

char buf[200001];
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        scanstr(buf);
        ll n=strlen(buf);
        VI f0(n);
        VI f1(n);
        if (buf[0]=='0'){
            f0[0]=1,f1[0]=0;
        } else if (buf[0]=='1'){
            f0[0]=0,f1[0]=1;
        } else {
            f0[0]=f1[0]=1;
        }
        rng(i,1,n){
            if (buf[i]=='0'){
                f0[i]=f1[i-1]+1;
                f1[i]=0;
            } else if (buf[i]=='1'){
                f0[i]=0;
                f1[i]=f0[i-1]+1;
            } else {
                f0[i]=f1[i-1]+1;
                f1[i]=f0[i-1]+1;
            }
        }
        VI ff(n);
        rng(i,0,n) ff[i]=max(f0[i],f1[i]);
        ll ans=sum(ff);
        cout<<ans<<endl;
    }
    return 0;
}
