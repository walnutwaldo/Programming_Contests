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
vector<ll*> points;

bool isGood(int i, int a, int b) {
    ll total = 0;
    F0R(j, 5) total += (points[a][j] - points[i][j]) * (points[b][j] - points[i][j]);
    if(total > 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    F0R(i, n) {
        ll* a =  new ll[5];
        cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];
        points.PB(a);
    }
    if(n == 1) cout << "1\n1\n";
    else if(n == 2) cout << "2\n1\n2\n";
    else {
        int v;
        int curr = 3;
        if(isGood(0, 1, 2)) v = 0;
        else if(isGood(2, 0, 1)) v = 2;
        else v = 1;
        while(curr < n) {
            if(isGood(curr, v, 0)) v = curr;
            curr++;
        }
        F0R(a, n) FOR(b, a + 1, n) {
            if(a == v || b == v) continue;
            if(!isGood(v, a, b)) {
                cout << "0\n";
                return 0;
            }
        }
        cout << "1\n" << v + 1 << "\n";
    }
    return 0;
}
