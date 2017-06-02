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
#include "air_show.h"
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
void INIT() {ME=MyNodeId();NODES=NumberOfNodes();}

/**
 * Distribute segment [0,n-1] to nodes [0,NODES-1] almost uniformly.
 *
 * Example 1: n=12,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-2     3-5     6-7     8-9     10-11
 * segsize  3       3       2       2       2
 *
 * Example 2: n=3,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-0     1-1     2-2     3-2     3-2
 * segsize  1       1       1       0       0
 *
 * Example 3: n=10,NODES=5
 * NODEID   0       1       2       3       4
 * segrange 0-1     2-3     4-5     6-7     8-9
 * segsize  2       2       2       2       2
 *
 */
pair<ll,ll> get_my_inverval(ll n) {
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

ll N;
ll SD;
VVI tids(2);
VVI stmps(2);
VVI xs(2);
VVI ys(2);
VVI zs(2);
VI ans(2);
VI tmpn(2);

void appendPosition(ll which, ll tid){
    ll pos=GetPosition(which,tid);
    ll posx=(pos&0xfffff0000000000)>>40;
    ll posy=(pos&0xfffff00000)>>20;
    ll posz=pos&0xfffff;
    xs[which].push_back(posx);
    ys[which].push_back(posy);
    zs[which].push_back(posz);
}

pair<ll,ll> getkey(ll which, ll i){
    return make_pair(stmps[which][i],which);
}

bool dangerdist(ll which){
    ll myn=tmpn[which];
    ll yrn=tmpn[1-which];
    assert(myn>=1);
    assert(yrn>=2);
    assert(getkey(1-which,yrn-2)<getkey(which,myn-1));
    assert(getkey(which,myn-1)<getkey(1-which,yrn-1));
    ll x0=xs[1-which][yrn-2];
    ll x1=xs[1-which][yrn-1];
    ll y0=ys[1-which][yrn-2];
    ll y1=ys[1-which][yrn-1];
    ll z0=zs[1-which][yrn-2];
    ll z1=zs[1-which][yrn-1];
    ll x=xs[which][myn-1];
    ll y=ys[which][myn-1];
    ll z=zs[which][myn-1];
    //cerr<<endl;
    //cerr<<"P0=("<<x0<<","<<y0<<","<<z0<<"), t0="<<stmps[1-which][yrn-2]<<endl;
    //cerr<<"P1=("<<x1<<","<<y1<<","<<z1<<"), t1="<<stmps[1-which][yrn-1]<<endl;
    //cerr<<"PP=("<<x<<","<<y<<","<<z<<"), tt="<<stmps[which][myn-1]<<endl;

    ll dt0=stmps[which][myn-1]-stmps[1-which][yrn-2];
    ll dt1=stmps[1-which][yrn-1]-stmps[which][myn-1];
     __int128 t=dt0+dt1;

     __int128 tdx=dt0*x1+dt1*x0-t*x;
     __int128 tdy=dt0*y1+dt1*y0-t*y;
     __int128 tdz=dt0*z1+dt1*z0-t*z;
    bool flag=tdx*tdx+tdy*tdy+tdz*tdz<SD*SD*t*t;
    if (flag) {
        //cerr<<"DANGER"<<endl;
    }
    //cerr<<endl;
    return flag;
}

void fetchNextSegment(ll which){
    ll tn=tmpn[which];
    assert(tn>=1);
    ll oldtid=tids[which][tn-1];
    ll oldstamp=stmps[which][tn-1];
    ll newtid=oldtid+1;
    ll dt=GetTime(which,oldtid);
    ll newstamp=oldstamp+dt;
    tids[which].push_back(newtid);
    stmps[which].push_back(newstamp);
    appendPosition(which,newtid);
    ++tmpn[which];
}


int main()
{
    srand(time(NULL));
    INIT();
    N=GetNumSegments();
    SD=GetSafeDistance();
    ll L,R;tie(L,R)=get_my_inverval(N);
    ll t0acc=0;
    ll t1acc=0;
    rng(i,L,R+1){
        t0acc+=GetTime(0,i);
        t1acc+=GetTime(1,i);
    }
    PutLL(0,L);
    PutLL(0,R);
    PutLL(0,t0acc);
    PutLL(0,t1acc);
    Send(0);

    if (ME==0){
        vector<tuple<ll,ll,ll>> events;
        events.emplace_back(0,0,0);
        events.emplace_back(0,1,0);
        ll t0acc=0,t1acc=0;
        rng(i,0,NODES){
            Receive(i);
            ll Li=GetLL(i);
            ll Ri=GetLL(i);
            ll newt0acc=GetLL(i);
            ll newt1acc=GetLL(i);
            if (Li>Ri) continue;
            t0acc+=newt0acc;
            t1acc+=newt1acc;
            events.emplace_back(t0acc,0,Ri+1);
            events.emplace_back(t1acc,1,Ri+1);
        }
        ll en=events.size();

        sort(events.begin(),events.end());

        VI stamp(en);
        VI which(en);
        VI index(en);
        rng(i,0,en){
            tie(stamp[i],which[i],index[i])=events[i];
            //cerr<<stamp[i]<<","<<which[i]<<","<<index[i]<<endl;
        }

        VI prevo(en);
        rng(i,0,en){
            prevo[i]=(i==0)?(-1):(which[i]==which[i-1])?prevo[i-1]:(i-1);
        }

        rng(i,0,NODES){
            ll L,R;tie(L,R)=get_interval(NODES,i,en);
            L=max(2LL,L);
            //cerr<<"assign:"<<i<<","<<L<<","<<R<<endl;
            ll startwhich=(L<en)?which[L]:(-1);
            ll startindex=(L<en)?index[L]:(-1);
            ll startstamp=(L<en)?stamp[L]:(-1);
            ll pretid=(L>=en)?(-1):(prevo[L]<0)?0:index[prevo[L]];
            ll prestamp=(L>=en)?(-1):(prevo[L]<0)?0:stamp[prevo[L]];
            ll endwhich=(R==en-1)?-1:which[R+1];
            ll endindex=(R==en-1)?-1:index[R+1];
            ll endstamp=(R==en-1)?-1:stamp[R+1];
            PutLL(i,startwhich);
            PutLL(i,startindex);
            PutLL(i,startstamp);
            PutLL(i,pretid);
            PutLL(i,prestamp);
            PutLL(i,endwhich);
            PutLL(i,endindex);
            PutLL(i,endstamp);
            Send(i);
        }
    }

    Receive(0);
    ll startp=GetLL(0);
    ll starttid=GetLL(0);
    ll startstmp=GetLL(0);
    ll pretid=GetLL(0);
    ll prestmp=GetLL(0);
    ll endp=GetLL(0);
    ll endtid=GetLL(0);
    ll endstamp=GetLL(0);
    auto endkey=make_pair(endstamp,endp);
    ll crtp=startp;
    //cerr<<"From master:"<<startp<<","<<starttid<<","<<startstmp<<","<<pretid<<","<<prestmp<<","<<endp<<","<<endtid<<endl;
    if (startp>=0){
        tids[crtp].push_back(starttid);
        stmps[crtp].push_back(startstmp);
        appendPosition(crtp,starttid);
        tmpn[crtp]=1;

        tids[1-crtp].push_back(pretid);
        stmps[1-crtp].push_back(prestmp);
        appendPosition(1-crtp,pretid);
        tmpn[1-crtp]=1;

        while (1){
            if (tids[crtp].back()==N||getkey(crtp,tmpn[crtp]-1)<getkey(1-crtp,tmpn[1-crtp]-1)) break;
            fetchNextSegment(1-crtp);
        }

        while(1){
            ll crttid=tids[crtp].back();
            if (crttid==N||getkey(crtp,tmpn[crtp]-1)>=endkey) break;
            if (dangerdist(crtp)) ++ans[crtp];
            fetchNextSegment(crtp);
            crtp=(getkey(0,tmpn[0]-1)<getkey(1,tmpn[1]-1))?0:1;
        }
    }
    PutLL(0,ans[0]);
    PutLL(0,ans[1]);
    Send(0);

    if (ME==0){
        ll ansp0=0,ansp1=0;
        rng(i,0,NODES){
            Receive(i);
            ansp0+=GetLL(i);
            ansp1+=GetLL(i);
        }
        cout<<ansp0<<' '<<ansp1<<endl;
    }
    return 0;
}
