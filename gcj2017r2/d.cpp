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

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll r=scan();
        ll c=scan();
        ll m=scan();
        vector<string> map(r);
        rng(i,0,r){
            cin>>map[i];
        }
        VI sx;
        VI sy;
        VI tx;
        VI ty;
        rng(i,0,r){
            rng(j,0,c){
                if (map[i][j]=='S'){
                    sx.push_back(i);
                    sy.push_back(j);
                }else if (map[i][j]=='T'){
                    tx.push_back(i);
                    ty.push_back(i);
                }
            }
        }
        ll sn=sx.size();
        ll tn=tx.size();
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
