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

ll pow3(ll n){
    ll res=1;
    rng(i,0,n) res*=3;
    return res;
}
ll sm(VI &A, ll mask){
    ll n=A.size();
    ll res=0;
    ll i=0;
    while (mask>0){
        if (mask%3==2){
            res+=A[i];
        }
        else if(mask%3==1){
            res-=A[i];
        }
        i++;
        mask/=3;
    }
    return res;
}

bool work(VI &A){
    ll n=A.size();
    rng(i,1,pow3(n)){
        if (sm(A,i)==0) {
            return true;
        }
    }
    return false;
}
int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI A(n);
        rng(i,0,n){
            A[i]=scan();
        }
        cout<<(work(A)?"YES":"NO")<<endl;
    }
    return 0;
}
