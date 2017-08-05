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
int sumToX[MAXN], sumToY[MAXN], numX, numY;
vector<pii> points;
map<int, vector<pii>> pointsAt;
map<int, int> compX, compY;

struct ST {

    int val = 0, lo, hi;
    ST *lchild, *rchild;

    ST(int lo, int hi) {
        this-> lo = lo;
        this-> hi = hi;
        lchild = NULL;
        rchild = NULL;
    }

    void update(int idx) {
        val += 1;
        if(lo == hi - 1) return;
        int mid = (hi + lo) >> 1;
        if(idx < mid) {
            if(lchild == NULL) lchild = new ST(lo, mid);
            lchild->update(idx);
        } else {
            if(rchild == NULL) rchild = new ST(mid, hi);
            rchild->update(idx);
        }
    }

    int query(int s, int e) {
        if(s == lo && e == hi) return val;
        int mid = (hi + lo) >> 1;
        int total = 0;
        if(lchild != NULL && s < mid) total += lchild->query(s, min(mid, e));
        if(rchild != NULL && e > mid) total += rchild->query(max(s, mid), e);
        return total;
    }
};

struct BIT {

    ST **tree;

    BIT() {
        tree = new ST*[numX + 1];
        F0R(i, numX + 1) tree[i] = new ST(0, numY);
    }

    void update(int x, int y) {
        for(x++; x <= numX; x += (x & -x)) tree[x]->update(y);
    }

    int query(int x, int y) {
        int total = 0;
        for(x++; x > 0; x -= (x & -x)) total += tree[x]->query(0, y + 1);
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
    sort(points.begin(), points.end());
    F0R(i, n) {
        points[i].F = compX[points[i].F];
        points[i].S = compY[points[i].S];
    }
    BIT bit;
    F0R(i, n) {
        int x = points[i].F;
        int y = points[i].S;
        bit.update(x, y);
        sumToX[x]++;
        sumToY[y]++;
    }
    FOR(x, 1, numX) sumToX[x] += sumToX[x - 1];
    FOR(y, 1, numY) sumToY[y] += sumToY[y - 1];
    int M = INT_MAX;
    F0R(x, numX) {
        int lo = 0, hi = numY;
        while(lo < hi) {
            int y = (lo + hi) >> 1;
            int ul = bit.query(x, y);
            int dl = sumToX[x] - ul;
            int ur = sumToY[y] - ul;
            int dr = n - ul - dl - ur;
            M = min(M, max(max(ul, ur), max(dl, dr)));
            if(ul + ur > dl + dr) {
                hi = y;
            } else {
                lo = y + 1;
            }
        }
    }
    fout << M << "\n";
    return 0;
}
