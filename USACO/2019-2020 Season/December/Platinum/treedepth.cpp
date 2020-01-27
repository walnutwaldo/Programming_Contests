#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 300

int n, k;
ll m, ans[MAXN];
vector<ll> poly[MAXN], invPoly[MAXN];

vector<ll> polymult(vector<ll>& v, int a) {
    vector<ll> res;
    vector<ll> pref;
    for (int i = 0; i < v.size(); i++) {
        pref.push_back((v[i] + (i ? pref[i - 1] : 0)) % m);
    }
    for (int i = 0; i < v.size() + a - 1; i++) {
        int l = max(0, i - a + 1);
        int r = min((int)v.size() - 1, i);
        res.push_back((pref[r] + m - (l ? pref[l - 1] : 0)) % m);
    }
    return res;
}

ll getV(vector<ll>& v, int p) {
    if (p < 0) { return 0; }
    if (p >= v.size()) { return 0; }
    return v[p];
}

ll prodCoeff(int i, int j, int p) {
    if (i < 0) {
        return getV(invPoly[j], p);
    }
    if (j >= n) {
        return getV(poly[i], p);
    }
    ll res = 0;
    for (int x = 0; x <= p; x++) {
        res += getV(poly[i], x) * getV(invPoly[j], p - x) % m;
        res %= m;
    }
    return res;
}

int main() {
    ifstream cin("treedepth.in");
    ofstream cout("treedepth.out");
    cin >> n >> k >> m;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    poly[0] = vector<ll>(1, 1);
    for (int i = 1; i < n; i++) { poly[i] = polymult(poly[i - 1], i + 1); }
    
    invPoly[n - 1] = vector<ll>(n, 1);
    for (int i = n - 2; i >= 0; i--) { invPoly[i] = polymult(invPoly[i + 1], i + 1); }
    
    for (int den = 0; den < n; den++) {
        ll leftVal = prodCoeff(den - 1, den + 1, k);
        for (int i = den; i < n; i++) {
            ans[i] = (ans[i] + leftVal) % m;
        }
        if (den) {
            ll rightVal = prodCoeff(den - 1, den + 1, k - den);
            for (int i = 0; i < n - den; i++) {
                ans[i] = (ans[i] + rightVal) % m;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i];
        if (i < n - 1) { cout << " "; }
    }
    cout << endl;
}
