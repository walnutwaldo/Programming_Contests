struct SegmentTree {

    int sz;
    ll *tree;

    SegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        memset(tree, 0, 2 * sz * sizeof(ll));
    }
    
    ll comb(ll a, ll b) { return a + b; } // modify this

    void update(int idx, ll v) { // sets element at index idx to v
        idx += sz;
        tree[idx] = v;
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = comb(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int lo, int hi) { // both ends includsive
        lo += sz, hi += sz;
        ll total = tree[lo];
        while(lo <= hi) {
            if(lo % 2 == 1) total = comb(total, tree[lo++]);
            if(hi % 2 == 0) total = comb(total, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return total;
    }
};
