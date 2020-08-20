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
ll minInVI(VI &arr){
    ll ans=INF;
    for (auto x:arr){
        ans=min(ans,x);
    }
    return ans;
}
void testMinInVI(){
    VI arr;
    arr.push_back(3);
    arr.push_back(-3);
    arr.push_back(2);
    arr.push_back(-2);
    assert(-3==minInVI(arr));
}
ll VI2pattern(VI &pv){
    ll rn=pv.size();
    ll ans=0;
    rng(i,0,rn){
        ans|=pv[i]*(1<<i);
    }
    return ans;
}
void testVI2pattern(){
    VI arr;
    arr.push_back(0);
    arr.push_back(0);
    assert(0==VI2pattern(arr));
}
ll getUpdateCost(ll pattern0, ll pattern1){
    ll ans=0;
    while (pattern0>0||pattern1>0){
        if (pattern0%2!=pattern1%2) ans++;
        pattern0/=2;
        pattern1/=2;
    }
    return ans;
}
void testGetUpdateCost(){
    ll p1=5;
    ll p2=2;
    assert(3==getUpdateCost(p1,p2));
    assert(3==getUpdateCost(p2,p1));
    ll p3=7;
    ll p4=6;
    assert(1==getUpdateCost(p3,p4));
}

VI getValidPrePatterns(ll rn, ll cur_pattern){
    VI ans;
    ll p0;
    ll p1;
    if (rn==2){
        ll a=cur_pattern%2;
        ll b=(cur_pattern/2)%2;
        ll x0=0;
        ll y0=1^a^b^x0;
        ll x1=1;
        ll y1=1^a^b^x1;
        p0=x0+y0*2;
        p1=x1+y1*2;
    }else{
        ll a=cur_pattern%2;
        ll b=(cur_pattern/2)%2;
        ll c=(cur_pattern/4)%2;
        ll x0=0;
        ll y0=1^a^b^x0;
        ll z0=1^b^c^y0;
        ll x1=1;
        ll y1=1^a^b^x1;
        ll z1=1^b^c^y1;
        p0=x0+y0*2+z0*4;
        p1=x1+y1*2+z1*4;
    }
    ans.push_back(p0);
    ans.push_back(p1);
    return ans;
}
void testGetValidPrePatterns(){
    VI actual=getValidPrePatterns(3,3);//011
    sort(actual.begin(),actual.end());
    assert(1==actual[0]);
    assert(6==actual[1]);
}
void getPatterns(ll &rn, ll &cn, vector<string> &row, VI &originalPatterns){
    if (rn<=3){
        originalPatterns.resize(cn,0);
        rng(ci,0,cn){
            rng(ri,0,rn){
                originalPatterns[ci]+=(1<<ri)*(row[ri][ci]-48);
            }
        }
    }else{
        originalPatterns.resize(rn,0);
        rng(ci,0,cn){
            rng(ri,0,rn){
                originalPatterns[ri]+=(1<<ci)*(row[ri][ci]-48);
            }
        }
        swap(rn,cn);
    }
}
void testGetPatterns(){
    ll rn=4;
    ll cn=3;
    vector<string> row(4);
    row[0]="101";
    row[1]="001";
    row[2]="110";
    row[3]="111";
    VI originalPatterns;
    getPatterns(rn,cn,row,originalPatterns);
    assert(originalPatterns[0]==5);
    assert(originalPatterns[1]==4);
    assert(originalPatterns[2]==3);
    assert(originalPatterns[3]==7);
    assert(rn==3);
    assert(cn==4);
}

int main()
{
    ll rn=scan();
    ll cn=scan();
    vector<string> row(rn);
    rng(ri,0,rn){
        cin>>row[ri];
    }
    if (rn>=4&&cn>=4){
        cout<<-1<<endl;
    }else if (rn==1||cn==1){
        cout<<0<<endl;
    }else{
        VI patternsOriginal;
        getPatterns(rn,cn,row,patternsOriginal);
        ll pn=1<<rn;
        VVI f(cn+1,VI(pn,INF));
        rng(pattern_cur,0,pn){
            f[1][pattern_cur]=getUpdateCost(patternsOriginal[0], pattern_cur);
        }
        rng(ck,2,cn+1){
            rng(cur_pattern,0,pn){
                ll update_cost = getUpdateCost(patternsOriginal[ck-1],cur_pattern);
                for(ll pre_pattern:getValidPrePatterns(rn,cur_pattern)){
                    f[ck][cur_pattern]=min(f[ck][cur_pattern],f[ck-1][pre_pattern]+update_cost);
                }
            }
        }
        cout<<minInVI(f[cn])<<endl;
    }
    return 0;
}
