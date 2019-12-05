#include <bits/stdc++.h>

using namespace std;

struct segtree {
    
    int sz;
    int *tree, *lazy;
    
    segtree(int _sz) {
        sz = (1 << (32 - __builtin_clz(_sz - 1)));
        tree = new int[2 * sz];
        lazy = new int[2 * sz];
        for (int i = 0; i < 2 * sz; i++) { tree[i] = lazy[i] = 0; }
    }
    
    void proplazy(int i) {
        for (int j = 0; j < 2; j++) {
            tree[2 * i + j] += lazy[i];
            lazy[2 * i + j] += lazy[i];
        }
        lazy[i] = 0;
    }
    
    void upd(int lo, int hi, int amt, int i = 1, int s = 0, int e = -1) {
        if (e == -1) { e = sz; }
        if (hi <= s || lo >= e) { return; }
        if (lo <= s && hi >= e) {
            tree[i] += amt;
            lazy[i] += amt;
            return;
        }
        proplazy(i);
        int mid = (s + e) >> 1;
        upd(lo, hi, amt, 2 * i, s, mid);
        upd(lo, hi, amt, 2 * i + 1, mid, e);
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    
    int query(int lo, int hi, int i = 1, int s = 0, int e = -1) {
        if (e == -1) { e = sz; }
        if (hi <= s || lo >= e) { return -1; }
        if (lo <= s && hi >= e) {
            return tree[i];
        }
        proplazy(i);
        int mid = (s + e) >> 1;
        return max(query(lo, hi, 2 * i, s, mid),
                   query(lo, hi, 2 * i + 1, mid, e));
    }
    
};

struct upd {
    int g;
    int x;
    int y;
    
    bool operator<(const upd& other) const {
        return make_tuple(x, g, y) < make_tuple(other.x, g, other.y);
    }
    
};

int n;
int k;
vector<upd> upds;
vector<int> iy;

void compress() {
    sort(iy.begin(), iy.end());
    iy.erase(unique(iy.begin(), iy.end()), iy.end());
}

int main() {
    ifstream cin("lazy.in");
    ofstream cout("lazy.out");
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        upd p;
        cin >> p.g >> p.x >> p.y;
        upds.push_back({ p.g, p.x - p.y - k, p.x + p.y });
        upds.push_back({ -p.g, p.x - p.y + k + 1, p.x + p.y });
        iy.push_back(p.x + p.y + k);
        iy.push_back(p.x + p.y - k);
    }
    compress();
    sort(upds.begin(), upds.end());
    segtree st(iy.size());
    int res = 0;
    for (const upd& u : upds) {
        int g = u.g;
        int y = u.y;
        int lo = lower_bound(iy.begin(), iy.end(), y - k) - iy.begin();
        int hi = lower_bound(iy.begin(), iy.end(), y + k) - iy.begin();
        st.upd(lo, hi + 1, g);
        res = max(res, st.query(0, iy.size()));
    }
    cout << res << endl;
    return 0;
}
