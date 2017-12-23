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
#define MAXN 100000
#define MOD 1000000007
#define HASH 71

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, nearestDiffR[MAXN];
ll uniqueFactor[MAXN];
ll powHash[MAXN], powInvHash[MAXN];
string names[MAXN];
vector<pii> allSuffixes;
vector<vector<ll>> suffixHash;

struct substringGreater {
    bool operator()(const pii& p1, const pii& p2) const {
        int nameA = p1.S;
        int nameB = p2.S;
        int startA = p1.F;
        int startB = p2.F;
        int l = min(names[nameA].size() - startA, names[nameB].size() - startB);
        F0R(i, l) if(names[nameA][startA + i] != names[nameB][startB + i]) return names[nameA][startA + i] < names[nameB][startB + i];
        return names[nameA].size() - startA < names[nameB].size() - startB;
    }
};

ll modPow(ll a, ll p) {
    if(p == 0) return 1;
    if(p % 2 == 1) return (a * modPow(a, p - 1)) % MOD;
    ll sqrt = modPow(a, p >> 1);
    return SQ(sqrt) % MOD;
}

ll substringHash(int a, int s, int e) {
    ll h = suffixHash[a][s] - suffixHash[a][e] + MOD;
    h %= MOD;
    h *= powInvHash[names[a].size() - e];
    h %= MOD;
    return h;
}

int lcp(int a, int b) {
    if(a < 0 || a >= allSuffixes.size() || b < 0 || b >= allSuffixes.size()) return 0;
    int nameA = allSuffixes[a].S;
    int nameB = allSuffixes[b].S;
    int startA = allSuffixes[a].F;
    int startB = allSuffixes[b].F;
    int lo = -1, hi = min(names[nameA].size() - startA, names[nameB].size() - startB);
    while(lo < hi - 1) {
        int mid = (lo + hi) >> 1;
        if(substringHash(nameA, startA, startA + mid + 1) == substringHash(nameB, startB, startB + mid + 1)) lo = mid;
        else hi = mid;
    }
    return hi;
}

int main() {
    ifstream fin("standingout.in");
    ofstream fout("standingout.out");
    powHash[0] = powInvHash[0] = 1;
    powInvHash[1] = modPow(HASH, MOD - 2);
    FOR(i, 1, MAXN) powHash[i] = (HASH * powHash[i - 1]) % MOD;
    FOR(i, 2, MAXN) powInvHash[i] = (powInvHash[1] * powInvHash[i - 1]) % MOD;
    fin >> n;
    F0R(i, n) fin >> names[i];
    F0R(i, n) {
        ll h = 0;
        vector<ll> s;
        s.PB(0);
        string suffix = "";
        R0F(j, names[i].size()) {
            allSuffixes.PB(MP(j, i));
            h += (powHash[names[i].size() - 1 - j] * (names[i][j] - 'a' + 1)) % MOD;
            h %= MOD;
            s.PB(h);
        }
        reverse(s.begin(), s.end());
        suffixHash.PB(s);
    }
    sort(allSuffixes.begin(), allSuffixes.end(), substringGreater());
    nearestDiffR[allSuffixes.size() - 1] = allSuffixes.size();
    R0F(i, allSuffixes.size() - 1) nearestDiffR[i] = ((allSuffixes[i + 1].S == allSuffixes[i].S) ? nearestDiffR[i + 1] : i + 1);
    F0R(i, allSuffixes.size()) {
        int res = 0;
        res = max(res, lcp(i - 1, i));
        res = max(res, lcp(nearestDiffR[i], i));
        uniqueFactor[allSuffixes[i].S] += names[allSuffixes[i].S].size() - allSuffixes[i].F - res;
    }
    F0R(i, n) fout << uniqueFactor[i] << "\n";
    return 0;
}
