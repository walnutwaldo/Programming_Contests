struct BIT {

    int sz;
    ll *tree;

    BIT(int sz) {
        this->sz = sz;
        tree = new ll[sz + 1];
        memset(tree, 0, (sz + 1) * sizeof(ll));
    }

    void update(int idx, ll v) {
        for(idx++; idx <= sz; idx += (idx & -idx)) tree[idx] += v;
    }

    ll query(int idx) {
        ll total = 0;
        for(idx++; idx > 0; idx -= (idx & -idx)) total += tree[idx];
        return total;
    }

    ll queryRangle(int lo, int hi) {
        return query(hi) - query(lo - 1);
    }

    ll querySingle(int idx) {
        ll total = tree[++idx];
        int z = idx - (idx & -idx);
        for(idx--; idx > z; idx -= (idx & -idx)) total -= tree[idx];
        return total;
    }
};
