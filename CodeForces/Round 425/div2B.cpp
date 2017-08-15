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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

bool good[26], foundStar;
string pattern, goodCharacters, queries[MAXN];
int beforeStar, afterStar, q;

bool possible(string query, int l, int starCover) {
    if(starCover < 0 || (starCover > 0 && !foundStar)) return false;
    F0R(j, beforeStar) {
        if(pattern[j] == '?' && !good[(int)(query[j] - 'a')]) return false;
        if(pattern[j] != '?' && query[j] != pattern[j]) return false;
    }
    F0R(j, starCover) {
        if(good[(int)(query[beforeStar + j] - 'a')]) return false;
    }
    F0R(j, afterStar) {
        if(pattern[1 + beforeStar + j] == '?' && !good[(int)(query[beforeStar + starCover + j] - 'a')]) return false;
        if(pattern[1 + beforeStar + j] != '?' && query[beforeStar + starCover + j] != pattern[1 + beforeStar + j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> goodCharacters;
    F0R(i, goodCharacters.length()) good[goodCharacters[i] - 'a'] = true;
    cin >> pattern;
    F0R(i, pattern.length()) {
        if(pattern[i] == '*') {
            foundStar = true;
        } else {
            if(!foundStar) beforeStar++;
            else afterStar++;
        }
    }
    cin >> q;
    F0R(i, q) cin >> queries[i];
    F0R(i, q) {
        int l = queries[i].length();
        int starCover = l - beforeStar - afterStar;
        if(possible(queries[i], l, starCover)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
