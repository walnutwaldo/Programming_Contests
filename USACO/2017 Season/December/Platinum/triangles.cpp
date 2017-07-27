#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define FOR(i, a, b) for (int i = a; i < b; i++)
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)

#define MAXN 300
int n, answer[MAXN], under[MAXN][MAXN], occur[1000001];
vector<pii> points;

bool between(int k, int i,  int j) {
    int left = (points[i].first < points[j].first)? i : j;
    int right = (points[i].first < points[j].first)? j : i;
    return (points[k].first > points[left].first && points[k].first <= points[right].first);
}

bool betweenInc(int k, int i,  int j) {
    int left = (points[i].first < points[j].first)? i : j;
    int right = (points[i].first < points[j].first)? j : i;
    return (points[k].first >= points[left].first && points[k].first <= points[right].first);
}

bool below(int k, int i, int j) {
    int left = (points[i].first < points[j].first)? i : j;
    int right = (points[i].first < points[j].first)? j : i;

    if(!between(k, left, right))
        return false;
    ld expected = points[left].second + (ld)(points[right].second - points[left].second) * (points[k].first - points[left].first)/(points[right].first - points[left].first);
    if((ld) points[k].second < expected) {
        return true;
    }
    return false;
}

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");

    fin >> n;
    F0R(i,n) {
        int x, y;
        fin >> x >> y;
        points.push_back({x, y});
        occur[x]++;
    }

    F0R(i, n) FOR(j, i+1, n) F0R(k,n) {
        if(k == i || k== j) {
            continue;
        }
        if(below(k,i,j)) {
            under[i][j]++;
            under[j][i]++;
        }
    }

    F0R(i, n) FOR(j, i+1, n) FOR(k, j+1,n) {
        if(betweenInc(i,j,k)) {
            int temp = i;
            i = k;
            k = temp;
        } else if(betweenInc(j,i,k)) {
            int temp = j;
            j = k;
            k = temp;
        }
        int left = (points[i].first < points[j].first)? i : j;
        int right = (points[i].first < points[j].first)? j : i;
        if(below(k,j,i))
            answer[under[left][right] - under[k][right] - under[left][k] + occur[points[k].first] - 1]++;
        else
            answer[under[left][k] + under[k][right] - under[left][right] - occur[points[k].first] + 1]++;
    }

    F0R(i, n - 2)
    cout << answer[i] << "\n";

    return 0;
}
