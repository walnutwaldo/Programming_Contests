#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

struct SegmentTree {

    int sz;
    ll *tree;

    SegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new ll[2 * sz];
        F0R(i, 2 * sz) tree[i] = 1e15;
    }

    void update(int idx, ll v) {
        idx += sz;
        if(tree[idx] > v)
            tree[idx] = v;
        for(idx /= 2; idx > 0; idx /= 2)
            tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
    }

    ll query(int lo, int hi) {
        lo += sz;
        hi += sz;
        ll res = tree[lo];
        while(lo <= hi) {
            if(lo % 2 == 1)
                res = min(res, tree[lo++]);
            if(hi % 2 == 0)
                res = min(res, tree[hi--]);
            lo /= 2;
            hi /= 2;
        }
        return res;
    }
};

int n, m, numIndices;
vector<tuple<pii, pair<ll, ll>, ll>> slings;
vector<pair<pii, pair<ll, ll>>> manures;
set<ll> indices;
ll res[100000];

void compressIndices() {
    unordered_map<ll, int> compress;
    int cntr = 0;
    for(const ll index : indices)
        compress[index] = cntr++;
    F0R(i, n) {
        get<0>(slings[i]).F = compress[get<1>(slings[i]).F];
        get<0>(slings[i]).S = compress[get<1>(slings[i]).S];
    }
    F0R(i, m) {
        manures[i].F.F = compress[manures[i].S.F];
        manures[i].F.S = compress[manures[i].S.S];
    }
}

int main() {
    ifstream fin("slingshot.in");
    ofstream fout("slingshot.out");
    fin >> n >> m;
    F0R(i, n) {
        ll x, y, t;
        fin >> x >> y >> t;
        slings.PB(MT(MP(0, 0), MP(x, y), t));
        indices.insert(x), indices.insert(y);
    }
    F0R(i, m) {
        ll a, b;
        fin >> a >> b;
        manures.PB(MP(MP(0, 0), MP(a, b)));
        indices.insert(a), indices.insert(b);
    }
    sort(slings.begin(), slings.end());
    compressIndices();
    numIndices = indices.size();

    // First
    SegmentTree st(numIndices);

    vector<pair<pair<int, pii>, pair<int, int>>> queries;
    F0R(i, m) {
        int x = manures[i].S.F, y = manures[i].S.S;
        res[i] = abs(x - y);
        queries.PB(MP(MP(manures[i].F.F, MP(manures[i].F.S, numIndices - 1)), MP(x - y, i)));
    }
    sort(queries.begin(), queries.end());
    int currSling = 0, currQuery = 0;
    F0R(x, numIndices) {
        while(currSling < slings.size() && get<0>(slings[currSling]).F == x) {
            ll s = get<1>(slings[currSling]).F, e = get<1>(slings[currSling]).S;
            st.update(get<0>(slings[currSling]).S, e - s + get<2>(slings[currSling]));
            currSling++;
        }
        while(currQuery < queries.size() && queries[currQuery].F.F == x) {
            pair<pair<int, pii>, pair<int, int>> q = queries[currQuery];
            res[q.S.S] = min(res[q.S.S], q.S.F + st.query(q.F.S.F, q.F.S.S));
            currQuery++;
        }
    }
    // Second
    st = SegmentTree(numIndices);

    queries.clear();
    F0R(i, m) {
        int x = manures[i].S.F, y = manures[i].S.S;
        queries.PB(MP(MP(manures[i].F.F, MP(0, manures[i].F.S)), MP(y - x, i)));
    }
    sort(queries.begin(), queries.end());
    currSling = slings.size() - 1, currQuery = queries.size() - 1;
    R0F(x, numIndices) {
        while(currSling >= 0 && get<0>(slings[currSling]).F == x) {
            ll s = get<1>(slings[currSling]).F, e = get<1>(slings[currSling]).S;
            st.update(get<0>(slings[currSling]).S, s - e + get<2>(slings[currSling]));
            currSling--;
        }
        while(currQuery >= 0 && queries[currQuery].F.F == x) {
            pair<pair<int, pii>, pair<int, int>> q = queries[currQuery];
            res[q.S.S] = min(res[q.S.S], q.S.F + st.query(q.F.S.F, q.F.S.S));
            currQuery--;
        }
    }
    // Third
    st = SegmentTree(numIndices);

    queries.clear();
    F0R(i, m) {
        int x = manures[i].S.F, y = manures[i].S.S;
        queries.PB(MP(MP(manures[i].F.F, MP(0, manures[i].F.S)), MP(x + y, i)));
    }
    sort(queries.begin(), queries.end());
    currSling = 0, currQuery = 0;
    F0R(x, numIndices) {
        while(currSling < slings.size() && get<0>(slings[currSling]).F == x) {
            ll s = get<1>(slings[currSling]).F, e = get<1>(slings[currSling]).S;
            st.update(get<0>(slings[currSling]).S, - s - e + get<2>(slings[currSling]));
            currSling++;
        }
        while(currQuery < queries.size() && queries[currQuery].F.F == x) {
            pair<pair<int, pii>, pair<int, int>> q = queries[currQuery];
            res[q.S.S] = min(res[q.S.S], q.S.F + st.query(q.F.S.F, q.F.S.S));
            currQuery++;
        }
    }
    // Fourth
    st = SegmentTree(numIndices);

    queries.clear();
    F0R(i, m) {
        int x = manures[i].S.F, y = manures[i].S.S;
        queries.PB(MP(MP(manures[i].F.F, MP(manures[i].F.S, numIndices - 1)), MP(- x - y, i)));
    }
    sort(queries.begin(), queries.end());
    currSling = slings.size() - 1, currQuery = queries.size() - 1;
    R0F(x, numIndices) {
        while(currSling >= 0 && get<0>(slings[currSling]).F == x) {
            ll s = get<1>(slings[currSling]).F, e = get<1>(slings[currSling]).S;
            st.update(get<0>(slings[currSling]).S, s + e + get<2>(slings[currSling]));
            currSling--;
        }
        while(currQuery >= 0 && queries[currQuery].F.F == x) {
            pair<pair<int, pii>, pair<int, int>> q = queries[currQuery];
            res[q.S.S] = min(res[q.S.S], q.S.F + st.query(q.F.S.F, q.F.S.S));
            currQuery--;
        }
    }

    F0R(i, m) fout << res[i] << "\n";
    return 0;
}
