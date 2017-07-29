#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, q;
ll STmin[1 << 19], STsum[1 << 19], STprop[1 << 19];

void update(int s, int e, int l, int r, int n, ll v) {
    if(s == l && r == e) {
        STprop[n] += v;
        STsum[n] += (r - l) * v;
        STmin[n] += v;
        return;
    }
    int mid = (l + r) >> 1;
    STmin[2 * n] += STprop[n];
    STsum[2 * n] += (mid - l) * STprop[n];
    STprop[2 * n] += STprop[n];
    STmin[2 * n + 1] += STprop[n];
    STsum[2 * n + 1] += (r - mid) * STprop[n];
    STprop[2 * n + 1] += STprop[n];
    STprop[n] = 0;

    if(s < mid) update(s, min(mid, e), l, mid, 2 * n, v);
    if(e > mid) update(max(mid, s), e, mid, r, 2 * n + 1, v);
    STsum[n] = STsum[2 * n] + STsum[2 * n + 1];
    STmin[n] = min(STmin[2 * n], STmin[2 * n + 1]);
}

ll minQuery(int s, int e, int l, int r, int n) {
    if(s == l && r == e) {
        return STmin[n];
    }
    int mid = (l + r) >> 1;
    STmin[2 * n] += STprop[n];
    STsum[2 * n] += (mid - l) * STprop[n];
    STprop[2 * n] += STprop[n];
    STmin[2 * n + 1] += STprop[n];
    STsum[2 * n + 1] += (r - mid) * STprop[n];
    STprop[2 * n + 1] += STprop[n];
    STprop[n] = 0;

    ll res = -1;
    if(s < mid) {
        ll m = minQuery(s, min(mid, e), l, mid, 2 * n);
        if(res == -1 || m < res) res = m;
    }
    if(e > mid) {
        ll m = minQuery(max(mid, s), e, mid, r, 2 * n + 1);
        if(res == -1 || m < res) res = m;
    }
    return res;
}

ll sumQuery(int s, int e, int l, int r, int n) {
    if(s == l && r == e) {
        return STsum[n];
    }
    int mid = (l + r) >> 1;
    STmin[2 * n] += STprop[n];
    STsum[2 * n] += (mid - l) * STprop[n];
    STprop[2 * n] += STprop[n];
    STmin[2 * n + 1] += STprop[n];
    STsum[2 * n + 1] += (r - mid) * STprop[n];
    STprop[2 * n + 1] += STprop[n];
    STprop[n] = 0;

    ll res = 0;
    if(s < mid) res += sumQuery(s, min(mid, e), l, mid, 2 * n);
    if(e > mid) res += sumQuery(max(mid, s), e, mid, r, 2 * n + 1);
    return res;
}

int main() {
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");
    fin >> n >> q;
    int upN = exp2(ceil(log2(n)));
    F0R(i, n) {
        ll v;
        fin >> v;
        update(i, i + 1, 0, upN, 1, v);
    }
    n = upN;
    F0R(i, q) {
        char command;
        fin >> command;
        if(command == 'P') {
            int a, b;
            ll c;
            fin >> a >> b >> c;
            a--;
            update(a, b, 0, n, 1, c);
        } else if(command == 'M') {
            int a, b;
            fin >> a >> b;
            a--;
            fout << minQuery(a, b, 0, n, 1) << "\n";
        } else {
            int a, b;
            fin >> a >> b;
            a--;
            fout << sumQuery(a, b, 0, n, 1) << "\n";
        }
    }
    return 0;
}
