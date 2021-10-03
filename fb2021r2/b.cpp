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
#include <numeric>
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

inline ll log2floor(ll x){
    assert(x>=1);
    return 63LL-__builtin_clzll(x);
}
inline ll log2ceil(ll x){
    assert(x>=1);
    return (x==1)?0LL:(64LL-__builtin_clzll(x-1));
}

void dumpVI(const VI &a){
    ll n=a.size();
    rng(i,0,n){
        cerr<<"v("<<i<<")="<<a[i]<<endl;
    }
}

template <typename T>
struct RMQOracle {
    ll n;
    vector<vector<T>> f0;
    vector<vector<T>> f1;
    void init(const vector<T> &a){
        n=a.size();
        ll K=log2floor(n);
        f0.resize(n);
        f1.resize(n);
        rng(i,0,n){f0[i].resize(K+1);f1[i].resize(K+1);}
        rng(i,0,n) f0[i][0]=f1[i][0]=a[i];
        rng(k,1,K+1){
            ll half=1<<(k-1);
            rng(i,0,n){
                if (i+half*2<=n) f0[i][k]=min(f0[i][k-1],f0[i+half][k-1]);
                if (i-half*2+1>=0) f1[i][k]=min(f1[i][k-1],f1[i-half][k-1]);
            }
        }
    }
    T get(ll ql, ll qr){
        assert(0<=ql);assert(ql<=qr);assert(qr<n);
        ll k=log2floor(qr-ql+1);
        return min(f0[ql][k],f1[qr][k]);
    }
};

struct UndirectedGraph {
    ll nodeCount;
    VVI adjsOf;
    void init(ll _nodeCount){
        nodeCount=_nodeCount;
        adjsOf=vector<VI>(nodeCount);
    }
    void addEdge(ll a, ll b){
        adjsOf[a].push_back(b);
        adjsOf[b].push_back(a);
    }
};

struct RootedTree {
    ll nodeCount;
    VVI childrenOf;
    VI parentOf;
    VI depthOf;
    void _explore(const UndirectedGraph &graph, ll curDepth, ll curNode, ll preNode){
        parentOf[curNode]=preNode;
        depthOf[curNode]=curDepth;
        for(ll adj:graph.adjsOf[curNode]){
            if (adj==preNode) continue;
            childrenOf[curNode].push_back(adj);
            _explore(graph,curDepth+1,adj,curNode);
        }
    }
    void init(const UndirectedGraph &g){
        nodeCount=g.nodeCount;
        childrenOf.resize(nodeCount);
        parentOf.resize(nodeCount);
        depthOf.resize(nodeCount);
        _explore(g,0,0,-1);
    }
};

struct LcaOracle {
    RMQOracle<pair<ll,ll>> ro;//<depth,nodeId>
    VI lastVisitTimeOf;
    void _traverse(const RootedTree &tree, ll curNode, ll curDepth, VI &trace, VI &depthOf){
        if (curNode<0||curNode>tree.nodeCount-1) return;
        trace.push_back(curNode);
        depthOf[curNode]=curDepth;
        for(auto nxtNode:tree.childrenOf[curNode]){
            _traverse(tree,nxtNode,curDepth+1,trace,depthOf);
            trace.emplace_back(curNode);
        }
    }
    void init(const RootedTree &tree){
        VI trace;
        VI depthOf(tree.nodeCount);
        _traverse(tree,0,0,trace,depthOf);
        vector<pair<ll,ll>> depNodePairs(trace.size());
        lastVisitTimeOf.assign(tree.nodeCount,-1);
        rng(i,0,trace.size()) {
            lastVisitTimeOf[trace[i]]=i;
            depNodePairs[i]=make_pair(tree.depthOf[trace[i]],trace[i]);
        }
        ro.init(depNodePairs);
    }
    ll query(ll a, ll b){
        ll ta=lastVisitTimeOf[a];
        ll tb=lastVisitTimeOf[b];
        auto [depth,node]=ro.get(min(ta,tb),max(ta,tb));
        return node;
    }
};

ll ansExplore(RootedTree&tree, map<ll,ll>&freq2lca, VI&freqOf, ll&ans, ll curNode) {
    ll curZ=tree.depthOf[freq2lca[freqOf[curNode]]];
    for(auto chd:tree.childrenOf[curNode]){
        curZ=min(curZ,ansExplore(tree,freq2lca,freqOf,ans,chd));
    }
    if (tree.depthOf[curNode]!=0&&curZ==tree.depthOf[curNode]) ans++;
    return curZ;
}


int main()
{
    ll tn=scan();
    rng(ti,0,tn){
        ll n=scan();
        UndirectedGraph graph;
        graph.init(n);
        rng(i,0,n-1){
            ll a=scan()-1;
            ll b=scan()-1;
            graph.addEdge(a,b);
        }
        RootedTree tree;
        tree.init(graph);

        map<ll,VI> freq2nodes;
        VI freqOf(n);
        rng(i,0,n){
            ll freq=scan();
            freqOf[i]=freq;
            freq2nodes[freq].push_back(i);
        }

        LcaOracle lo;
        lo.init(tree);

        map<ll,ll> freq2lca;
        for(auto &[freq,nodes]:freq2nodes){
            ll curLca=nodes[0];
            for(auto v:nodes) curLca=lo.query(curLca,v);
            freq2lca[freq]=curLca;
        }

        ll ans=0;
        ansExplore(tree,freq2lca,freqOf,ans,0);
        printf("Case #%lld: %lld\n",ti+1,ans);
    }
    return 0;
}
