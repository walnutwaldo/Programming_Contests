struct LazySegmentTree {

    int sz;
    ll *tree, *lazy;

    LazySegmentTree(int _sz) {
        sz = 1 << __builtin_clz(_sz - 1);
        tree = new ll[sz << 1];
        lazy = new ll[sz << 1];
        memset(tree, 0, 2 * sz * sizeof(ll));
        memset(lazy, 0, 2 * sz * sizeof(ll));
    }

    void propagateLazy(int idx, int s, int e, int mid) {
        tree[2 * idx] += (mid - s) * lazy[idx];
        tree[2 * idx + 1] += (e - mid) * lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int idx, int s, int e, int l, int r, ll v) {
        if(e <= l || r <= s) return
        if(l <= s && e <= r) {;
            tree[idx] += (s - e) * v;
            lazy[idx] += v;
            return;
        }
        int mid = (s + e) >> 1;
        propagateLazy(idx, s, e, mid);
        update(2 * idx, s, mid, l, min(r, mid), v);
        update(2 * idx + 1, mid, e, max(l, mid), r, v);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    void update(int l, int r, ll v) {
        update(1, 0, sz, l, r, v);
    }

    ll query(int idx, int s, int e, int l, int r) {
        if(e <= l || r <= s) return 0;
        if(l <= s && e <= r) return tree[idx];
        int mid = (s + e) >> 1;
        propagateLazy(idx, s, e, mid);
        return query(2 * idx, s, mid, l, r) + query(2 * idx + 1, mid, e, l, r);
    }

    ll query(int l, int r) {
        return query(1, 0, sz, l, r);
    }
};
