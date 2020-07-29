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
