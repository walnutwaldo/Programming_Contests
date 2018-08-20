#include <bits/stdc++.h>

#define SQ(a) (a)*(a)

#define F0R(i, a) for(int i = 0; i < (a); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define R0F(i, a) for(int i = (a) - 1; i >= 0; i--)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); i--)

#define ran() (rand() & 0x7FFF)
#define rand31() ((ran() << 16) | (ran() << 1) | (ran() & 1))
#define rand32() ((ran() << 17) | (ran() << 2) | (ran() & 3))
#define rand63() (((ll)ran() << 48) | ((ll)ran() << 33) | ((ll)ran() << 18) | ((ll)ran() << 3) | ((ll)ran() & 7))
#define rand64() (((ll)ran() << 49) | ((ll)ran() << 34) | ((ll)ran() << 19) | ((ll)ran() << 4) | ((ll)ran() & 15))

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define UB upper_bound
#define LB lower_bound
#define MOD 1000000007
#define MAXLINES 100

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct StringTokenizer {

    int ptr = 0;
    string s;

    void takeString(string ss) {
        s = ss;
        ptr = 0;
    }

    string nextToken() {
        if(ptr == s.size()) return "";
        string token = "";
        while(ptr < s.size() && s[ptr] == ' ') ptr++;
        if(ptr == s.size()) return "";
        while(ptr < s.size() && s[ptr] != ' ') token += s[ptr++];
        return token;
    }

};

struct Matrix {

    int rows, columns;
    ll **mat;

    Matrix() {
        rows = 0, columns = 0;
    }

    Matrix(int n) {
        *this = identity(n);
    }

    Matrix(int r, int c) {
        rows = r, columns = c;
        mat = new ll*[r];
        F0R(i, r) {
            mat[i] = new ll[c];
            memset(mat[i], 0, c * sizeof(ll));
        }
    }

    Matrix identity(int n) {
        Matrix m(n, n);
        F0R(i, n) m.mat[i][i] = 1;
        return m;
    }

    Matrix operator +(Matrix b) {
        if(b.rows != rows || b.columns != columns) return Matrix();
        Matrix m(rows, columns);
        F0R(r, rows) F0R(c, columns) m.mat[r][c] = (mat[r][c] + b.mat[r][c]) % MOD;
        return m;
    }

    Matrix operator -(Matrix b) {
        if(b.rows != rows || b.columns != columns) return Matrix();
        Matrix m(rows, columns);
        F0R(r, rows) F0R(c, columns) m.mat[r][c] = (mat[r][c] + MOD - b.mat[r][c]) % MOD;
        return m;
    }

    Matrix operator *(Matrix b) {
        if(columns != b.rows) return Matrix(0, 0);
        Matrix m(rows, b.columns);
        F0R(r, rows) F0R(c, b.columns) {
            m.mat[r][c] = 0;
            F0R(i, columns) {
                m.mat[r][c] += mat[r][i] * b.mat[i][c] % MOD;
                m.mat[r][c] %= MOD;
            }
        }
        return m;
    }

    Matrix operator ^(ll p) {
        if(columns != rows) return Matrix();
        if(p == 0) return identity(rows);
        if(p % 2 == 1) return ((*this ^ (p - 1)) * (*this));
        Matrix sqrt = (*this ^ (p >> 1));
        return (sqrt * sqrt);
    }

    void operator +=(Matrix b) {
        *this = *this + b;
    }

    void operator -=(Matrix b) {
        *this = *this - b;
    }

    void operator *=(Matrix b) {
        *this = *this * b;
    }

    void operator ^=(ll p) {
        *this = *this ^ p;
    }

};

StringTokenizer st;
unordered_map<string, int> varMap;
string line[MAXLINES];
int returnVar, loopNumber[MAXLINES], loopSize[MAXLINES / 2], numVars = 1, numLines, numLoops, loopEnd[MAXLINES / 2];

Matrix getMat(int lo, int hi) {
    if(hi <= lo) return Matrix(numVars);
    st.takeString(line[lo]);
    string token = st.nextToken();
    if(token[0] >= '1' && token[0] <= '9') return getMat(loopEnd[loopNumber[lo]] + 1, hi) * (getMat(lo + 1, loopEnd[loopNumber[lo]]) ^ loopSize[loopNumber[lo]]);
    else {
        Matrix res(numVars);
        int changingVar = varMap[token];
        res.mat[changingVar][changingVar] = 0;
        while((token = st.nextToken()) != "") {
            if(token[0] >= '1' && token[0] <= '9') res.mat[changingVar][0] += stoi(token);
            else if(token[0] >= 'a' && token[0] <= 'z') res.mat[changingVar][varMap[token]]++;
        }
        return getMat(lo + 1, hi) * res;
    }
}

int main() {
    ifstream fin("cowbasic.in");
    ofstream fout("cowbasic.out");
    stack<int> loops;
    while(1) {
        getline(fin, line[numLines]);
        st.takeString(line[numLines]);
        string firstToken = st.nextToken();
        if(firstToken == "RETURN") {
            returnVar = varMap[st.nextToken()];
            break;
        } else if(firstToken[0] >= '1' && firstToken[0] <= '9') {
            loopNumber[numLines] = numLoops;
            loopSize[numLoops] = stoi(firstToken);
            loops.push(numLoops++);
        } else if(firstToken == "}") {
            loopEnd[loops.top()] = numLines;
            loops.pop();
        } else if(!varMap.count(firstToken)) varMap.insert(MP(firstToken, numVars++));
        numLines++;
    }
    fout << getMat(0, numLines).mat[returnVar][0] << "\n";
    return 0;
}
