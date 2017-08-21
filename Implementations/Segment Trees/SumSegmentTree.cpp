struct SumSegmentTree {

    int sz;
    ll *tree;

    SumSegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        memset(tree, 0, sizeof tree);
    }

    void update(ll v, int idx) {
        idx += sz;
        tree[idx] += v;
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    ll query(int lo, int hi) {
        lo += sz;
        hi += sz;
        ll total = 0;
        while(lo <= hi) {
            if(lo % 2 == 1) total += tree[lo++];
            if(hi % 2 == 0) total += tree[hi--];
            lo /= 2;
            hi /= 2;
        }
        return total;
    }

};
