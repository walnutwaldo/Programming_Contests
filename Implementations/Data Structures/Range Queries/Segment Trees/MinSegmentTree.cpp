struct SegmentTree {

    int sz;
    ll *tree;

    SegmentTree(int _sz) {
        sz = 1 << (32 - __builtin_clz(_sz - 1));
        tree = new ll[2 * sz];
        memset(tree, 0, 2 * sz * sizeof(ll));
    }

    void update(int idx, ll v) {
        idx += sz;
        tree[idx] += v;
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int lo, int hi) {
        lo += sz;
        hi += sz;
        ll res = tree[lo];
        while(lo <= hi) {
            if(lo % 2 == 1) res = min(res, tree[lo++]);
            if(hi % 2 == 0) res = min(res, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return res;
    }
};
