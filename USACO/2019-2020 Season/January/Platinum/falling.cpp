#include <bits/stdc++.h>

using namespace std;

#define MAXN 200000

int n, a[MAXN], qidx[MAXN];
pair<long long, long long> res[MAXN];
vector<pair<int, int>> v;

void solve() {
    v.clear();
    for (int i = 0; i < n; i++) {
        v.emplace_back(a[i], i);
    }
    sort(v.begin(), v.end());
    
    vector<int> q;
    for (int i = 0; i < n; i++) {
        long long y = v[i].first;
        long long x = v[i].second;
        while (!q.empty() && q.back() > x) { q.pop_back(); }
        while (!q.empty() && q.size() >= 2) {
            long long x2 = q.back(); long long y2 = a[x2];
            long long x1 = q[q.size() - 2]; long long y1 = a[x1];
            if ((x2 - x) * (y1 - y) < (y2 - y) * (x1 - x)) { q.pop_back(); } else { break; }
        }
        q.push_back(x);
        
        // cout << x << " " << qidx[x] << " " << a[x] << " " << a[qidx[x]] << endl;
        if (a[qidx[x]] > a[x]) {
            int lo = 0, hi = lower_bound(q.begin(), q.end(), qidx[x]) - q.begin() - 1;
            if (hi == -1) {
                continue;
            }
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                assert(mid != q.size() - 1);
                
                long long x1 = q[mid]; long long y1 = a[x1];
                long long x2 = q[mid + 1]; long long y2 = a[x2];
                long long x3 = qidx[x]; long long y3 = a[x3];
                
                if ((y3 - y1) * (x3 - x2) < (y3 - y2) * (x3 - x1)) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            int x1 = q[lo]; int y1 = a[x1];
            int x2 = qidx[x]; int y2 = a[x2];
            res[x] = make_pair(y2 - y1, x2 - x1);
        }
    }
}

void reverse() {
    for (int i = 0; i < n / 2; i++) {
        swap(a[i], a[n - 1 - i]);
        swap(res[i], res[n - 1 - i]);
        swap(qidx[i], qidx[n - 1 - i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] = 1000000000 - a[i];
        qidx[i] = n - 1 - qidx[i];
    }
}

int gcd(int a, int b) {
    if (a < b) { swap(a, b); }
    while (b > 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ifstream fin("falling.in");
    ofstream fout("falling.out");
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        fin >> qidx[i];
        qidx[i]--;
    }
    solve();
    reverse();
    solve();
    reverse();
    for (int i = 0; i < n; i++) {
        int g = gcd(res[i].first, res[i].second);
        if (g == 0) { fout << -1 << "\n"; } else{ fout << (res[i].first / g) << "/" << (res[i].second / g) << "\n"; }
    }
}
