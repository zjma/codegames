// template.cpp : Defines the entry point for the console application.
//
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
ll scan() {ll r;cin>>r;return r;}
void scanstr(char *buf){scanf("%s",buf);}

int main()
{
    ll n=scan();
    VI a(n);
    rng(i,0,n){
        a[i]=scan();
    }

    rng(i,1,n){
        ll dy=a[i]-a[0];
        ll dx=i;
        VI mark(n);
        ll todocount=0;
        rng(j,1,n){
            ll tdy=a[j]-a[0];
            ll tdx=j;
            mark[j]=(dx*tdy==dy*tdx);
            if (!mark[j]) ++todocount;
        }
        if (todocount==0) continue;
        if (todocount==1){
            cout<<"Yes"<<endl;
            return 0;
        }
        bool fine=true;
        ll st=0;
        ll lx2,ly2;
        rng(j,1,n){
            if (mark[j]) continue;
            if (st==0){
                lx2=j;
                ly2=a[j];
                st=1;
            }else{
                ll tdx=j-lx2;
                ll tdy=a[j]-ly2;
                fine=fine&&(tdx*dy==tdy*dx);
            }
        }
        if (fine){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    ll g0=a[1]-a[0];
    ll g1=a[2]-a[1];
    bool fine2=true;
    rng(i,3,n){
        fine2=fine2&&(a[i]-a[i-1]==g1);
    }
    if (g0!=g1&&fine2){
        cout<<"Yes"<<endl;
        return 0;
    }
    cout<<"No"<<endl;
    return 0;
}
