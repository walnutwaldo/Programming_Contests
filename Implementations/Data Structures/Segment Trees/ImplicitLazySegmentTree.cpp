struct LazySegmentTree {

    int s, e;
    ll val = 0, lazy = 0;
    LazySegmentTree *lChild = NULL, *rChild = NULL;

    LazySegmentTree(int sz) {
        this->s = 0;
        this->e = sz;
    }

    LazySegmentTree(int s, int e) {
        this->s = s;
        this->e = e;
    }
    
    void propogateLazy() {
        int mid = (s + e) >> 1;
        if(lChild == NULL) lChild = new LazySegmentTree(s, mid);
        if(rChild == NULL) rChild = new LazySegmentTree(mid, e);
        lChild->val += (mid - s) * lazy;
        rChild->val += (e - mid) * lazy;
        lChild->lazy += lazy;
        rChild->lazy += lazy;
        lazy = 0;
    }

    void update(int l, int r, ll v) {
        val += (r - l) * v;
        if(l == s && r == e) {
            lazy += v;
            return;
        }
        if(lazy != 0) propogateLazy();
        int mid = (s + e) >> 1;
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
        if(lazy != 0) propogateLazy();
        int mid = (s + e) >> 1;
        ll total = 0;
        if(l < mid && lChild != NULL) total += lChild->query(l, min(mid, r));
        if(r > mid && rChild != NULL) total += rChild->query(max(mid, l), r);
        return total;
    }
};
