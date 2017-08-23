#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define MAXN 300000
#define MAXM 300000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

struct SegmentTree {

    int sz;
    pair<ll, int> *tree;

    SegmentTree(int pre_sz) {
        sz = 1 << (int)ceil(log2(pre_sz));
        tree = new pair<ll, int>[2 * sz];
        F0R(i, sz) {
            tree[sz + i] = MP(0, i);
            update(i, 0);
        }
    }

    void update(int idx, ll v) {
        idx += sz;
        tree[idx].F += v;
        for(idx /= 2; idx > 0; idx /= 2) {
            if(tree[idx * 2].F >= tree[idx * 2 + 1].F) tree[idx] = tree[idx * 2];
            else tree[idx] = tree[idx * 2 + 1];
        }
    }

    int query(int lo, int hi) {
        lo += sz;
        hi += sz;
        int bestI = -1;
        while(lo <= hi) {
            if(lo % 2 == 1) {
                if(bestI == -1 || tree[lo].F > tree[sz + bestI].F) bestI = tree[lo].S;
                lo++;
            }
            if(hi % 2 == 0) {
                if(bestI == -1 || tree[hi].F > tree[sz + bestI].F) bestI = tree[hi].S;
                hi--;
            }
            lo /= 2;
            hi /= 2;
        }
        return bestI;
    }
};

int n, m;
ll C, single[MAXN], opt[MAXN];
vector<tuple<ll, ll, ll>> clouds;
vector<pair<ll, int>> queries;
ll answerToQuery[MAXM];
unordered_map<ll, ll> cross;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> C;
    vector<pair<ll, int>> toProcess;
    F0R(i, n) {
        ll l, r, c;
        cin >> l >> r >> c;
        clouds.PB(MT(c, l, r));
    }
    sort(clouds.begin(), clouds.end());
    F0R(i, n) {
        ll l = get<1>(clouds[i]);
        ll r = get<2>(clouds[i]);
        toProcess.PB(MP(l, i));
        toProcess.PB(MP(r, i));
    }
    sort(toProcess.begin(), toProcess.end());
    cin >> m;
    F0R(i, m) {
        ll k;
        cin >> k;
        queries.PB(MP(k, i));
    }
    sort(queries.begin(), queries.end());
    int atQuery = 0;
    unordered_set<int> open;
    ll free = 0;
    ll top = 0;
    ll lastSpot = 0;
    SegmentTree st(n);
    for(const pair<ll, ll> p : toProcess) {
        ll len = p.F - lastSpot;
        if(open.empty()) free += len;
        else if(open.size() == 1) {
            int a = *(open.begin());
            if(get<0>(clouds[a]) <= C) {
                st.update(a, -single[a] - 1);
                single[a]+= len;
                opt[a]+= len;
                int searchEnd = UB(clouds.begin(), clouds.end(), MT(C - get<0>(clouds[a]), 10000000000, 10000000000)) - clouds.begin() - 1;
                if(searchEnd >= 0) {
                    int other = st.query(0, searchEnd);
                    if(other != a) {
                        ll total = single[a] + single[other] + cross[(ll)min(a, other) * (n + 1) + max(a, other)];
                        opt[a] = max(opt[a], total);
                        opt[other] = max(opt[other], total);
                        top = max(top, max(opt[a], opt[other]));
                    }
                }
                top = max(top, opt[a]);
                st.update(a, single[a] + 1);
            }
        } else if(open.size() == 2) {
            int a = min(*(open.begin()), *(++open.begin()));
            int b = max(*(open.begin()), *(++open.begin()));
            cross[(ll)a * (n + 1) + b]+=len;
            if(get<0>(clouds[a]) + get<0>(clouds[b]) <= C) {
                opt[a] = max(opt[a], cross[(ll)a * (n + 1) + b] + single[a] + single[b]);
                opt[b] = max(opt[b], cross[(ll)a * (n + 1) + b] + single[a] + single[b]);
            }
            top = max(top, max(opt[a], opt[b]));
        }
        if(open.count(p.S)) open.erase(p.S);
        else open.insert(p.S);
        lastSpot = p.F;
        while(atQuery < m && queries[atQuery].F <= free + top) {
            answerToQuery[queries[atQuery].S] = lastSpot - free - top + queries[atQuery].F;
            atQuery++;
        }
        if(atQuery == m) break;
    }
    while(atQuery < m) {
        answerToQuery[queries[atQuery].S] = lastSpot - free - top + queries[atQuery].first;
        atQuery++;
    }
    F0R(i, m) {
        cout << answerToQuery[i] << "\n";
    }
    return 0;
}
