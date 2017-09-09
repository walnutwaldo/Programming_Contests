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

int firstHalf[3], secondHalf[3], firstSum, secondSum;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    F0R(i, 3) {
        char c;
        cin >> c;
        firstHalf[i] = c - '0';
        firstSum += firstHalf[i];
    }
    F0R(i, 3) {
        char c;
        cin >> c;
        secondHalf[i] = c - '0';
        secondSum += secondHalf[i];
    }
    if(secondSum < firstSum) {
        F0R(i, 3) swap(firstHalf[i], secondHalf[i]);
        swap(firstSum, secondSum);
    }
    int diff = secondSum - firstSum;
    vi changes;
    F0R(i, 3) changes.PB(9 - firstHalf[i]);
    F0R(i, 3) changes.PB(secondHalf[i]);
    sort(changes.rbegin(), changes.rend());
    int change = 0;
    while(diff > 0) {
        diff -= changes[change];
        change++;
    }
    cout << change << "\n";
    return 0;
}
