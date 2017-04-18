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


string calc(string game, ll round){
    if (round==0){
        if (game=="PR"||game=="RP") return "PR";
        if (game=="PS"||game=="SP") return "PS";
        if (game=="SR"||game=="RS") return "RS";
        assert(false);
    }
    string sub1=(game[0]=='P')?calc("PR",round-1):(game[0]=='R')?calc("RS",round-1):calc("PS",round-1);
    string sub2=(game[1]=='P')?calc("PR",round-1):(game[1]=='R')?calc("RS",round-1):calc("PS",round-1);
    if (sub1<sub2) return sub1+sub2; else return sub2+sub1;
}

tuple<ll,ll,ll> scount(string &s){
    ll cp=0,cr=0,cs=0;
    for (auto c:s){
        if (c=='P') ++cp;
        if (c=='R') ++cr;
        if (c=='S') ++cs;
    }
    return make_tuple(cr,cp,cs);
}

int main()
{
    ll TN;scanll(TN);
    rng(TI,1,TN+1){
        ll n,r,p,s;scanll(n);scanll(r);scanll(p);scanll(s);
        string ret1 = calc("PR",n-1);
        ll ansr1,ansp1,anss1;tie(ansr1,ansp1,anss1)=scount(ret1);
        string ret2 = calc("PS",n-1);
        ll ansr2,ansp2,anss2;tie(ansr2,ansp2,anss2)=scount(ret2);
        string ret3 = calc("SR",n-1);
        ll ansr3,ansp3,anss3;tie(ansr3,ansp3,anss3)=scount(ret3);
        string ans=(ansr1==r&&ansp1==p&&anss1==s)?ret1:(ansr2==r&&ansp2==p&&anss2==s)?ret2:(ansr3==r&&ansp3==p&&anss3==s)?ret3:"IMPOSSIBLE";
        printf("Case #%lld: %s\n", TI, ans.c_str());
        //cerr<<ret1<<","<<ret2<<","<<ret3<<endl;
    }
    return 0;
}
