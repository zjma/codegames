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

const ll N=200000;
char buf[N+1];
ll F[N][3][3];
ll PF[3][3][N+1];
ll V[3][3];
void initV(){
    rng(i,0,3)
        rng(j,0,3)
            V[i][j]=0;
}
ll calc(){
    ll ans=INF;
    ans=min(ans,V[0][1]+V[0][2]+V[1][0]+V[1][2]+V[2][0]+V[2][1]);
    ans=min(ans,V[0][1]+V[0][2]+V[1][0]+V[1][1]+V[2][0]+V[2][2]);
    ans=min(ans,V[0][0]+V[0][2]+V[1][1]+V[1][2]+V[2][0]+V[2][1]);
    ans=min(ans,V[0][0]+V[0][2]+V[1][0]+V[1][1]+V[2][1]+V[2][2]);
    ans=min(ans,V[0][0]+V[0][1]+V[1][1]+V[1][2]+V[2][0]+V[2][2]);
    ans=min(ans,V[0][0]+V[0][1]+V[1][0]+V[1][2]+V[2][1]+V[2][2]);
    return ans;
}

ll onQuery(ll li, ll ri){
    initV();
    rng(i,0,3){
        rng(j,0,3){
            V[i][j]+=PF[i][j][ri+1]-PF[i][j][li];
        }
    }
    return calc();
}

int main()
{
    ll n=scan();
    ll m=scan();
    scanstr(buf);
    rng(i,0,n){
        F[i][i%3][buf[i]-97]++;
    }
    rng(i,0,n){
        rng(j,0,3){
            rng(k,0,3){
                PF[j][k][i+1]=PF[j][k][i]+F[i][j][k];
            }
        }
    }
    rng(i,0,m){
        ll li=scan()-1;
        ll ri=scan()-1;
        printf("%lld\n", onQuery(li,ri));
    }
    return 0;
}
