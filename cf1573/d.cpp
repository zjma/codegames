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

bool solve(VI&A, VI&ans){
    ans.clear();
    ll n=A.size();
    VI segval;
    VI seglen;
    rng(i,0,n){
        if(i==0||A[i]!=A[i-1]){
            segval.push_back(A[i]);
            seglen.push_back(1);
        }else{
            seglen[seglen.size()-1]++;
        }
    }
    ll segn=seglen.size();
    VI segnxt(segn,-1);
    VI segpre(segn,-1);
    rng(i,0,segn-1){
        segnxt[i]=i+1;
        segpre[i+1]=i;
    }

    ll cur=0;
    ll prevCount=0;
    while(cur>=0){
        if (segval[cur]==1){
            if (seglen[cur]%2==1){
                ll nxt=segnxt[cur];
                ll nxt2=(nxt>=0)?segnxt[nxt]:-1;
                if (nxt<0||nxt2<0) return false;
                assert(segval[nxt]==0);
                assert(segval[nxt2]==1);
                if (seglen[nxt]%2==0){
                    rng(i,0,seglen[nxt]/2){
                        ans.push_back(prevCount+seglen[cur]+i*2);
                    }
                    seglen[cur]+=seglen[nxt]+seglen[nxt2];
                    seglen[nxt]=0;
                    seglen[nxt2]=0;
                    ll nxt3=segnxt[nxt2];
                    segnxt[cur]=nxt3;
                    segpre[nxt3]=cur;
                    //no need to update cur.
                }
                else //if (seglen[nxt]%2==1)
                {
                    rng(i,0,seglen[nxt]/2){
                        ans.push_back(prevCount+seglen[cur]+i*2);
                    }
                    //now we have an 1...101
                    rng(i,0,(seglen[cur]+seglen[nxt])/2){
                        ans.push_back(prevCount+seglen[cur]+seglen[nxt]-1-i*2);
                    }
                    segval[cur]=0;
                    if (seglen[nxt2]==1){
                        segval[nxt2]=0;
                    }else{
                        seglen[nxt]++;
                        seglen[nxt2]--;
                    }
                    prevCount+=seglen[cur]+seglen[nxt];
                    cur=nxt2;
                }
            }
            else// if (cur->c%2==0)
            {
                if (segpre[cur]>=0){
                    rng(i,0,seglen[cur]/2){
                        ans.push_back(prevCount+i*2);
                    }
                    segval[cur]=0;
                    prevCount+=seglen[cur];
                    cur=segnxt[cur];
                }else if(segnxt[cur]>=0){
                    rng(i,0,seglen[cur]/2){
                        ans.push_back(prevCount+seglen[cur]-1-i*2);
                    }
                    segval[cur]=0;
                    prevCount+=seglen[cur];
                    cur=segnxt[cur];
                }else{
                    return false;
                }
            }
        }
        else //if (cur->v==0)
        {
            prevCount+=seglen[cur];
            cur=segnxt[cur];
        }
    }
    return true;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        VI A(n);
        rng(i,0,n){
            A[i]=scan();
        }
        VI ans;
        if (solve(A,ans)){
            printf("YES\n");
            ll an=ans.size();
            printf("%lld\n",an);
            rng(i,0,an-1){
                printf("%lld ",ans[i]);
            }
            printf("%lld\n",ans[an-1]);
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
