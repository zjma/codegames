
void kosaraju_dfs(const VI &v2e0, const VI &e2n, const VI &e2t, const ll v_cur, VI &visited, stack<ll> &stk){
    visited[v_cur]=1;
    for(ll e=v2e0[v_cur];e>=0;e=e2n[e]){
        ll v_nxt=e2t[e];
        if (!visited[v_nxt])
            kosaraju_dfs(v2e0,e2n,e2t,v_nxt,visited,stk);
    }
    stk.push(v_cur);
}

void kosaraju_assign(const VI &v2re0, const VI &re2n, const VI& re2t, const ll v_cur, const ll cid, VI &v2c){
    v2c[v_cur]=cid;
    for(ll e=v2re0[v_cur];e>=0;e=re2n[e]){
        ll v_nxt=re2t[e];
        if (v2c[v_nxt]<0)
            kosaraju_assign(v2re0, re2n, re2t, v_nxt, cid, v2c);
    }
}

/*
param n     Vertex count.
param v2e0  First edge of a vertex.
param e2f   Source vertex of an edge.
param e2t   Destination vertext of an edge.
param e2n   Next edge of an edge.
param cn    (Output) Component count.
param v2c   (Output) Assigned component ID of a vertex.
*/
void kosaraju(const ll n, const VI &v2e0, const VI &e2f, const VI &e2t, const VI &e2n, ll &cn, VI &v2c){
    //DFS1
    VI visited(n,0);
    stack<ll> stk;
    rng(i,0,n)
        if (!visited[i])
            kosaraju_dfs(v2e0,e2n,e2t,i,visited,stk);

    //Reversed graph.
    VI v2re0(n,-1),re2n,re2t;
    ll en=e2f.size();
    rng(i,0,en){
        re2t.push_back(e2f[i]);
        re2n.push_back(v2re0[e2t[i]]);
        v2re0[e2t[i]]=re2t.size()-1;
    }

    //Assign.
    v2c.resize(n);
    v2c.assign(n,-1);
    cn=0;
    while(!stk.empty()){
        ll v_cur=stk.top();
        if (v2c[v_cur]<0){
            kosaraju_assign(v2re0,re2n,re2t,v_cur,cn,v2c);
            cn++;
        }
        stk.pop();
    }
}
