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


int main()
{
    ll n;scanll(n);
    ll k;scanll(k);
    ll m=n;
    VI ans;
    rng(i,2,n+1){
        while (m%i==0){
            m/=i;
            ans.push_back(i);
        }
    }
    ll an=ans.size();
    if (an<k){
        cout<<-1<<endl;
    }else{
        rng(i,0,k-1){
            cout<<ans[i]<<' ';
        }
        ll last=1;
        rng(i,k-1,an){
            last*=ans[i];
        }
        cout<<last<<endl;
    }
    return 0;
}
