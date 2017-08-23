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

vi L, R;
int digits;
ll answer = 0;

bool works(int* toTry, int pos, bool equalL, bool equalR) {
    if(pos == digits) return true;
    bool work = false;
    if(equalL && equalR) {
        if(L[pos] == R[pos]) {
            if(toTry[L[pos]] > 0) {
                toTry[L[pos]]--;
                work = works(toTry, pos + 1, true, true);
                toTry[L[pos]]++;
            }
        } else {
            FOR(nextDigits, L[pos] + 1, R[pos]) if(toTry[nextDigits]) return true;
            if(toTry[L[pos]] > 0) {
                toTry[L[pos]]--;
                work = works(toTry, pos + 1, true, false);
                toTry[L[pos]]++;
            }
            if(work) return true;
            if(toTry[R[pos]] > 0) {
                toTry[R[pos]]--;
                work = works(toTry, pos + 1, false, true);
                toTry[R[pos]]++;
            }
        }
    } else if(equalL) {
        FOR(nextDigit, L[pos] + 1, 10) if(toTry[nextDigit]) return true;
        if(toTry[L[pos]] > 0) {
            toTry[L[pos]]--;
            work = works(toTry, pos + 1, true, false);
            toTry[L[pos]]++;
        }
    } else {
        FOR(nextDigit, 0, R[pos]) if(toTry[nextDigit]) return true;
        if(toTry[R[pos]] > 0) {
            toTry[R[pos]]--;
            work = works(toTry, pos + 1, false, true);
            toTry[R[pos]]++;
        }
    }
    return work;
}

void genPossibilities(int* curr, int last, int numDigits) {
    if(numDigits == digits) {
        if(last != 0) {
            if(works(curr, 0, true, true)) {
                answer++;
            }
        }
        return;
    }
    FOR(nextDigit, last, 10) {
        curr[nextDigit]++;
        genPossibilities(curr, nextDigit, numDigits + 1);
        curr[nextDigit]--;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string l, r;
    cin >> l >> r;
    digits = r.size();
    int* startingState = new int[10] {0};
    if(digits == 19) {
        digits--;
        if(l.size() == 19) {
            cout << "1\n";
            return 0;
        }
        FOR(i, l.size(), digits) L.PB(0);
        for(const char c : l) L.PB(c - '0');
        for(const char c : r) R.PB(9);
        startingState[0]++;
    } else {
        FOR(i, l.size(), digits) L.PB(0);
        for(const char c : l) L.PB(c - '0');
        for(const char c : r) R.PB(c - '0');
    }
    genPossibilities(startingState, 0, 0);
    cout << answer;
    return 0;
}
