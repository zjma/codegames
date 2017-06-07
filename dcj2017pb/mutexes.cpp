#include <message.h>
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
#include "mutexes.h"
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

ll ME=0;
ll NODES=0;

pair<ll,ll> get_interval(ll NODES, ll ME, ll n) {
    ll n2=n%NODES;
    ll n1=NODES-n2;
    ll l1=n/NODES;
    ll l2=l1+1;
    ll L,R;
    if (ME<n2){
        L=l2*ME;
        R=L+l2-1;
    }else{
        L=l2*n2+l1*(ME-n2);
        R=L+l1-1;
    }
    return make_pair(L,R);
}

ll TL[100];
ll TR[100];
ll xcmd[40001];
ll ycmd[40001];
bool xacqed[100001];
bool xyacqed[100001];
bool unava[501][50001];

int main()
{
    srand(time(NULL));
    ME=MyNodeId();
    NODES=NumberOfNodes();
    ll OPN0=NumberOfOperations(0)+1;
    ll OPN1=NumberOfOperations(1)+1;

    rng(i,0,NODES){
        tie(TL[i],TR[i])=get_interval(NODES,i,OPN0-1);
        ++TL[i];
        ++TR[i];
    }
    if (TL[ME]>TR[ME]) return 0;
    ll VNODES=min(NODES,OPN0-1);

    rng(i,0,OPN1){
        ycmd[i]=(i==OPN1-1)?-INF:GetOperation(1,i);
    }
    rng(i,0,OPN0){
        xcmd[i]=(i==OPN0-1)?-INF:GetOperation(0,i);
    }

    rng(i,0,TL[ME]){
        if (xcmd[i]>0){
            xacqed[xcmd[i]]=true;
        }else{
            xacqed[-xcmd[i]]=false;
        }
    }

    // VVI unava(TR[ME]-TL[ME]+2,VI(OPN1));//[TL[ME]..TR[ME]+1][1..OPN1]
    rng(i,TL[ME],TR[ME]+2){//require xcmd[TL[ME]..TR[ME]]
        memset(xyacqed,0,sizeof(bool)*100001);
        ll xyacqed_ctr=0;
        rng(j,1,OPN1){
            if (ycmd[j-1]>0){
                xyacqed[ycmd[j-1]]=xacqed[ycmd[j-1]];
                if (xyacqed[ycmd[j-1]]) ++xyacqed_ctr;
            }else{
                if (xyacqed[-ycmd[j-1]]) --xyacqed_ctr;
                xyacqed[-ycmd[j-1]]=false;
            }
            unava[i-TL[ME]][j-1]=(xyacqed_ctr>0);
        }
        unava[i-TL[ME]][OPN1-1]=false;
        if (xcmd[i]==-INF){

        }else if (xcmd[i]>0){
            xacqed[xcmd[i]]=true;
        }else{
            xacqed[-xcmd[i]]=false;
        }
    }

    ll ans=INF;
    rng(i,TL[ME],TR[ME]+1){//TL[ME]..TR[ME]
        rng(j,1,OPN1){//1..OPN1-1
            if (!unava[i-TL[ME]][j-1]&&unava[i+1-TL[ME]][j-1]&&unava[i-TL[ME]][j]){
                ans=min(ans,i+j);
            }
        }
    }
    PutLL(0,ans);
    Send(0);

    if (ME==0){
        ll ans=INF;
        rng(i,0,VNODES){
            Receive(i);
            ans=min(ans,GetLL(i));
        }
        if (ans==INF){
            cout<<"OK"<<endl;
        }else{
            cout<<ans+2<<endl;
        }
    }
    return 0;
}
