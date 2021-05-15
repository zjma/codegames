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

const ll LEN=1000001;
char buf[LEN];

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        scanstr(buf);
        ll n=strlen(buf);
        if (n==1){
            cout<<0<<endl;
        }else{
            VI f00(n);
            VI f01(n);
            VI f10(n);
            VI f11(n);
            f00[1]=(buf[0]==buf[1])?INF:0;
            f01[1]=1;
            f10[1]=1;
            f11[1]=2;
            rng(i,2,n){
                if (buf[i]==buf[i-1]&&buf[i-1]==buf[i-2]){//aaa
                    f00[i]=INF;
                    f01[i]=f10[i-1]+1;
                    f10[i]=f11[i-1];//XXO
                    f11[i]=min(f11[i-1],f01[i-1])+1;
                }else if (buf[i-2]==buf[i-1]&&buf[i-1]!=buf[i]){//aab
                    f00[i]=f10[i-1];
                    f01[i]=f10[i-1]+1;
                    f10[i]=min(f11[i-1],f01[i-1]);
                    f11[i]=min(f11[i-1],f01[i-1])+1;
                }else if (buf[i-2]!=buf[i-1]&&buf[i-1]!=buf[i]&&buf[i-2]!=buf[i]){//abc
                    f00[i]=min(f10[i-1],f00[i-1]);
                    f01[i]=min(f10[i-1],f00[i-1])+1;
                    f10[i]=min(f01[i-1],f11[i-1]);
                    f11[i]=min(f01[i-1],f11[i-1])+1;
                }else if (buf[i-2]==buf[i]&&buf[i-1]!=buf[i]){//aba
                    f00[i]=f10[i-1];
                    f01[i]=min(f00[i-1],f10[i-1])+1;
                    f10[i]=f11[i-1];
                    f11[i]=min(f01[i-1],f11[i-1])+1;
                }else if (buf[i-1]==buf[i]&&buf[i-2]!=buf[i]){//abb
                    f00[i]=INF;
                    f01[i]=min(f10[i-1],f00[i-1])+1;
                    f10[i]=min(f01[i-1],f11[i-1]);
                    f11[i]=min(f01[i-1],f11[i-1])+1;
                }else{
                    assert(0);
                }
            }
            cout<<min(min(f00[n-1],f01[n-1]),min(f10[n-1],f11[n-1]))<<endl;
        }
    }

    return 0;
}
