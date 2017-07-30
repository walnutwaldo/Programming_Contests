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
#define MAXN 50000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll n, num[MAXN], tmod7, l[7], r[7];

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");
    fin >> n;
    F0R(i, n) {
        fin >> num[i];
        tmod7 = (tmod7 + num[i]) % 7;
    }
    F0R(i, 7) {
        l[i] = -1;
        r[i] = -1;
    }
    int sumMod7 = 0;
    l[0] = 0;
    r[0] = 0;
    F0R(i, n) {
        sumMod7 = (sumMod7 + num[i]) % 7;
        if(l[sumMod7] == -1) l[sumMod7] = i + 1;
    }
    sumMod7 = 0;
    F0R(i, n) {
        sumMod7 = (sumMod7 + num[n - 1 - i]) % 7;
        if(r[sumMod7] == -1) r[sumMod7] = i + 1;
    }
    ll maxLength = 0;
    F0R(i, 7) {
        int extraNeeded = (tmod7 - i + 7) % 7;
        if(r[i] != -1 && l[extraNeeded] != -1) maxLength = max(maxLength, n - r[i] - l[extraNeeded]);
    }
    fout << maxLength << "\n";
    return 0;
}
