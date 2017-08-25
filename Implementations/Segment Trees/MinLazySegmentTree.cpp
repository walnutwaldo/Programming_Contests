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
        if(l == s && r == e) {
            val += v;
            lazy += v;
            return;
        }
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += lazy;
            rChild->val += lazy;
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
        if(lChild != NULL && rChild != NULL) val = min(lChild->val, rChild->val);
        else val = 0;
    }

    ll query(int l, int r) {
        if(l == s && r == e) return val;
        int mid = (s + e) >> 1;
        if(lazy != 0) {
            if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
            if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
            lChild->val += lazy;
            rChild->val += lazy;
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
        ll leftVal = -1, rightVal = -1;
        if(l < mid) {
            if(lChild != NULL) leftVal = lChild->query(l, min(mid, r));
            else leftVal = 0;
        }
        if(r > mid) {
            if(rChild != NULL) rightVal = rChild->query(max(mid, l), r);
            else rightVal = 0;
        }
        if(r <= mid) return leftVal;
        if(l >= mid) return rightVal;
        return min(leftVal, rightVal);
    }
};
