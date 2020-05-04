#include <bits/stdc++.h>

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define R0F(i, a) for (int i = (a) - 1; i >= 0; i--)

#define PB push_back
#define MP make_pair
#define F first
#define S second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

int n;
string tot;
vector<string> v;
vector<pii> from;
vi sa;
vll val[18];

void bs(int j, int shift, int bits) {
    vi b[1 << bits];
    int mask = (1 << bits) - 1;
    F0R(i, sa.size()) b[(val[j][sa[i]] >> shift) & mask].PB(sa[i]);
    sa.clear();
    F0R(i, 1 << bits) sa.insert(sa.end(), b[i].begin(), b[i].end());
}

void rs(int j) {
    F0R(i, 8) bs(j, 8 * i, 8);
}

void gensuff() {
    F0R(i, tot.size()) {
        sa.PB(i);
        val[0].PB(tot[i] - 'a');
    }
    rs(0);
    FOR(j, 1, 18) {
        vi idx(tot.size() + 1, 0);
        idx[sa[0]] = 1;
        FOR(i, 1, sa.size()) {
            idx[sa[i]] = idx[sa[i - 1]] + (val[j - 1][sa[i - 1]] != val[j - 1][sa[i]]);
        }
        F0R(i, sa.size()) {
            val[j].PB(((ll)idx[i] << 32) |
                      idx[min((int)tot.size(), i + (1 << (j - 1)))]);
        }
        rs(j);
    }
}

string ss(int i) { return tot.substr(i, tot.size() - i); }

int lcp(int u, int v) {
    int res = 0;
    R0F(j, 18) {
        if (val[j][u] == val[j][v]) {
            res += 1 << j;
            u += 1 << j;
            v += 1 << j;
        }
    }
    return res;
}

void upd(pii& a, int b) {
    if (a.S == -1 || from[a.S].F == from[b].F) {
        a.S = b;
    } else {
        a = MP(a.S, b);
    }
}

int main() {
    ifstream fin("standingout.in");
    ofstream fout("standingout.out");
    fin >> n;
    F0R(i, n) {
        string s;
        fin >> s;
        v.push_back(s);
        tot += s;
        tot += '$';
        F0R(j, s.size() + 1) {
            from.PB(MP(i, j));
        }
    }
    gensuff();
    vi maxsame(tot.size(), 0);
    pii running = MP(-1, -1);
    F0R(i, tot.size()) {
        int idx = sa[i];
        int notsame = running.S;
        if (notsame != -1 && from[notsame].F == from[idx].F) {
            notsame = running.F;
        }
        int maxlen = v[from[idx].F].size() - from[idx].S;
        if (notsame != -1) {
            maxsame[idx] = max(maxsame[idx], min(lcp(notsame, idx), maxlen));
        }
        if (i < sa.size() - 1) {
            maxsame[idx] = max(maxsame[idx], min(lcp(sa[i + 1], idx), maxlen));
        }
        upd(running, idx);
    }
    vi res(v.size());
    
    F0R(i, tot.size()) res[from[i].F] += v[from[i].F].size() - from[i].S - maxsame[i];
    F0R(i, n) fout << res[i] << "\n";
}
