struct SegmentTree {

    int s, e;
    ll val = 0;
    SegmentTree *lChild, *rChild;

    SegmentTree(int sz) {
        this->s = 0;
        this->e = sz;
        lChild = NULL, rChild = NULL;
    }

    SegmentTree(int s, int e) {
        this->s = s;
        this->e = e;
        lChild = NULL, rChild = NULL;
    }

    void update(int idx, ll v) {
        val += v;
        if(e == s + 1) return;
        int mid = (s + e) >> 1;
        if(idx < mid) {
            if(lChild == NULL) lChild = new SegmentTree(s, mid);
            lChild->update(idx, v);
        } else {
            if(rChild == NULL) rChild = new SegmentTree(mid, e);
            rChild->update(idx, v);
        }
    }

    ll query(int l, int r) {
        if(l == s && r == e) return val;
        int mid = (s + e) >> 1;
        ll res = 0;
        if(l < mid && lChild != NULL) res += lChild->query(l, min(mid, r));
        if(r > mid && rChild != NULL) res += rChild->query(max(mid, l), r);
        return res;
    }
};
