#include <bits/stdc++.h>

using namespace std;

#define PB push_back

typedef long long ll;

struct segtree {
    
    int sz;
    vector<ll> tree, lazy;
    
    segtree(int _sz) {
        sz = 1 << (32 - __builtin_clz(_sz - 1));
        tree = vector<ll>(2 * sz, 0);
        lazy = vector<ll>(2 * sz, 0);
    }
    
    void prop(int idx, int lo, int hi) {
        for (int i = 0; i < 2; i++) {
            tree[2 * idx + i] += (hi - lo) / 2 * lazy[idx];
            lazy[2 * idx + i] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    
    void upd(int lo, int hi, long long v, int idx = 1, int s = 0, int e = -1) {
        if (e == -1) { e = sz; }
        if (hi <= s || lo >= e) { return; }
        if (lo <= s && hi >= e) {
            tree[idx] += v * (e - s);
            lazy[idx] += v;
            return;
        }
        prop(idx, s, e);
        int mid = (s + e) >> 1;
        upd(lo, hi, v, idx * 2, s, mid);
        upd(lo, hi, v, idx * 2 + 1, mid, e);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
    
    long long query(int lo, int hi, int idx = 1, int s = 0, int e = -1) {
        if (e == -1) { e = sz; }
        if (hi <= s || lo >= e) { return 0; }
        if (lo <= s && hi >= e) {
            return tree[idx];
        }
        prop(idx, s, e);
        int mid = (s + e) >> 1;
        return query(lo, hi, 2 * idx, s, mid) + query(lo, hi, 2 * idx + 1, mid, e);
    }
    
};

#define MAXN 100000

int n, q;
pair<int, int> t[MAXN];
vector<int> adj[MAXN];
set<pair<int, int>> ofcolor[MAXN];

void dfs(int node, int par, int currT) {
    t[node].first = currT++;
    for (const int next : adj[node]) {
        if (next != par) {
            dfs(next, node, currT);
            currT = t[next].second;
        }
    }
    t[node].second = currT;
}

int main() {
    ifstream cin("snowcow.in");
    ofstream cout("snowcow.out");
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].PB(b);
        adj[b].PB(a);
    }
    dfs(0, -1, 0);
    segtree st(n);
    for (int i = 0; i < q; i++) {
        int command;
        cin >> command;
        if (command == 1) {
            int node;
            ll c;
            cin >> node >> c;
            c--;
            node--;
            auto ptr = ofcolor[c].lower_bound(t[node]);
            while (ptr != ofcolor[c].end() && ptr->second <= t[node].second) {
                st.upd(ptr->first, ptr->second, -1);
                ptr = ofcolor[c].erase(ptr);
            }
            if (ofcolor[c].empty() || ptr == ofcolor[c].begin() || (--ptr)->second <= t[node].first) {
                {
                    ofcolor[c].insert(t[node]);
                    st.upd(t[node].first, t[node].second, 1);
                }
            }
        } else {
            int node;
            cin >> node;
            node--;
            cout << st.query(t[node].first, t[node].second) << "\n";
        }
    }
    return 0;
}
