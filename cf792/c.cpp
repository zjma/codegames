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

const int N=100000;
char buf[N+1];
ll f[N+1][3];
ll g[N+1];
ll p[N+1][3];
bool pz[N+1];

int an=0;
char ans[N+1];
void put(ll i, ll j){
    if (p[i][j]==-1){
        ans[an++]=buf[i-1];
        return;
    }
    if (p[i][j]==0){
        auto val=buf[i-1]-48;
        auto vr=val%3;
        put(i-1,(j+3-vr)%3);
        ans[an++]=buf[i-1];
        return;
    }
    put(i-1,j);
}

int main()
{
    scanstr(buf);
    ll n=strlen(buf);
    pz[0]=false;
    g[0]=f[0][0]=f[0][1]=f[0][2]=INT_MAX;
    rng(i,1,n+1){
        ll val=buf[i-1]-'0';
        ll vr=val%3;
        pz[i]=pz[i-1]||val==0;
        g[i]=(pz[i])?(i-1):INT_MAX;
        rng(j,0,3){
            f[i][j]=INT_MAX;
            if (vr==j && val!=0 && i-1<f[i][j]){
                f[i][j]=i-1;
                p[i][j]=-1;
            }
            if (f[i-1][(j+3-vr)%3]<f[i][j]){
                f[i][j]=f[i-1][(j+3-vr)%3];
                p[i][j]=0;
            }
            if (f[i-1][j]+1<f[i][j]){
                f[i][j]=f[i-1][j]+1;
                p[i][j]=1;
            }
            //printf("f(%lld,%lld)=%lld\n",i,j,f[i][j]);
        }
    }
    if (f[n][0]>=INT_MAX&&g[n]>=INT_MAX) {
        cout<<-1<<endl;
        return 0;
    }
    if (g[n]<=f[n][0]){
        cout<<0<<endl;
        return 0;
    }
    stack<int> stk;
    ll i=n,j=0;
    while(true){
        if (p[i][j]!=1) stk.push(i-1);
        if (p[i][j]==-1) break;
        if (p[i][j]==0){
            auto val=buf[i-1]-48;
            auto vr=val%3;
            j=(j+3-vr)%3;
        }
        --i;
    }
    while(!stk.empty()){
        ans[an++]=buf[stk.top()];
        stk.pop();
    }
    ans[an]=0;
    printf("%s\n",ans);
    return 0;
}
