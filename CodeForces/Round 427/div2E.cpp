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

int n, x, y, answer1, answer2;
bitset<1000> possible;

int binSearch() {
    int c = possible.count();
    if(c == 1) {
        F0R(i, n) if(possible[i]) {
            return i;
        }
    }
    int used = 0;
    int curr = 0;
    bitset<1000> possible2;
    while(curr < n) {
        if(used < c/2 && possible[curr]) {
            possible2[curr] = 1;
            used++;
        } else {
            possible2[curr] = 0;
        }
        curr++;
    }
    int expected;
    if(possible2.count() % 2 == 0) expected = 0;
    else expected = x;
    cout << "? " << possible2.count();
    F0R(i, n) {
        if(possible2[i]) cout << " " << (i + 1);
    }
    cout << endl;
    int actual;
    cin >> actual;
    if(actual == expected) {
        possible &= (~possible2);
    } else {
        possible &= possible2;
    }
    binSearch();
}

void work(int step) {
    bitset<1000> curr;
    F0R(i, n) {
        if(i % (2 * step) < step) curr[i] = 1;
    }
    int expected;
    if(curr.count() % 2 == 0) expected = 0;
    else expected = x;
    cout << "? " << curr.count();
    F0R(i, n) {
        if(curr[i]) cout << " " << (i + 1);
    }
    cout << endl;
    int actual;
    cin >> actual;
    if(actual == expected) {
        work(step / 2);
        if(curr[answer1]) possible &= curr;
        else possible &= (~curr);
    } else {
        possible = curr;
        answer1 = binSearch();
        possible = (~curr);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> x >> y;
    work(exp2(ceil(log2(n)) - 1));
    answer2 = binSearch();
    cout << "! " << min(answer1, answer2) + 1 << " " << max(answer1, answer2) + 1 << endl;
    return 0;
}
