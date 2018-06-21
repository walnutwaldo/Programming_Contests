struct DSU {

    int *parent, *rank;

    DSU(int sz) {
        parent = new int[sz], rank = new int[sz];
        F0R(i, sz) parent[i] = i, rank[i] = 0;
    }

    int root(int a) { (parent[a] == a)? a : (parent[a] = root(parent[a])); }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        if(rank[ra] > rank[rb]) swap(ra, rb);
        parent[ra] = rb;
        if(rank[ra] == rank[rb]) rank[rb]++;
    }

    bool connected(int a, int b) { return root(a) == root(b); }

};
