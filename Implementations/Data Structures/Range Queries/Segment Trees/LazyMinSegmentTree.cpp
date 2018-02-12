struct LazySegmentTree {

    int sz;
    ll *tree, *lazy;

    LazySegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        lazy = new ll[2 * sz];
        memset(tree, 0, 2 * sz * sizeof(ll));
        memset(lazy, 0, 2 * sz * sizeof(ll));
    }

    void propagateLazy(int idx) {
        tree[2 * idx] += lazy[idx];
        tree[2 * idx + 1] += lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int idx, int s, int e, int l, int r, ll v) {
        if(l == s && r == e) {
            tree[idx] += v;
            lazy[idx] += v;
            return;
        }
        propagateLazy(idx);
        int mid = (s + e) >> 1;
        if(l < mid) update(2 * idx, s, mid, l, min(r, mid), v);
        if(r > mid) update(2 * idx + 1, mid, e, max(l, mid), r, v);
        tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    void update(int l, int r, ll v) {
        update(1, 0, sz, l, r, v);
    }

    ll query(int idx, int s, int e, int l, int r) {
        if(l == s && r == e) return tree[idx];
        propagateLazy(idx);
        int mid = (s + e) >> 1;
        if(l < mid && r > mid) return min(query(2 * idx, s, mid, l, min(mid, r)), query(2 * idx + 1, mid, e, max(mid, l), r));
        else if(l < mid) return query(2 * idx, s, mid, l, min(mid, r));
        else return query(2 * idx + 1, mid, e, max(mid, l), r);
    }

    ll query(int l, int r) {
        return query(1, 0, sz, l, r);
    }
};
