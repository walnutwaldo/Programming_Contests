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
#define MAXN 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, b;
vector<pii> points;

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> n >> b;
    set<int> xs, ys;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        points.PB(MP(x,y));
        xs.insert(x - 1);
        xs.insert(x + 1);
        ys.insert(y - 1);
        ys.insert(y + 1);
    }
    int M = INT_MAX;
    for(const int x: xs) {
        for(const int y: ys) {
            int inQuad[2][2] {{0, 0}, {0, 0}};
            for(const pii point: points) {
                int a, b;
                if(point.F < x) a = 0;
                else a = 1;
                if(point.S < y) b = 0;
                else b = 1;
                inQuad[a][b]++;
            }
            M = min(M, max(max(inQuad[0][0], inQuad[0][1]), max(inQuad[1][0], inQuad[1][1])));
        }
    }
    fout << M << "\n";
    return 0;
}
