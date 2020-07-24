/* LCA initialization.
param n     Tree node count. Nodes are numbered 0..(n-1).
param lc    lc[i]: left child of node i.
param rc    rc[i]: right child of node i.
param root  Tree root node.
param path  An empty vector.
param dep   (output) dep[i]: depth of node i.
param anc   (output) anc[i][j]: (2**j)-th nearest ancestor of node i.
*/
void lcaInit(ll n, VI &lc, VI &rc, ll root, VI& path, VI &dep, VVI &anc){
    if (root<0||root>=n) return;
    ll pn=path.size();
    dep[root]=pn;
    ll pd=1;
    while(pd<=pn){
        anc[root].push_back(path[pn-pd]);
        pd*=2;
    }
    path.push_back(root);
    lcaInit(n,lc,rc,lc[root],path,dep,anc);
    lcaInit(n,lc,rc,rc[root],path,dep,anc);
    path.pop_back();
}

/* LCA query handling.
param n     Same as above.
param dep   Same as above.
param anc   Same as above.
param i0    First node in query.
param i1    Second node in query.
returns     The LCA.
*/
ll lcaQuery(ll n, VI &dep, VVI &anc, ll i0, ll i1){
    if (dep[i0]>dep[i1]) swap(i0,i1);
    while(dep[i0]<dep[i1]) i1=anc[i1][log2(dep[i1]-dep[i0])];
    while(i0!=i1){
        ll aidx=0, an=anc[i0].size();
        while(aidx<an&&anc[i0][aidx]!=anc[i1][aidx]) aidx++;
        aidx=max(aidx-1,0LL);
        i0=anc[i0][aidx];
        i1=anc[i1][aidx];
    }
    return i0;
}
