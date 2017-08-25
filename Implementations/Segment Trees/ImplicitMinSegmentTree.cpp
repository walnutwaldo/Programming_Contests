struct SegmentTree {

    int s, e;
    ll val = 0;
    SegmentTree *lChild = NULL, *rChild = NULL;

    SegmentTree(int sz) {
        this->s = 0;
        this->e = sz;
    }

    SegmentTree(int s, int e) {
        this->s = s;
        this->e = e;
    }

    void update(int idx, ll v) {
        if(e == s + 1) {
            val += v;
            return;
        }
        int mid = (s + e) >> 1;
        if(idx < mid) {
            if(lChild == NULL) lChild = new SegmentTree(s, mid);
            lChild->update(idx, v);
        } else {
            if(rChild == NULL) rChild = new SegmentTree(mid, e);
            rChild->update(idx, v);
        }
        if(lChild == NULL) val = min(0, rChild->val);
        else if(rChild == NULL) val = min(0, lChild->val);
        else val = min(lChild->val, rChild->val);
    }

    ll query(int l, int r) {
        if(l == s && r == e) return val;
        int mid = (s + e) >> 1;
        int lVal = 0, rVal = 0;
        if(l < mid && lChild != NULL) lVal = lChild->query(l, min(mid, r));
        if(r > mid && rChild != NULL) rVal = rChild->query(max(mid, l), r);
        if(r <= mid) return lVal;
        else if(l >= mid) return rVal;
        else return min(lVal, rVal);
    }
};
