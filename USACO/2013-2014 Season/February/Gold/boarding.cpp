#include <bits/stdc++.h>
#include <ext/pd_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace pb_ds;

typedef tree<
        int,
        null_mapped_type,
        less<int>,
        rb_tree_tag,
        // This policy updates nodes' metadata for order statistics.
        tree_order_statistics_node_update>
    set_t;

int n, s[200000];
long long t[200000];

int main() {
    ifstream cin("boarding.in");
    ofstream cout("boarding.out");
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
        s[i]--;
    }
    set_t s;
    for (int i = 1; i <= n; i++) { s.insert(i); }
    long long res = 0;
    for (int i = n - 1; i >= 0; i--) {
        int walktime = s[i] + n - i;
        long long bq = bit.query(walktime);
        res = max(res, bq + walktime + t[i]);
        bit.update(walktime + 1, bq + t[i]);
    }
    cout << res << endl;
    return 0;
}
