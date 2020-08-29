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
void dumpVI(VI &arr){
    ll n=arr.size();
    rng(i,0,n-1){
        cerr<<arr[i]<<",";
    }
    cerr<<arr[n-1]<<endl;
}

void dfs(ll x, VI &psum, vector<string> &words){
    if (psum.back()==x){
        ll pn=psum.size()-1;
        rng(w,1,pn){
            rng(i,0,pn+1-w){
                if (x%(psum[i+w]-psum[i])==0) return;
            }
        }
        string obj;
        rng(i,0,pn){
            obj.push_back(psum[i+1]-psum[i]+48);
        }
        words.push_back(obj);
    }else{
        rng(d,1,min(x-psum.back(),9ll)+1){
            psum.push_back(psum.back()+d);
            dfs(x,psum,words);
            psum.pop_back();
        }
    }
}

void getWords(ll x, vector<string> &words){
    VI psum(1,0);
    dfs(x,psum,words);
}
void testGetWords(){
    vector<string> words;
    getWords(19,words);
    cerr<<words.size()<<endl;
}
ll newnode(VVI &link, VI &wordflag, VI &parent, VI &srcex, ll vi_parent, ll ex_src){
    link.emplace_back(VI(9,-1));
    wordflag.push_back(0);
    parent.push_back(vi_parent);
    srcex.push_back(ex_src);
    return link.size()-1;
}
void build(const vector<string> &words, VVI &link, VI &wordflag, VI &parent, VI &srcex, VI &suflink){
    link.clear();wordflag.clear();parent.clear();srcex.clear();suflink.clear();

    ll root=newnode(link,wordflag,parent,srcex,-1,-1);
    for (auto word:words){
        ll curNode=root;
        for (char const &c:word){
            ll ex=c-49;
            if (link[curNode][ex]<0){
                link[curNode][ex]=newnode(link,wordflag,parent,srcex,curNode,ex);
            }
            curNode=link[curNode][ex];
        }
        wordflag[curNode]=1;
    }

    suflink.resize(link.size(),-1);
    queue<ll> q;
    q.push(0LL);
    while(!q.empty()){
        ll vi_cur=q.front();
        q.pop();
        //get suflink for current.
        if (vi_cur==0){
            suflink[vi_cur]=-1;
        }else{
            ll vi_tmp=suflink[parent[vi_cur]];
            ll ex_tmp=srcex[vi_cur];
            while(vi_tmp>=0&&link[vi_tmp][ex_tmp]<0) vi_tmp=suflink[vi_tmp];
            suflink[vi_cur]=(vi_tmp<0)?0:link[vi_tmp][ex_tmp];
        }

        //explore.
        rng(ex,0,9){
            ll vi_nxt=link[vi_cur][ex];
            if (vi_nxt>=0){
                q.push(vi_nxt);
            }
        }
    }
}

ll onestep(VVI &link, VI &suflink, ll vi, ll ex){
    if (link[vi][ex]<0){
        link[vi][ex]=(vi==0)?0:onestep(link,suflink,suflink[vi],ex);
    }
    return link[vi][ex];
}
int main()
{
    string s;cin>>s;
    ll x;cin>>x;
    vector<string> words;
    getWords(x,words);
    VVI link;
    VI wordflag;
    VI parent;
    VI srcex;
    VI suflink;
    build(words,link,wordflag,parent,srcex,suflink);
    ll sn=s.size();
    ll vn=link.size();
    VVI dp(2,VI(vn,INF));dp[0][0]=0;
    rng(si,0,sn){
        ll ii=si%2;
        ll ii_next=1-ii;
        ll ex=s[si]-49;
        dp[ii_next].assign(vn,INF);
        rng(vi,0,vn){
            if (wordflag[vi]) continue;
            ll vi_keep=onestep(link,suflink,vi,ex);
            dp[ii_next][vi_keep]=min(dp[ii_next][vi_keep],dp[ii][vi]);
            dp[ii_next][vi]=min(dp[ii_next][vi],dp[ii][vi]+1);
        }
    }

    ll ii=sn%2;
    ll ans=INF; rng(vi,0,vn){
        if (!wordflag[vi]) ans=min(ans,dp[ii][vi]);
    }
    cout<<ans<<endl;
    return 0;
}
