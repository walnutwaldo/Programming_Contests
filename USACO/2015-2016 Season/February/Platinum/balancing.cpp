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
int numX, numY;
vector<pii> points;
unordered_map<int, int> compX, compY;

struct ST {

    int ups;
    int *tree;

    ST(int s) {
        ups = exp2(ceil(log2(s)));
        tree = new int[2 * this->ups];
        memset(tree, 0, (2 * this->ups) * sizeof(int));
    }

    void update(int idx, int v) {
        idx += ups;
        while(idx > 0) {
            tree[idx]+= v;
            idx/= 2;
        }
    }

    int query(int lo, int hi) {
        lo += ups;
        hi += ups;
        int total = 0;
        while(lo <= hi) {
            if(lo % 2 == 1) total += tree[lo++];
            if(hi % 2 == 0) total += tree[hi--];
            lo/=2;
            hi/=2;
        }
        return total;
    }

};

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> n;
    set<int> xs, ys;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        points.PB(MP(x,y));
        xs.insert(x);
        ys.insert(y);
    }
    numX = xs.size();
    numY = ys.size();
    F0R(i, numX) {
        compX[*(xs.begin())] = i;
        xs.erase(*xs.begin());
    }
    F0R(i, numY) {
        compY[*(ys.begin())] = i;
        ys.erase(*ys.begin());
    }
    F0R(i, n) {
        points[i].F = compX[points[i].F];
        points[i].S = compY[points[i].S];
    }
    vi atX[numX];
    vi atY[numY];
    F0R(i, numX) atX[i] = vi();
    F0R(i, numY) atY[i] = vi();
    ST l(numY), r(numY);
    F0R(i, n) {
        int x = points[i].F;
        int y = points[i].S;
        atX[x].PB(y);
        atY[y].PB(x);
        r.update(y, 1);
    }
    int M = -1;
    F0R(x, numX) {
        for(const int y : atX[x]) {
            r.update(y, -1);
            l.update(y, 1);
        }
        int lo = 0, hi = numY;
        while(lo < hi) {
            int y = (lo + hi) >> 1;
            int ul = l.query(0, y);
            int dl = l.query(y + 1, numY - 1);
            int ur = r.query(0, y);
            int dr = r.query(y + 1, numY - 1);
            int greatestQuad = max(max(ul, ur), max(dl, dr));
            if(M == -1 || greatestQuad < M) M = greatestQuad;
            if(greatestQuad == ul || greatestQuad == ur) {
                hi = y;
            } else {
                lo = y + 1;
            }
        }
    }
    fout << M << "\n";
    return 0;
}
