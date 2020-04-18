#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define MAXN 7500

int n;
ull m;
ull fact[MAXN + 1];
bool comp[MAXN + 1];

ull madd(ull a, ull b) { return (a + b) % m; }

ull msub(ull a, ull b) { return (a + m - b) % m; }

ull mmult(ull a, ull b) { return a * b % m; }

ull modpow(ull a, ull p) {
    return p ? ((p & 1) ? mmult(a, modpow(a, p ^ 1)) : modpow(mmult(a, a), p >> 1)) : 1;
}

ull without(int z) {
    ull res = 1;
    for (int i = 1; i <= n; i++) {
        if (i % z) { res = res * i % (m - 1); } else{ res = res * (i - 1) % (m - 1); }
    }
    return res;
}

ull with(int z) {
    return (fact[n] + m - 1 - without(z)) % (m - 1);
}

int main() {
    ifstream fin("exercise.in");
    ofstream fout("exercise.out");
    fin >> n >> m;
    fact[0] = 1;
    for (int i = 1; i <= n; i++) { fact[i] = fact[i - 1] * i % (m - 1); }
    ull res = 1;
    for (int i = 2; i <= n; i++) {
        if (!comp[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                comp[j] = true;
            }
            for (int x = i; x <= n; x *= i) {
                res = mmult(res, modpow(i, with(x)));
            }
        }
    }
    fout << res << endl;
}
