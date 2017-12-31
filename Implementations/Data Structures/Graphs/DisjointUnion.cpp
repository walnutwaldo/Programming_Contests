struct DSU {

    int *parent;

    DSU(int sz) {
        parent = new int[sz];
        F0R(i, sz) parent[i] = i;
    }

    int root(int a) {
        if(parent[a] == a) return a;
        return (parent[a] = root(parent[a]));
    }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        parent[ra] = rb;
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

};
