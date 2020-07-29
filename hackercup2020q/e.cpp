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

struct SegTree {
    ll sl;
    ll sr;
    ll val;
    ll base;
    SegTree *cl;
    SegTree *cr;
};

SegTree *segtree_new(ll sl, ll sr, ll bv){
    SegTree *result=new SegTree();
    result->sl=sl;
    result->sr=sr;
    result->val=result->base=bv;
    result->cl=result->cr=NULL;
    return result;
}

bool segtree_trysplit(SegTree *root){
    if (root==NULL||root->sl==root->sr||root->cl) return false;
    ll sep=(root->sl+root->sr)/2;
    root->cl=segtree_new(root->sl,sep,root->base);
    root->cr=segtree_new(sep+1,root->sr,root->base);
    return true;
}

ll segtree_get(SegTree *root, ll ql, ll qr){
    if (root==NULL||ql>root->sr||qr<root->sl||ql>qr) return INF;
    if (ql<=root->sl&&qr>=root->sr) return root->val;
    segtree_trysplit(root);
    return min(segtree_get(root->cl,ql,qr),segtree_get(root->cr,ql,qr));
}

void segtree_update(SegTree *root, ll pos, ll newval){
    if (root==NULL||pos<root->sl||pos>root->sr) return;
    segtree_trysplit(root);
    segtree_update(root->cl,pos,newval);
    segtree_update(root->cr,pos,newval);
    root->val=min(root->val,newval);
}

void segtree_dump(SegTree *root){
    if (root==NULL) return;
    cerr<<"["<<root->sl<<","<<root->sr<<"] : "<<root->val<<endl;
    segtree_dump(root->cl);
    segtree_dump(root->cr);
}

void segtree_free(SegTree *root){
    if (root==NULL) return;
    segtree_free(root->cl);
    segtree_free(root->cr);
    delete root;
}

bool findPath(VVI &rootless, ll current, ll parent, ll dest, VI &path){
    if (current<0) return false;
    path.push_back(current);
    if (current==dest) return true;
    for (ll child : rootless[current]){
        if (child==parent) continue;
        if (findPath(rootless,child,current,dest,path)) return true;
    }
    path.pop_back();
    return false;
}

void traverse(VVI &rootless, ll current, ll parent, ll cur_rel_depth, ll ignored1, ll ignored2, VI &nodes, VI &rel_depths){
    if (current<0) return;
    nodes.push_back(current);
    rel_depths.push_back(cur_rel_depth);
    for (ll child : rootless[current]){
        if (child==ignored1||child==ignored2||child==parent) continue;
        traverse(rootless,child,current,cur_rel_depth+1,ignored1,ignored2,nodes,rel_depths);
    }
}

string dumpVI(VI &arr){
    string result="";
    for (ll x:arr) result+=to_string(x)+",";
    return result;
}

ll solve(ll volume, VVI &rootless, VI &cost, ll src, ll dst){
    VI backbone;
    findPath(rootless,src,-1,dst,backbone);
    ll blen=backbone.size();
    ll n=cost.size();
    VI cache(n);
    SegTree *root=segtree_new(1,blen-1,INF);
    cache[src]=0;
    segtree_update(root,blen-1,0);

    rng(i,1,blen-1){
        ll bbnode_depth=blen-1-i;
        //Traverse subtree for current backbone node.
        VI nodes;
        VI rel_depths;
        traverse(rootless,backbone[i],-1,0,backbone[i-1],backbone[i+1],nodes,rel_depths);
        ll len=nodes.size();
        rng(j,0,len){
            if (cost[nodes[j]]==0) continue;
            cache[nodes[j]]=segtree_get(root,bbnode_depth+1,bbnode_depth+volume-rel_depths[j])+cost[nodes[j]];
        }
        rng(j,0,len){
            if (cost[nodes[j]]==0) continue;
            segtree_update(root,bbnode_depth+rel_depths[j],cache[nodes[j]]);
        }
    }
    ll ans=segtree_get(root,1,volume);
    if (ans>=INF) ans=-1;
    segtree_free(root);
    return ans;
}

int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan(),m=scan(),a=scan()-1,b=scan()-1;
        VI c(n);
        VVI rootless(n);
        rng(i,0,n){
            ll p=scan()-1;
            if (p>=0){
                rootless[i].push_back(p);
                rootless[p].push_back(i);
            }
            c[i]=scan();
        }
        ll ans=solve(m,rootless,c,a,b);
        cout<<"Case #"<<(ti+1)<<": "<<ans<<endl;
    }
    return 0;
}
