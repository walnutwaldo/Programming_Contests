struct DSU {

    int *parent, *numNodes;

    DSU(int sz) {
        parent = new int[sz];
        numNodes = new int[sz];
        F0R(i, sz) parent[i] = i, numNodes[i] = 1;
    }

    int root(int a) {
        if(parent[a] == a) return a;
        return (parent[a] = root(parent[a]));
    }

    void join(int a, int b) {
        int ra = root(a), rb = root(b);
        if(ra == rb) return;
        if(numNodes[ra] > numNodes[rb]) swap(ra, rb);
        parent[ra] = rb;
        numNodes[rb] += numNodes[ra];
    }

    bool connected(int a, int b) {
        return root(a) == root(b);
    }

};
