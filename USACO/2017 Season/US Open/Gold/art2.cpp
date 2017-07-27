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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, color[MAXN + 1], last[MAXN + 1];
bool seen[MAXN + 1];

int main() {
    ifstream fin("art2.in");
    ofstream fout("art2.out");

    fin >> n;
    FOR(i, 1, n + 1) {
        fin >> color[i];
        last[color[i]] = i;
    }
    bool on[n + 1];
    int numOn = 0;
    memset(on, 0, (n + 1) * sizeof(bool));
    on[0] = true;
    stack<int> s;
    s.push(0);
    int maxLayers = 0;
    FOR(i, 1, n + 1) {
        if(on[color[i]] && s.top() != color[i]) {
            fout << -1 << endl;
            return 0;
        }
        if(!on[color[i]]) {
            on[color[i]] = true;
            s.push(color[i]);
            numOn++;
        }
        maxLayers = max(maxLayers, numOn);
        if(color[i] != 0 && i == last[color[i]]) {
            on[color[i]] = false;
            s.pop();
            numOn--;
        }
    }
    seen[0] = true;
    fout << maxLayers << endl;
    return 0;
}
