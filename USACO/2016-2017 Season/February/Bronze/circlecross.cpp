#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (a) - 1; i >= (b); i--)

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int first[26], last[26];

int main() {
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");
    FOR(i, 1, 53) {
        char c;
        fin >> c;
        if(first[c - 'A'] == 0) {
            first[c - 'A'] = i;
        } else {
            last[c - 'A'] = i;
        }
    }
    int num = 0;
    F0R(i, 26) {
        F0R(j, 26) {
            if(first[j] > first[i] && first[j] < last[i] && last[j] > last[i]) num++;
        }
    }
    fout << num << endl;
    return 0;
}
