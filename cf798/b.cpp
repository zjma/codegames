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

ll movefromto(string &f, string &t){
    ll n=f.size();
    ll m=t.size();
    if (n!=m) return -1;
    rng(i,0,n){
        ll flag=1;
        rng(j,0,n){
            if (f[(i+j)%n]!=t[j]) {
                flag=0;
                break;
            }
        }
        if (flag) return i;
    }
    return -1;
}

int main()
{
    ll n;cin>>n;
    vector<string> s(n);
    rng(i,0,n){
        cin>>s[i];
    }
    VI a(n);
    rng(i,1,n){
        a[i]=movefromto(s[i],s[0]);
        if (a[i]<0){cerr<<"Bad "<<s[i]<<" "<<s[0]<<endl;
            cout<<-1<<endl;
            return 0;
        }
    }
    VI ans(n);
    rng(i,0,n){
        rng(j,0,n){
            ans[i]+=a[j];
        }
        ll d=a[(i+1)%n];
        rng(j,0,n){
            a[j]=(a[j]-d+n)%n;
        }
    }
    ll bst=INF;
    rng(i,0,n){
        bst=min(bst,ans[i]);
    }
    cout<<bst<<endl;
    return 0;
}
