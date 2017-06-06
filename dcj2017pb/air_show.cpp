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

#define sqr(x) ((x)*(x))
#define makekey(stamp,which) (((stamp)<<1)|(which))

void midpoint(
    double x0, double y0, double z0,
    ll t0, ll t1,
    double x1, double y1, double z1,
    double &xm, double &ym, double &zm
    )
{
    ll tt=t0+t1;
    if (tt==0){
        xm=x1;
        ym=y1;
        zm=z1;
    }else{
        xm=(t0*x1+t1*x0)/tt;
        ym=(t0*y1+t1*y0)/tt;
        zm=(t0*z1+t1*z0)/tt;
    }
}

double distance2(double x0, double y0, double z0, double x1, double y1, double z1){
    return sqr(x0-x1)+sqr(y0-y1)+sqr(z0-z1);
}

void parsePosition(ll encoded, ll &x, ll &y, ll &z){
    x=(encoded&0xfffff0000000000)>>40;
    y=(encoded&0xfffff00000)>>20;
    z=encoded&0xfffff;
}

int main()
{
    NODES=NumberOfNodes();
    ME=MyNodeId();
    ll segn=GetNumSegments();
    ll safedis=GetSafeDistance();
    ll safedis2=sqr(safedis);
    VI segL(NODES);
    VI segR(NODES);
    rng(i,0,NODES){
        tie(segL[i],segR[i])=get_interval(NODES,i,segn-2);
    }
    if (segL[ME]<=segR[ME]){
        ll localtimeacc0=0;
        ll localtimeacc1=0;
        rng(i,segL[ME],segR[ME]+1){
            localtimeacc0+=GetTime(0,i+1);
            localtimeacc1+=GetTime(1,i+1);
        }
        PutLL(0,localtimeacc0);
        PutLL(0,localtimeacc1);
        Send(0);
    }

    if (ME==0){
        vector<tuple<ll,ll,ll>> events;//stamp,which,index
        ll timeacc0=GetTime(0,0);
        ll timeacc1=GetTime(1,0);
        events.emplace_back(timeacc0,0,1);
        events.emplace_back(timeacc1,1,1);
        rng(ni,0,NODES){
            if (segL[ni]>segR[ni]) continue;
            Receive(ni);
            timeacc0+=GetLL(ni);
            timeacc1+=GetLL(ni);
            events.emplace_back(timeacc0,0,segR[ni]+2);
            events.emplace_back(timeacc1,1,segR[ni]+2);
        }

        ll tottime0=timeacc0+GetTime(0,segn-1);
        ll tottime1=timeacc1+GetTime(1,segn-1);
        assert(tottime0==tottime1);

        sort(events.begin(),events.end());
        ll en=events.size();
        VI stamps(en);
        VI whichs(en);
        VI indexs(en);
        rng(ei,0,en){
            tie(stamps[ei],whichs[ei],indexs[ei])=events[ei];
        }
        VI mrmcp_eids(en);
        rng(ei,0,en){
            mrmcp_eids[ei]=(ei==0)?(-1):(whichs[ei]==whichs[ei-1])?mrmcp_eids[ei-1]:(ei-1);
        }

        VI eegL(NODES);
        VI eegR(NODES);
        rng(ni,0,NODES){
            tie(eegL[ni],eegR[ni])=get_interval(NODES,ni,en);
        }
        rng(ni,0,NODES){
            if (eegL[ni]>eegR[ni]){
                PutLL(ni,-1);
                Send(ni);
            }else{
                ll focused_eid=eegL[ni];
                PutLL(ni,0);
                // Send starting point.
                PutLL(ni,stamps[focused_eid]);
                PutLL(ni,whichs[focused_eid]);
                PutLL(ni,indexs[focused_eid]);

                // Send most recently met counter-point.
                if (mrmcp_eids[focused_eid]<0){
                    PutLL(ni,0);
                    PutLL(ni,1-whichs[focused_eid]);
                    PutLL(ni,0);
                }else{
                    PutLL(ni,stamps[mrmcp_eids[focused_eid]]);
                    PutLL(ni,whichs[mrmcp_eids[focused_eid]]);
                    PutLL(ni,indexs[mrmcp_eids[focused_eid]]);
                }

                // Send exclusively ending point.
                if (ni==NODES-1||eegL[ni+1]>eegR[ni+1]){
                    PutLL(ni,tottime0);
                    PutLL(ni,0);
                    PutLL(ni,segn);
                }else{
                    PutLL(ni,stamps[eegL[ni+1]]);
                    PutLL(ni,whichs[eegL[ni+1]]);
                    PutLL(ni,indexs[eegL[ni+1]]);
                }
                Send(ni);
            }
        }
    }

    Receive(0);
    ll job=GetLL(0);
    if (job>=0){
        ll startstamp=GetLL(0);
        ll startwhich=GetLL(0);
        ll startindex=GetLL(0);
        ll mrmcpstamp=GetLL(0);
        ll mrmcpwhich=GetLL(0);
        ll mrmcpindex=GetLL(0);
        ll exendstamp=GetLL(0);
        ll exendwhich=GetLL(0);
        ll exendindex=GetLL(0);
        auto startkey=makekey(startstamp,startwhich);
        auto endkey=makekey(exendstamp,exendwhich);
        assert(startkey<endkey);
        assert(startwhich!=mrmcpwhich);
        ll crtwhich=startwhich;
        VI posx(2);
        VI posx_old(2);
        VI posy(2);
        VI posy_old(2);
        VI posz(2);
        VI posz_old(2);
        VI index(2);
        VI index_old(2);
        VI stamp(2);
        VI stamp_old(2);
        VI ans(2);

        // Init my queue.
        ll dp=GetPosition(crtwhich,startindex);
        parsePosition(dp,posx[crtwhich],posy[crtwhich],posz[crtwhich]);
        stamp[crtwhich]=startstamp;
        index[crtwhich]=startindex;

        // Init enemy queue.
        dp=GetPosition(1-crtwhich,mrmcpindex);
        parsePosition(dp,posx_old[1-crtwhich],posy_old[1-crtwhich],posz_old[1-crtwhich]);
        stamp_old[1-crtwhich]=mrmcpstamp;
        index_old[1-crtwhich]=mrmcpindex;

        // ll loopgtr=0;
        while(1){
            // assert(loopgtr++<5000000);
            index[1-crtwhich]=index_old[1-crtwhich]+1;
            stamp[1-crtwhich]=stamp_old[1-crtwhich]+GetTime(1-crtwhich,index_old[1-crtwhich]);
            ll dp=GetPosition(1-crtwhich,index[1-crtwhich]);
            parsePosition(dp,posx[1-crtwhich],posy[1-crtwhich],posz[1-crtwhich]);
            auto newkey=makekey(stamp[1-crtwhich],1-crtwhich);
            if (newkey>startkey) break;
            stamp_old[1-crtwhich]=stamp[1-crtwhich];
            index_old[1-crtwhich]=index[1-crtwhich];
            posx_old[1-crtwhich]=posx[1-crtwhich];
            posy_old[1-crtwhich]=posy[1-crtwhich];
            posz_old[1-crtwhich]=posz[1-crtwhich];
        }

        // main local test.
        // ll loopctr=0;
        while(1){
            // assert(loopctr++<5000000);
            auto mrmkey=makekey(stamp_old[1-crtwhich],1-crtwhich);
            auto crtkey=makekey(stamp[crtwhich],crtwhich);
            auto futkey=makekey(stamp[1-crtwhich],1-crtwhich);
            assert(mrmkey<crtkey);
            assert(crtkey<futkey);
            if (crtkey>=endkey) break;

            // Test danger.
            __int128 x0=posx_old[1-crtwhich];
            __int128 y0=posy_old[1-crtwhich];
            __int128 z0=posz_old[1-crtwhich];
            __int128 x1=posx[1-crtwhich];
            __int128 y1=posy[1-crtwhich];
            __int128 z1=posz[1-crtwhich];
            __int128 x=posx[crtwhich];
            __int128 y=posy[crtwhich];
            __int128 z=posz[crtwhich];
            __int128 t0=stamp[crtwhich]-stamp_old[1-crtwhich];
            __int128 t1=stamp[1-crtwhich]-stamp[crtwhich];
            __int128 tt=t0+t1;
            __int128 tdx=t0*x1+t1*x0-tt*x;
            __int128 tdy=t0*y1+t1*y0-tt*y;
            __int128 tdz=t0*z1+t1*z0-tt*z;
            __int128 sd2=safedis2;
            if (sqr(tdx)+sqr(tdy)+sqr(tdz)<sqr(tt)*sd2) ++ans[crtwhich];

            //get next timepoint on route crtwhich.
            stamp_old[crtwhich]=stamp[crtwhich];
            index_old[crtwhich]=index[crtwhich];
            posx_old[crtwhich]=posx[crtwhich];
            posy_old[crtwhich]=posy[crtwhich];
            posz_old[crtwhich]=posz[crtwhich];
            ll dt=GetTime(crtwhich,index_old[crtwhich]);
            stamp[crtwhich]+=dt;
            index[crtwhich]++;
            ll dp=GetPosition(crtwhich,index[crtwhich]);
            parsePosition(dp,posx[crtwhich],posy[crtwhich],posz[crtwhich]);

            // Choose next point.
            auto newkey=makekey(stamp[crtwhich],crtwhich);
            crtwhich=(newkey<futkey)?crtwhich:(1-crtwhich);
        }
        PutLL(0,0);
        PutLL(0,ans[0]);
        PutLL(0,ans[1]);
        Send(0);
    }else{
        PutLL(0,-1);
        Send(0);
    }

    if (ME==0){
        ll ans0=0;
        ll ans1=0;
        rng(i,0,NODES){
            Receive(i);
            ll smr=GetLL(i);
            if (smr<0) continue;
            ans0+=GetLL(i);
            ans1+=GetLL(i);
        }
        cout<<ans0<<" "<<ans1<<endl;
    }
    return 0;
}
