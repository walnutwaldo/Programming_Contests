#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define X real()
#define Y imag()
#define R real()
#define I image()
#define PI acos(-1)
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;
typedef complex<ld> cld;

int n, k, dfe[MAXN];
bool solved[MAXN];
vi connections[MAXN];

int solve(int node, int moves, int last = -1) {
    if(dfe[node] <= moves) return 1;
    int res = 0;
    for(const int next : connections[node]) if(next != last) res += solve(next, moves + 1, node);
    return res;
}

int main() {
    ifstream fin("atlarge.in");
    ofstream fout("atlarge.out");
    fin >> n >> k;
    k--;
    F0R(i, n - 1) {
        int a, b;
        fin >> a >> b;
        a--, b--;
        connections[a].PB(b);
        connections[b].PB(a);
    }
    vi q;
    F0R(i, n) if(connections[i].size() == 1) q.PB(i), solved[i] = 1;
    F0R(i, n) for(const int next : connections[q[i]]) if(!solved[next]) {
            dfe[next] = dfe[q[i]] + 1;
            solved[next] = 1;
            q.PB(next);
        }
    fout << solve(k, 0) << "\n";
    return 0;
}
