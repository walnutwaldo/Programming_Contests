#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define F0R(i, a) for(int i = 0; i < a; i++)

#define MAXN 50000

int N;
ll res = 1e18+1, maximumArea, maxLeft[MAXN], maxRight[MAXN], minLeft[MAXN], minRight[MAXN];
pair<ll,ll> points[MAXN];

void invert() {
    F0R(i, N) {
        points[i] = {points[i].second, points[i].first};
    }
    sort(points, points + N);
    maximumArea *= (points[N - 1].first - points[0].first);
}

void solve() {
    F0R(i, N) {
        if(i == 0) {
            maxLeft[i] = points[i].second;
            minLeft[i] = points[i].second;
            maxRight[N - 1 - i]
                = points[N - 1 - i].second;
            minRight[N - 1 - i] = points[N - 1 - i].second;
        } else {
            maxLeft[i] = max(maxLeft[i - 1], points[i].second);
            minLeft[i] = min(minLeft[i - 1], points[i].second);
            maxRight[N - 1 - i] = max(maxRight[N - i], points[N - 1 - i].second);
            minRight[N - 1 - i] = min(minRight[N - i], points[N - 1 - i].second);
        }
    }
    F0R(i, N - 1) {
        ll area1 = (points[i].first - points[0].first) * (maxLeft[i] - minLeft[i]);
        ll area2 = (points[N - 1].first - points[i + 1].first) * (maxRight[i + 1] - minRight[i + 1]);
        if(points[i].first == points[i+1].first)
            continue;
        else
            res = min(res, area1 + area2);
    }
}

int main() {
    ifstream fin("split.in");
    ofstream fout("split.out");
    fin >> N;
    F0R(i, N) {
        ll x,y;
        fin >> x >> y;
        points[i] = {x,y};
    }
    sort(points, points + N);
    maximumArea = points[N - 1].first - points[0].first;
    solve();
    invert();
    solve();
    fout << (maximumArea - res);
    return 0;
}
