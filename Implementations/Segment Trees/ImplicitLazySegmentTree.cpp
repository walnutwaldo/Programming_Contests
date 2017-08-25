struct LazySegmentTree {

    int s, e;
    ll val = 0, lazy = 0;
    LazySegmentTree *lChild, *rChild;

    LazySegmentTree(int sz) {
        this->s = 0;
        this->e = sz;
        lChild = NULL, rChild = NULL;
    }

    LazySegmentTree(int s, int e) {
        this->s = s;
        this->e = e;
        lChild = NULL, rChild = NULL;
    }

    void update(int l, int r, ll v) {
        val += (r - l) * v;
        if(l == s && r == e) {
            lazy += v;
            return;
        }
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += (mid - s) * lazy;
            rChild->val += (e - mid) * lazy;
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
        if(l < mid) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            lChild->update(l, min(r, mid), v);
        }
        if(r > mid) {
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            rChild->update(max(l, mid), r, v);
        }
    }

    ll query(int l, int r) {
        if(l == s && r == e) return val;
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += (mid - s) * lazy;
            rChild->val += (e - mid) * lazy;
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
        ll res = 0;
        if(l < mid && lChild != NULL) res += lChild->query(l, min(mid, r));
        if(r > mid && rChild != NULL) res += rChild->query(max(mid, l), r);
        return res;
    }
};
