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

    void propogateLazy(int idx, int s, int e, int mid) {
        tree[2 * idx] += (mid - s) * lazy[idx];
        tree[2 * idx + 1] += (e - mid) * lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int idx, int s, int e, int l, int r, ll v) {
        tree[idx] += (r - l) * v;
        if(l == s && r == e) {
            lazy[idx] += v;
            return;
        }
        int mid = (s + e) >> 1;
        propogateLazy(idx, s, e, mid);
        if(l < mid) update(2 * idx, s, mid, l, min(r, mid), v);
        if(r > mid) update(2 * idx + 1, mid, e, max(l, mid), r, v);
    }

    void update(int l, int r, ll v) {
        update(1, 0, sz, l, r, v);
    }

    ll query(int idx, int s, int e, int l, int r) {
        if(l == s && r == e) return tree[idx];
        int mid = (s + e) >> 1;
        propogateLazy(idx, s, e, mid);
        ll total = 0;
        if(l < mid) total += query(2 * idx, s, mid, l, min(mid, r));
        if(r > mid) total += query(2 * idx + 1, mid, e, max(mid, l), r);
        return total;
    }

    ll query(int l, int r) {
        return query(1, 0, sz, l, r);
    }
};
