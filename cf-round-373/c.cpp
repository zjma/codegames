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

const int N=200001;
char b[N];
int main()
{
    ll n,t;
    scanll(n);scanll(t);
    scanstr(b);

    ll acc4=0;
    ll cut=-1;
    bool afterdot=false;
    rng(i,0,n){
        if (afterdot){
            if (b[i]>='5'){
                cut=i-min(acc4,t-1);
                break;
            }else if (b[i]=='4'){
                acc4++;
            }else{
                acc4=0;
            }
        }else{
            if (b[i]=='.') afterdot=true;
        }
    }
    ll x = (cut==-1)?(n-1):(cut-1);
    ll carry=(cut==-1)?0:1;
    string ans;
    while (x>=0){
        if (b[x]=='.') {
            ans.push_back('.');
            x--;
            continue;
        }
        ll v = b[x]-48+carry;
        carry = v/10;
        v = v % 10;
        ans.push_back(v+48);
        x-=1;
    }
    if (carry==1) ans.push_back('1');

    ll nn=ans.size();
    rng(i,0,nn/2){
        swap(ans[i],ans[nn-1-i]);
    }

    x = nn-1;
    while (ans[x]=='0' || ans[x]=='.'){
        bool bk=ans[x]=='.';
        ans.pop_back();
        x--;
        if (bk) break;
    }
    cout<<ans<<endl;
    return 0;
}
