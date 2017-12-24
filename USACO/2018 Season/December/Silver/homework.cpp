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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
ll score[MAXN];

int main() {
    ifstream fin("homework.in");
    ofstream fout("homework.out");
    fin >> n;
    F0R(i, n) fin >> score[i];
    ll minScore = score[n - 1];
    ld total = score[n - 1], maxAvg = 0;
    vi res;
    ROF(i, 1, n - 1) {
        total += score[i];
        minScore = min(minScore, score[i]);
        ld avg = (ld)(total - minScore) / (n - 1 - i);
        if(avg > maxAvg) {
            res.clear();
            maxAvg = avg;
        }
        if(avg == maxAvg) res.PB(i);
    }
    reverse(res.begin(), res.end());
    for(const int i : res) fout << i << "\n";
    return 0;
}
