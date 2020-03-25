#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define MOD 1000000007
#define MAXN 100000

#define madd(a, b) ((a) + (b)) % MOD
#define mmult(a, b) ((a) * (b)) % MOD

int n, k, _n;
vector<pii> v;
vector<int> tree[1 << 18];
ll lazy2[1 << 18];
int comb[11][11];

void initcomb() {
    comb[0][0] = 1;
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = madd(comb[i - 1][j], comb[i - 1][j - 1]);
            }
        }
    }
}

void Vmadd(vector<int>& v1, const vector<int>& v2, ll fact) {
    if (fact == 1) {
        F0R(i, k + 1) v1[i] = madd(v1[i], v2[i]);
        return;
    }
    F0R(i, k + 1) v1[i] = madd(v1[i], mmult(fact, v2[i]));
}

void Vmmult(vector<int>& v1, ll fact) {
    if (fact == 1) { return; }
    F0R(i, k + 1) v1[i] = mmult(fact, v1[i]);
}

vector<int> shift(const vector<int>& arr) {
    vector<int> res;
    F0R(i, k + 1) {
        res.PB(0);
        F0R(j, i + 1) {
            res[i] = madd(res[i], mmult((ll)comb[i][j], arr[j]));
        }
    }
    return res;
}

void init() {
    _n = 1 << (32 - __builtin_clz(n - 1));
    F0R(i, 2 * _n) tree[i] = vector<int>(k + 1, 0);
    F0R(i, 2 * _n) lazy2[i] = 1;
}

void propLazy(int idx, int s, int e) {
    F0R(i, 2) {
        Vmmult(tree[2 * idx + i], lazy2[idx]);
        lazy2[2 * idx + i] = mmult((ll)lazy2[2 * idx + i], lazy2[idx]);
    }
    lazy2[idx] = 1;
}

void pull(int idx) {
    F0R(i, tree[idx].size()) tree[idx][i] = madd(tree[2 * idx][i], tree[2 * idx + 1][i]);
}

void upd(int idx, int lo, int hi, int s, int e, const vector<int>& val) {
    if (e <= lo || s >= hi) { return; }
    if (s >= lo && e <= hi) {
        Vmadd(tree[idx], val, e - s);
        return;
    }
    propLazy(idx, s, e);
    int mid = (s + e) >> 1;
    upd(2 * idx, lo, hi, s, mid, val);
    upd(2 * idx + 1, lo, hi, mid, e, val);
    pull(idx);
}

void upd2(int idx, int lo, int hi, int s, int e) {
    if (e <= lo || s >= hi) { return; }
    if (s >= lo && e <= hi) {
        Vmmult(tree[idx], 2);
        lazy2[idx] = mmult(lazy2[idx], 2);
        return;
    }
    propLazy(idx, s, e);
    int mid = (s + e) >> 1;
    upd2(2 * idx, lo, hi, s, mid);
    upd2(2 * idx + 1, lo, hi, mid, e);
    pull(idx);
}

vector<int> query(int idx, int lo, int hi, int s, int e) {
    if (e <= lo || s >= hi) { return vector<int>(k + 1, 0); }
    if (s >= lo && e <= hi) {
        return tree[idx];
    }
    propLazy(idx, s, e);
    int mid = (s + e) >> 1;
    vector<int> res = query(2 * idx, lo, hi, s, mid);
    Vmadd(res, query(2 * idx + 1, lo, hi, mid, e), 1);
    return res;
}

int main() {
    ifstream cin("help.in");
    ofstream cout("help.out");
    initcomb();
    cin >> n >> k;
    n++;
    init();
    vector<int> rLocs;
    F0R(i, n - 1) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        v.emplace_back(l, r);
        rLocs.push_back(r);
    }
    sort(v.begin(), v.end());
    sort(rLocs.begin(), rLocs.end());
    vector<int> initV(k + 1, 0);
    initV[0] = 1;
    upd(1, 0, 1, 0, _n, initV);
    F0R(i, n - 1) {
        int lIdx = upper_bound(rLocs.begin(), rLocs.end(), v[i].first) - rLocs.begin() + 1;
        int rIdx = lower_bound(rLocs.begin(), rLocs.end(), v[i].second) - rLocs.begin() + 1;
        upd2(1, rIdx, n, 0, _n);
        vector<int> add1 = query(1, lIdx, rIdx, 0, _n);
        vector<int> add2 = shift(query(1, 0, lIdx, 0, _n));
        Vmadd(add1, add2, 1);
        upd(1, rIdx, rIdx + 1, 0, _n, add1);
    }
    cout << query(1, 0, n, 0, _n)[k] << endl;
}
