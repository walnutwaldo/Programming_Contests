#include <bits/stdc++.h>

#define PB push_back

using namespace std;

typedef vector<int> vi;

#define MAXN 100000

int n;
vi adj[MAXN];

bool pairable(vi& children, int ign, int k) {
    vector<int> q;
    for (int i = 0; i < children.size(); i++) {
        if (i != ign) {
            int v = children[i];
            if (q.empty()) {
                if (v < k) { q.push_back(v); }
            } else {
                if (q.back() + v >= k) { q.pop_back(); } else { q.push_back(v); }
            }
        }
    }
    return q.empty();
}

int maxinto(int node, int k, int par = -1) {
    vector<int> children;
    for (const int next : adj[node]) {
        if (next != par) {
            children.push_back(maxinto(next, k, node) + 1);
            if (children.back() == INT_MIN) { return INT_MIN; }
        }
    }
    if (children.empty()) { return 0; }
    sort(children.begin(), children.end());
    vector<int> q;
    int res = 0;
    for (const int v : children) {
        if (q.empty()) {
            if (v >= k) { res = max(res, v); } else{ q.push_back(v); }
        } else {
            if (q.back() + v >= k) { q.pop_back(); } else { q.push_back(v); }
        }
    }
    if (q.size() >= 2) {
        return INT_MIN;
    } else {
        int lo = -1, hi = children.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (pairable(children, mid, k)) { lo = mid; } else{ hi = mid - 1; }
        }
        if (lo == -1) { return 0; }
        return children[lo];
    }
}

bool works(int k) {
    vi v;
    for (const int next : adj[0]) {
        v.PB(maxinto(next, k, 0) + 1);
    }
    sort(v.begin(), v.end());
    return pairable(v, -1, k);
}

int main() {
    ifstream cin("deleg.in");
    ofstream cout("deleg.out");
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].PB(b);
        adj[b].PB(a);
    }
    int lo = 1, hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (works(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << endl;
}
