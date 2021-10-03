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

ll lowdit(ll x){
    ll ans=1;
    while(x%10==0){
        x/=10;
        ans*=10;
    }
    return ans;
}

ll ln(ll x){
    ll ans=0;
    while(x>=10){
        ans++;
        x/=10;
    }
    return ans;
}

ll p10[10];
void init(){
    p10[0]=1;
    rng(i,1,10){
        p10[i]=p10[i-1]*10;
    }
}
int main()
{
    init();
    ll tn=scan();
    rng(ti,0,tn){
        ll s=scan();
        ll n=scan();
        priority_queue<ll> hp;
        VI oc(10);
        if (lowdit(s)==s){
            oc[ln(s)]++;
        }else{
            hp.push(s);
        }
        rng(i,0,n-1){
            ll fish;
            if (!hp.empty()){
                fish=hp.top();
                hp.pop();
                ll lowd=lowdit(fish);
                ll other=fish-lowd;
                oc[ln(lowd)]++;
                if (other==p10[ln(other)]){
                    oc[ln(other)]++;
                }else{
                    hp.push(other);
                }
            }else{
                rng(i,1,10){
                    if (oc[i]>=1){
                        oc[i]--;
                        oc[i-1]++;
                        hp.push(p10[i-1]*9);
                        break;
                    }
                }
            }
        }
        rng(i,0,10){
            ll v=p10[i];
            rng(j,0,oc[i]){
                cout<<v<<' ';
            }
        }
        while(!hp.empty()){
            cout<<hp.top()<<' ';
            hp.pop();
        }
        cout<<endl;

    }
    return 0;
}
