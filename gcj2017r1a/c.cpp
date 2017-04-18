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

ll divceil(ll x, ll y){
    return (x+y-1)/y;
}

ll simulate(ll hd, ll ad, ll hk, ll ak, ll b, ll d, ll bn, ll dn){
    ll ret=0;
    ll cap=hd;
    char last_action=0;

    while(true){
        assert(hd>=1);
        assert(hk>=1);
        ++ret;

        //dragon's move
        char exp_todo=(dn>0)?'d':(bn>0)?'b':'a';
        bool exp_knight_live=(exp_todo=='a')?(ad>=hk):true;
        ll exp_knight_atk=(exp_todo=='d')?max(ak-d,(ll)0):ak;
        bool exp_dragon_death=exp_knight_live&&hd<=exp_knight_atk;
        if (exp_dragon_death){
            if (last_action=='c') return -1;
            hd=cap;
            last_action='c';
        }else{
            switch(exp_todo){
                case 'a':
                    hk-=ad;
                    if (hk<0) return ret;
                    break;
                case 'b':
                    ad+=b;
                    --bn;
                    break;
                case 'd':
                    ak=max(ak-d,(ll)0);
                    --dn;
                    break;
            }
            last_action=exp_todo;
        }

        //knight's move
        hd=max(hd-ak,(ll)0);
        if (hd==0){
            return -1;
        }
    }
}

ll solve(ll hd, ll ad, ll hk, ll ak, ll b, ll d){
    ll ans=-1;
    cerr<<"solve entrance: ak="<<ak<<", ad="<<ad<<endl;
    rng(dn,0,divceil(ak,d)){
        rng(bn,0,divceil(hk-ad,b)){
            cerr<<"simu with dn="<<dn<<", bn="<<bn<<endl;
            ll res=simulate(hd,ad,hk,ak,b,d,bn,dn);
            cerr<<"simu dome"<<endl;
            if (res<0) continue;
            ans=(ans<0||res<ans)?res:ans;
        }
    }
    return ans;
}

int main()
{
    ll tn;scanll(tn);
    rng(ti,0,tn){
        ll hd,ad,hk,ak,b,d;cin>>hd>>ad>>hk>>ak>>b>>d;
        cerr<<"readed"<<endl;
        ll ans=solve(hd,ad,hk,ak,b,d);
        cout<<"Case #"<<(ti+1)<<": ";
        if (ans<0){
            cout<<"IMPOSSIBLE";
        }else{
            cout<<ans;
        }
        cout<<endl;
    }
    return 0;
}
