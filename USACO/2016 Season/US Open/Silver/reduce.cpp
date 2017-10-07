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
#define X real()
#define Y imag()

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ld> point;

int n, res = -1;

priority_queue<pii, vector<pii>, greater<pii>> minX;
priority_queue<pii, vector<pii>, greater<pii>> minY;
priority_queue<pii> maxX;
priority_queue<pii> maxY;

void solve(int depth);

void actRemove(int depth, int i) {
    pii nothing = {0, 0};
    pii minXP = nothing, maxXP = nothing, minYP = nothing, maxYP = nothing;
    if(minX.top().S == i) {
        minXP = minX.top();
        minX.pop();
    }
    if(maxX.top().S == i) {
        maxXP = maxX.top();
        maxX.pop();
    }
    if(minY.top().S == i) {
        minYP = minY.top();
        minY.pop();
    }
    if(maxY.top().S == i) {
        maxYP = maxY.top();
        maxY.pop();
    }
    solve(depth);
    if(minXP != nothing) minX.push(minXP);
    if(maxXP != nothing) maxX.push(maxXP);
    if(minYP != nothing) minY.push(minYP);
    if(maxYP != nothing) maxY.push(maxYP);
}

void solve(int depth) {
    if(depth == 3) {
        int area = (maxX.top().F - minX.top().F) * (maxY.top().F - minY.top().F);
        if(res == -1 || area < res) res = area;
        return;
    }
    actRemove(depth + 1, minX.top().S);
    actRemove(depth + 1, maxX.top().S);
    actRemove(depth + 1, minY.top().S);
    actRemove(depth + 1, maxY.top().S);
}

int main() {
    ifstream fin("reduce.in");
    ofstream fout("reduce.out");
    fin >> n;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        minX.push(MP(x, i));
        maxX.push(MP(x, i));
        minY.push(MP(y, i));
        maxY.push(MP(y, i));
    }
    solve(0);
    fout << res << "\n";
    return 0;
}
