#include <bits/stdc++.h>

using namespace std;

int n;
long long t;

int main() {
    ifstream fin("cowjog.in");
    ofstream fout("cowjog.out");
    fin >> n >> t;
    vector<pair<long long, long long>> vec;
    for (int i = 0; i < n; i++) {
        long long p, s;
        fin >> p >> s;
        long long v = p + s * t;
        vec.emplace_back(v, -p);
    }
    sort(vec.begin(), vec.end());
    set<long long> front;
    int res = 0;
    for (int i = 0; i < n; i++) {
        long long v = -vec[i].second;
        auto ptr = front.lower_bound(v);
        if (ptr != front.begin()) {
            ptr--;
            front.erase(ptr);
        } else { res++; }
        front.insert(v);
    }
    fout << res << endl;
    fout.close();
    return 0;
}
