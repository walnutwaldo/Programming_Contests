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
typedef complex<ll> point;

int n, m, curr = 0;
bool included[1 << 19];
int hasStart[1 << 19];

void add(int a) {
    F0R(i, 19) {
        int firstI = a & ~((1 << (18 - i)) - 1);
        hasStart[firstI] |= (1 << i);
    }
}

int findClosest() {
    int soFar = 0;
    F0R(i, 19) {
        soFar |= (curr & (1 << (18 - i)));
        if(!(hasStart[soFar] & (1 << i))) soFar ^= (1 << (18 - i));
    }
    return soFar;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    F0R(i, n) {
        int a;
        cin >> a;
        included[a] = true;
    }
    F0R(i, 1 << 19) if(!included[i]) add(i);
    F0R(i, m) {
        int x;
        cin >> x;
        curr ^= x;
        cout << (findClosest() ^ curr) << "\n";
    }
    return 0;
}
close
