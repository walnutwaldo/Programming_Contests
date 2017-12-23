struct RMQ {

    int n;
    ll* arr;
    vector<vi> sparse;

    RMQ(int sz) {
        n = sz;
        arr = new ll[n];
        memset(arr, 0, n * sizeof(ll));
    }

    void update(int i, ll v) {
        arr[i] += v;
    }

    void genRMQ() {
        F0R(i, n) sparse.PB(vi());
        F0R(i, n) sparse[i].PB(arr[i]);
        FOR(i, 1, log2(n)) F0R(j, n) {
            if(j + (1 << i) > n) sparse[j].PB(sparse[j][i - 1]);
            else sparse[j].PB(max(sparse[j][i - 1], sparse[j + (1 << (i - 1))][i - 1]));
        }
    }

    ll query(int l, int r) {
        int s = (int)ceil(log2(r - l + 1)) - 1;
        return max(sparse[l][s], sparse[r + 1 - (1 << s)][s]);
    }
};
