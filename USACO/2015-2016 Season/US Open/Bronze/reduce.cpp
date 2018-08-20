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

int n;

int main() {
    ifstream fin("reduce.in");
    ofstream fout("reduce.out");
    fin >> n;
    priority_queue<pii, vector<pii>, greater<pii>> minX;
    priority_queue<pii, vector<pii>, greater<pii>> minY;
    priority_queue<pii> maxX;
    priority_queue<pii> maxY;
    F0R(i, n) {
        int x, y;
        fin >> x >> y;
        minX.push(MP(x, i));
        maxX.push(MP(x, i));
        minY.push(MP(y, i));
        maxY.push(MP(y, i));
    }
    int res = -1;
    F0R(i, n) {
        pii minXP = {0, 0}, maxXP = {0, 0}, minYP = {0, 0}, maxYP = {0, 0};
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
        int area = (maxX.top().F - minX.top().F) * (maxY.top().F - minY.top().F);
        if(minXP != MP(0, 0)) minX.push(minXP);
        if(maxXP != MP(0, 0)) maxX.push(maxXP);
        if(maxYP != MP(0, 0)) maxY.push(maxYP);
        if(minYP != MP(0, 0)) minY.push(minYP);
        if(res == -1 || area < res) res = area;
    }
    fout << res << "\n";
    return 0;
}
