#include <bits/stdc++.h>

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXN 100000

pair<int, ll> comb(pair<int, ll> p1, pair<int, ll> p2) {
    pair<int, ll> res;
    if(p1.F == p2.F) res = MP(p1.F, p1.S + p2.S);
    else res = max(p1, p2);
    if(res.S < 0) res.S = 1e18;
    return res;
}

struct BIT {

    int sz;
    pair<int, ll> *tree;

    BIT(int sz) {
        this->sz = sz;
        tree = new pair<int, ll>[sz + 1];
        F0R(i, sz + 1) tree[i] = MP(0, 0);
    }

    void update(int idx, pair<int, ll> v) {
        for(int i = sz - idx; i <= sz; i += i & -i) tree[i] = comb(tree[i], v);
    }

    pair<int, ll> query(int idx) {
        pair<int, ll> res = MP(0, 0);
        for(int i = sz - idx; i > 0; i -= i & -i) res = comb(res, tree[i]);
        return res;
    }

};

struct MSTree {

    BIT *bit = NULL;
    MSTree *lChild = NULL, *rChild = NULL;
    int s, e, *arr;

    MSTree(int s, int e, int* arr2) {
        this->s = s, this->e = e;
        bit = new BIT(e - s);
        arr = new int[e - s];
        if(e - s == 1) arr[0] = arr2[s];
        else {
            int m = (s + e) >> 1;
            lChild = new MSTree(s, m, arr2);
            rChild = new MSTree(m, e, arr2);
            int i = 0, j = 0;
            while(i < m - s || j < e - m) {
                if(j == e - m || i != m - s && lChild->arr[i] < rChild->arr[j]) arr[i++ + j] = lChild->arr[i];
                else arr[i + j++] = rChild->arr[j];
            }
        }
    }

    int update(int idx, pair<int, ll> v) {
        int a;
        if(e == s + 1) a = arr[0];
        else if(idx >= (s + e) / 2) a = rChild->update(idx, v);
        else a = lChild->update(idx, v);
        int i = LB(arr, arr + e - s, a) - arr;
        bit->update(i, v);
        return a;
    }

    pair<int, ll> query(int lo, int hi, int lb) {
        if(hi <= s || lo >= e) return MP(0, 0);
        if(s >= lo && e <= hi) return bit->query(LB(arr, arr + e - s, lb) - arr);
        return comb(lChild->query(lo, hi, lb), rChild->query(lo, hi, lb));
    }

};

int n, arr[MAXN], idxOf[MAXN + 1];
ll k;

int main() {
    ifstream fin("itout.in");
    ofstream fout("itout.out");
    fin >> n >> k;
    F0R(i, n) {
        fin >> arr[i];
        idxOf[arr[i]] = i;
    }
    MSTree tree(0, n, arr);
    R0F(i, n) {
        pair<int, ll> p = tree.query(i, n, arr[i]);
        if(p.F == 0) p.S = 1;
        tree.update(i, MP(p.F + 1, p.S));
    }
    int curr = -1;
    set<int> res;
    while(1) {
        int lo = ((curr == -1)?1:arr[curr] + 1), hi = n;
        pair<int, ll> r = tree.query(curr + 1, n, lo);
        if(r.F == 0) break;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            pair<int, ll> p = tree.query(curr + 1, n, mid);
            if(p.F == r.F && p.S >= k) lo = mid;
            else hi = mid - 1;
        }
        pair<int, ll> r2 = tree.query(curr + 1, n, lo + 1);
        if(r2.F == r.F) k -= r2.S;
        curr = idxOf[lo];
        res.insert(lo);
    }
    fout << n - sz(res) << "\n";
    FOR(i, 1, n + 1) if(!res.count(i)) fout << i << "\n";
}
