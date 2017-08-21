struct MaxSegmentTree {

    int sz;
    ll *tree;

    MaxSegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        memset(tree, 0, sizeof tree);
    }

    void update(int idx, ll v) {
        idx += sz;
        tree[idx] += v;
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int lo, int hi) {
        lo += sz;
        hi += sz;
        ll res = tree[lo];
        while(lo <= hi) {
            if(lo % 2 == 1) res = max(res, tree[lo++]);
            if(hi % 2 == 0) res = max(res, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return res;
    }
};
