#include <bits/stdc++.h>

using namespace std;

int n, a[501];

bool possible(int excl) {
    vector<int> v;
    for (int i = 0; i < n + 1; i++) { if (i != excl) { v.push_back(a[i]); } }
    sort(v.begin(), v.end());
    while (!v.empty()) {
        vector<int> tmp(v);
        v.clear();
        int t = tmp.back();
        if (t == 0) { break; }
        if (t > tmp.size() - 1 || tmp[tmp.size() - 1 - t] == 0) { return false; }
        int i = tmp.size() - 1 - t;
        int j = 0;
        while (i < tmp.size() - 1 || j < tmp.size() - 1 - t) {
            if (j == tmp.size() - 1 - t || (i < tmp.size() - 1 && tmp[i] - 1 < tmp[j])) {
                v.push_back(tmp[i++] - 1);
            } else { v.push_back(tmp[j++]); }
        }
    }
    return true;
}

int main() {
    ifstream cin("fcount.in");
    ofstream cout("fcount.out");
    cin >> n;
    for (int i = 0; i < n + 1; i++) {
        cin >> a[i];
    }
    vector<int> res;
    for (int i = 0; i < n + 1; i++) {
        if (possible(i)) {
            res.push_back(i + 1);
        }
    }
    cout << res.size() << "\n";
    for (const int i : res) { cout << i << "\n"; }
    return 0;
}
