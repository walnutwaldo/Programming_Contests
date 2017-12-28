#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define rand31() ((rand() << 16) | (rand() << 1) | (rand() & 1))
#define rand32() ((rand() << 17) | (rand() << 2) | (rand() & 3))
#define rand63() (((ll)rand() << 48) | ((ll)rand() << 33) | ((ll)rand() << 18) | ((ll)rand() << 3) | ((ll)rand() & 7))
#define rand64() (((ll)rand() << 49) | ((ll)rand() << 34) | ((ll)rand() << 19) | ((ll)rand() << 4) | ((ll)rand() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MAXN 1000
#define MAXK 7

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;
ll r[MAXN];
ll dp[MAXK][MAXN], q[MAXN], p[MAXN];

struct Partial {

    ll base;
    int start;

    Partial(ll bb, int ss) {
        base = bb, start = ss;
    }

    ll valueAt(int x) {
        return base - p[start] + p[x] - start * q[x] + start * q[start];
    }

    ll qBeatenBy(Partial p2) {
        ll b1 = base - p[start] + start * q[start];
        ll b2 = p2.base - p[p2.start] + p2.start * q[p2.start];
        int a1 = -start;
        int a2 = -p2.start;
        ll numerator = b1 - b2;
        int denominator = a2 - a1;
        if(numerator % denominator == 0) return numerator / denominator;
        else return numerator / denominator + 1;
    }

};

ll solveLinear() {
    q[0] = 0, p[0] = 0;
    F0R(i, n) {
        if(i > 0) q[i] = q[i - 1], p[i] = p[i - 1];
        q[i] += r[i], p[i] += i * r[i];
    }
    F0R(i, n) dp[0][i] = p[i];
    FOR(d, 1, k) {
        int fptr = 0;
        vector<Partial> hull;
        FOR(i, d, n) {
            Partial part(dp[d - 1][i - 1], i);
            while(hull.size() - fptr > 1 && hull[hull.size() - 1].qBeatenBy(part) <= hull[hull.size() - 2].qBeatenBy(part)) hull.pop_back();
            hull.PB(part);
            while(hull.size() - fptr > 1 && hull[fptr].valueAt(i) >= hull[fptr + 1].valueAt(i)) fptr++;
            dp[d][i] = hull[fptr].valueAt(i);
        }
    }
    return dp[k - 1][n - 1];
}

void rot() {
    ll temp = r[0];
    F0R(i, n) r[i] = r[i + 1];
    r[n - 1] = temp;
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> n >> k;
    F0R(i, n) fin >> r[i];
    ll res = 1e15;
    F0R(i, n) {
        res = min(res, solveLinear());
        rot();
    }
    fout << res << "\n";
    return 0;
}
