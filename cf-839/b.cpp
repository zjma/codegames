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


int solve(int bigcount, int smallcount, VI &team)
{
    ll tinycount=0;
    ll n=team.size();

    rng(i,0,n){
        while (team[i]>=4&&bigcount>=1){
            team[i]-=4;
            --bigcount;
        }
    }

    bool no4p=true;
    rng(i,0,n){
        no4p=no4p&&(team[i]<=3);
    }

    if (no4p){
        rng(i,0,n){
            while (team[i]>=3&&bigcount>=1){
                team[i]-=3;
                --bigcount;
            }
        }

        bool no3p=true;
        rng(i,0,n){
            no3p=no3p&&(team[i]<=2);
        }

        if (no3p){
            rng(i,0,n){
                if (team[i]==2&&smallcount>=1){
                    team[i]=0;
                    --smallcount;
                }
            }

            if (smallcount==0){
                rng(i,0,n){
                    if (team[i]==2&&bigcount>=1){
                        team[i]=0;
                        --bigcount;
                        ++tinycount;
                    }
                }

                bool no2p=true;
                rng(i,0,n){
                    no2p=no2p&&(team[i]<=1);
                }

                if (no2p){
                    tinycount+=bigcount*2;
                    bigcount=0;
                }

                ll tmp=0;
                rng(i,0,n){
                    tmp+=team[i];
                }

                if (tmp<=tinycount) return 1;
                return 0;
            }else{
                ll tmp=0;
                rng(i,0,n){
                    assert(team[i]<=1);
                    tmp+=team[i];
                }
                return (tmp<=bigcount*2+smallcount+tinycount)?1:0;
            }
        }else{
            assert(bigcount==0);
            rng(i,0,n){
                smallcount-=(team[i]+1)/2;
                if (smallcount<0) return 0;
            }
            return 1;
        }
    }else{
        assert(bigcount==0);
        rng(i,0,n){
            smallcount-=(team[i]+1)/2;
            if (smallcount<0) return 0;
        }
        return 1;
    }
}

int main()
{
    ll n=scan();
    ll k=scan();
    VI a(k);
    rng(i,0,k){
        a[i]=scan();
    }

    if (solve(n,n*2,a)==1){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
    return 0;
}
