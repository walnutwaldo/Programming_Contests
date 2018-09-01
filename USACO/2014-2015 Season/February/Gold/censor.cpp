#include <bits/stdc++.h>

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
#define X real()
#define Y imag()

#define PI acos(-1)

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define SQ(x) ((x) * (x))

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<ll> vll;
typedef vector<ull> vul;
typedef complex<ld> point;
typedef complex<ld> cld;
typedef vector<cld> vcld;

#define MAXL 100000

string s;
char res[MAXL];
vector<string> p;
int n, nodeAt[MAXL];

vector<int*> trie, dfa;
vi strLen, link;

void bfs() {
    queue<int> q; q.push(0);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        F0R(c, 26) if(dfa[link[i]][c]) dfa[i][c] = dfa[link[i]][c];
        F0R(c, 26) if(trie[i][c]) {
            q.push(trie[i][c]);
            link[trie[i][c]] = dfa[i][c];
            dfa[i][c] = trie[i][c];
        }
    }
}

int addNode() {
    link.PB(0); dfa.PB(new int[26]{0}); trie.PB(new int[26]{0}); strLen.PB(0);
    return sz(link) - 1;
}

void build() {
    addNode();
    F0R(i, sz(p)) {
        int curr = 0;
        for(const char c : p[i]) {
            if(!trie[curr][c - 'a']) trie[curr][c - 'a'] = addNode();
            curr = trie[curr][c - 'a'];
        }
        strLen[curr] = sz(p[i]);
    }
    bfs();
}

int main() {
    ifstream fin("censor.in");
    ofstream fout("censor.out");
    fin >> s >> n;
    p = vector<string>(n);
    F0R(i, n) fin >> p[i];
    build();
    int curr = 0, currNode = 0;
    F0R(i, sz(s)) {
        currNode = dfa[currNode][s[i] - 'a'];
        nodeAt[curr] = currNode;
        res[curr] = s[i];
        curr -= strLen[currNode];
        currNode = (curr == -1)?0 : nodeAt[curr];
        curr++;
    }
    F0R(i, curr) fout << res[i];
    fout << endl;
}
