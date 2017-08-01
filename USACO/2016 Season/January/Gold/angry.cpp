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

int n;
ll bales[MAXN], neededF[MAXN], neededB[MAXN];

bool works(ld r) {
    F0R(i, n) {
        if(neededF[i] <= r && neededB[i] <= r) return true;
        ll otherEnd = bales[i] + 2 * r;
        int j = UB(bales, bales + n, otherEnd) - bales - 1;
        if(neededF[i] <= r - 1 && neededB[j] <= r - 1)
            return true;
    }
    return false;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");
    fin >> n;
    F0R(i, n) fin >> bales[i];
    sort(bales, bales + n);

    neededF[0] = 0;
    priority_queue<pii, vector<pii>,greater<pii>> pq;
    FOR(i, 1, n) {
        while(!pq.empty()) {
            int powNeeded = pq.top().F + 1;
            int disNeeded = bales[i] - bales[pq.top().S];
            if(disNeeded > powNeeded) {
                pq.pop();
                continue;
            }
            break;
        }
        if(pq.empty()) neededF[i] = max(bales[i] - bales[i - 1], neededF[i - 1] + 1);
        else neededF[i] = pq.top().F + 1;
        pq.push(MP(neededF[i], i));
    }

    neededB[n - 1] = 0;
    pq = priority_queue<pii, vector<pii>,greater<pii>>();
    R0F(i, n - 1) {
        while(!pq.empty()) {
            int powNeeded = pq.top().F + 1;
            int disNeeded = bales[pq.top().S] - bales[i];
            if(disNeeded > powNeeded) {
                pq.pop();
                continue;
            }
            break;
        }
        if(pq.empty()) neededB[i] = max(bales[i + 1] - bales[i], neededB[i + 1] + 1);
        else neededB[i] = pq.top().F + 1;
        pq.push(MP(neededB[i], i));
    }

    ld lo = 0;
    ld hi = 1000000000;
    F0R(i, 50) {
        ld mid = (lo + hi) / 2;
        if(works(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    fout << fixed << setprecision(1);
    fout << round(lo * 10) / 10 << endl;
    return 0;
}
