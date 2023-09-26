int n, ar[MAX];
vector<int> st[4*MAX];

inline void build(int node, int l, int r){
    if(l == r){
        st[node].pb(ar[l]);
    }
    else{
        int mid = (l+r)>>1;
        build(2*node,l,mid);
        build(2*node+1,mid+1,r);
        merge( all(st[2*node]), all(st[2*node+1]), back_inserter(st[node]) );
    }
}

inline int qry(int node, int l, int r, int x, int y){
    if(r < x or l > y) return 0;
    if(x <= l and r <= y){
        int v = upper_bound(all(st[node]), x-1)-st[node].begin();
        return v;
    }
    else{
        int mid = (l+r)>>1;
        return (qry(2*node,l,mid,x,y)+qry(2*node+1,mid+1,r,x,y));
    }
}
