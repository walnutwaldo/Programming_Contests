#include <bits/stdc++.h>

#define PI acos(-1)

using namespace std;

#define MAXN 50000

int n, r;
set<long double> s;

long double bringInRange(long double angle) {
    while (angle < 0) { angle += 2 * PI; }
    while (angle >= 2 * PI) { angle -= 2 * PI; }
    return angle;
}

int main() {
    ifstream cin("sight.in");
    ofstream cout("sight.out");
    cin >> n >> r;
    vector<pair<long double, long double>> vec;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        long double dis = sqrt((long double)(x * x + y * y));
        long double arg = atan2(y, x);
        long double angle = acos(r / dis);
        
        long double inAngle = bringInRange(arg - angle);
        long double outAngle = bringInRange(arg + angle);
        if (inAngle > outAngle) {
            s.insert(outAngle);
            vec.emplace_back(inAngle, outAngle + 2 * PI);
        } else {
            vec.emplace_back(inAngle, outAngle);
        }
    }
    long long res = 0;
    sort(vec.begin(), vec.end());
    for (const pair<long double, long double> p : vec) {
        double angle = p.first;
        while (!s.empty() && *s.begin() < angle) {
            s.erase(s.begin());
        }
        res += s.size();
        s.insert(p.second);
    }
    cout << res << endl;
    return 0;
}
