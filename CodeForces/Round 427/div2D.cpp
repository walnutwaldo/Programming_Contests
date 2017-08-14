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

string s;
int numStrings[5001];
bool isP[5000][5000];
int palindromeRank[5000][5000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    FOR(length, 1, s.size() + 1) {
        F0R(start, s.size() - length + 1) {
            if(length == 1) isP[start][start + length - 1] = true;
            if(length == 2) isP[start][start + length - 1] = (s[start] == s[start + 1]);
            if(length > 2) isP[start][start + length - 1] = (s[start] == s[start + length - 1]) && isP[start + 1][start + length - 2];
            if(isP[start][start + length - 1]) palindromeRank[start][start + length - 1] = 1 + palindromeRank[start][start + (length / 2) - 1];
            numStrings[palindromeRank[start][start + length - 1]]++;
        }
    }
    ROF(i, 1, s.size()) numStrings[i] += numStrings[i + 1];
    FOR(i, 1, s.size() + 1) cout << numStrings[i] << " ";
    cout << "\n";
    return 0;
}
