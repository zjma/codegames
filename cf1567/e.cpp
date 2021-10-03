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

struct Node {
    ll tail;
    ll head;
    ll tailv;
    ll headv;
    ll ans;
    ll pref;
    ll suff;
    ll getLen(){
        return tail-head+1;
    }
};

ll log2ceil(ll x){
    ll ans=0;
    ll build=1;
    while(build<x){
        ans++;
        build*=2;
    }
    return ans;
}

void calc(Node &ch0, Node &ch1, Node &prt){
    ll smooth=ch0.tailv<=ch1.headv;
    ll combined=smooth?(ch0.suff*ch1.pref):0;
    prt.ans=ch0.ans+ch1.ans+combined;
    prt.head=ch0.head;
    prt.tail=ch1.tail;
    prt.pref=(ch0.pref==ch0.getLen()&&smooth)?(ch0.getLen()+ch1.pref):ch0.pref;
    prt.suff=(ch1.suff==ch1.getLen()&&smooth)?(ch1.getLen()+ch0.suff):ch1.suff;
    prt.tailv=ch1.tailv;
    prt.headv=ch0.headv;
}

void query(vector<Node> &T, ll cur, ll ql, ll qr, Node &ret){
    ql=max(ql,T[cur].head);
    qr=min(qr,T[cur].tail);
    if (ql>qr){
        ret.ans=0;
        ret.pref=0;
        ret.suff=0;
        ret.headv=-INF;
        ret.tailv=INF;
        ret.head=-1;
        ret.tail=-1;
        return;
    }
    if (ql==T[cur].head&&qr==T[cur].tail){
        ret.ans=T[cur].ans;
        ret.pref=T[cur].pref;
        ret.suff=T[cur].suff;
        ret.tail=T[cur].tail;
        ret.head=T[cur].head;
        ret.tailv=T[cur].tailv;
        ret.headv=T[cur].headv;
        return;
    }
    Node left;
    Node right;
    query(T,cur*2+1,ql,qr,left);
    query(T,cur*2+2,ql,qr,right);
    calc(left,right,ret);
    // printf("cur=%lld, segL=%lld, segR=%lld, ql=%lld, qr=%lld, ans=%lld\n", cur, T[cur].head, T[cur].tail, ql, qr, ret.ans);
}

int main()
{
    ll n=scan();
    ll n2=1<<log2ceil(n);
    ll q=scan();
    ll tn=n2*2-1;
    vector<Node> T(tn);
    rng(i,0,n){
        ll v=scan();
        ll ii=n2-1+i;
        T[ii].tailv=T[ii].headv=v;
        T[ii].ans=1;
        T[ii].suff=1;
        T[ii].pref=1;
        T[ii].head=i;
        T[ii].tail=i;
    }
    rng(i,n,n2){
        ll ii=n2-1+i;
        T[ii].tailv=T[ii].headv=0;
        T[ii].ans=1;
        T[ii].suff=1;
        T[ii].pref=1;
        T[ii].head=i;
        T[ii].tail=i;
    }
    rng(i,0,n2-1){
        ll ii=n2-2-i;
        calc(T[ii*2+1],T[ii*2+2],T[ii]);
    }
    rng(i,0,q){
        ll cmd=scan();
        ll x=scan();
        ll y=scan();
        if (cmd==1){
            ll xx=n2-1+x-1;
            T[xx].headv=T[xx].tailv=y;
            while(xx>0){
                xx=(xx-1)/2;
                calc(T[xx*2+1],T[xx*2+2],T[xx]);
            }
        }else{
            Node tmp;
            query(T,0,x-1,y-1,tmp);
            cout<<tmp.ans<<endl;
        }
    }
    return 0;
}
