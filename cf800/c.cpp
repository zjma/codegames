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
const DOUBLE EPS=1e-6;
const DOUBLE PI = atan(1) * 4;
const ll M = 1000000007;

#define sqr(x) ((x)*(x))
//for-loop shortcut
#define rng(i,begin,end) for (ll i=begin;i<end;++i)


//scanf shortcuts
void scanll(ll &x) {ll r;scanf("%lld",&r);x=r;}
void scanstr(char *buf){scanf("%s",buf);}

ll mod(ll x, ll m) { return ((x%m) + m) % m; }

ll gcd(ll x, ll y){
    if (y==0) return x;
    return gcd(y, x%y);
}

void eucext(ll a, ll b, ll &g, ll &k1, ll &k2){
    if (b==0){
        g=a;
        k1=1;
        k2=0;
        return;
    }
    ll subk1,subk2,subg;
    ll q=a/b;
    eucext(b, a-q*b, subg, subk1, subk2);
    g=subg;
    k1=subk2;
    k2=subk1-subk2*q;
}

//return x so that ax=b mod m, assuming gcd(a,m)|gcd(b,m)
ll getMultiplier(ll a, ll b, ll m){
    ll g,k1,k2;
    eucext(a,m,g,k1,k2);
    k1=mod(k1,m);
    assert(b%g==0);
    return k1*b/g%m;
}



int main()
{
    ll dn,m;scanll(dn);scanll(m);
    vector<bool> disabled(m);
    rng(i,0,dn){
        ll x;scanll(x);
        disabled[x]=true;
    }

    vector<vector<ll>> d2allows(m+1);
    rng(i,0,m){
        if (disabled[i]) continue;
        ll d=gcd(i,m);
        d2allows[d].push_back(i);
    }

    VI vi2tag;
    VI vi2w;
    rng(d,1,m+1){
        ll tmp=d2allows[d].size();
        if (tmp>0){
            vi2tag.push_back(d);
            vi2w.push_back(tmp);
        }
    }
    ll vn=vi2tag.size();

    vector<vector<bool>> mep(vn,vector<bool>(vn));
    rng(vi,0,vn){
        rng(vj,0,vn){
            if (vi2tag[vj]>vi2tag[vi]&&vi2tag[vj]%vi2tag[vi]==0){
                mep[vi][vj]=true;
            }
        }
    }

    VI vi2ans(vn);
    VI vi2ansp(vn);
    vi2ans[0]=vi2w[0];
    vi2ansp[0]=-1;
    rng(vi,0,vn){
        rng(vj,0,vn){
            if (mep[vi][vj]){
                ll cand=vi2ans[vi]+vi2w[vj];
                if (cand>vi2ans[vj]){
                    vi2ans[vj]=cand;
                    vi2ansp[vj]=vi;
                }
            }
        }
    }

    ll ansi=0;
    rng(i,0,vn){
        if (vi2ans[i]>vi2ans[ansi]) ansi=i;
    }
    cout<<vi2ans[ansi]<<endl;
    VI pplist_rev;
    while(ansi>=0){
        ll tag=vi2tag[ansi];
        for (auto e:d2allows[tag]){
            pplist_rev.push_back(e);
        }
        ansi=vi2ansp[ansi];
    }
    ll an=pplist_rev.size();
    VI ansseq;
    rng(fi,0,an){
        ll i=an-1-fi;
        ll pp=pplist_rev[i];
        ll pplast=(fi==0)?-1:pplist_rev[i+1];
        ansseq.push_back((pplast==-1)?pp:getMultiplier(pplast,pp,m));
    }
    rng(i,0,an-1){
        cout<<ansseq[i]<<' ';
    }cout<<ansseq[an-1]<<endl;
    return 0;
}
