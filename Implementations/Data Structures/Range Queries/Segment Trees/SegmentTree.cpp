template<typename T>
struct SegmentTree {

	function<T(T, T)> comb;
	function<void(T&, T)> upd;
    int sz;
    T *tree;

    SegmentTree(int _sz = 0, function<T(T, T)> _comb = nullptr, function<void(T&, T)> _upd = nullptr)
		: comb(_comb), upd(_upd)
	{
		sz = 1 << (32 - __builtin_clz(_sz - 1));
		tree = new T[sz << 1];
        memset(tree, 0, 2 * sz * sizeof(T));
    }
    
    void update(int idx, T v) { // sets element at index idx to v
        idx += sz;
		upd(tree[idx], v);
        for(idx /= 2; idx > 0; idx /= 2) tree[idx] = comb(tree[2 * idx], tree[2 * idx + 1]);
    }

    T query(int lo, int hi) { // both ends includsive
        lo += sz, hi += sz;
        T total = tree[lo++];
        while(lo <= hi) {
            if(lo % 2 == 1) total = comb(total, tree[lo++]);
            if(hi % 2 == 0) total = comb(total, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return total;
    }
};

