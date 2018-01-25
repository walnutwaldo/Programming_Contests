struct DSU {

    int *parent, *sizeRooted;

    DSU(int sz) {
        parent = new int[sz], sizeRooted = new int[sz];
        F0R(i, sz) parent[i] = i, sizeRooted[i] = 1;
    }

    int root(int a) {
        if(parent[a] == a) return a;
        return (parent[a] = root(parent[a]));
    }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        if(sizeRooted[ra] > sizeRooted[rb]) swap(ra, rb);
        parent[ra] = rb;
        sizeRooted[rb] += sizeRooted[ra];
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

    int componentSize(int a) {
        return sizeRooted[root(a)];
    }

};
