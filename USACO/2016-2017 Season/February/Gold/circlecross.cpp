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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int first[26], second[26], cowAt[52];

int main() {
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");

    F0R(i, 26) first[i] = second[i] = -1;
    F0R(i, 52) {
        char c;
        fin >> c;
        cowAt[i] = (int)(c - 'A');
        if(first[cowAt[i]] == -1)
            first[cowAt[i]] = i;
        else
            second[cowAt[i]] = i;
    }
    int res = 0;
    F0R(i, 26) {
        int numOn = 0;
        bool in[26];
        F0R(j, 26) in[j] = false;
        FOR(j, first[i] + 1, second[i]) {
            if(!in[cowAt[j]]) {
                in[cowAt[j]] = true;
                numOn++;
            } else {
                in[cowAt[j]] = false;
                numOn--;
            }
        }
        res += numOn;
    }
    fout << (res / 2) << endl;
    return 0;
}
