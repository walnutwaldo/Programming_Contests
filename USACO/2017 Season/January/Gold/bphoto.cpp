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
#define MAXN 100000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, bit[MAXN + 1], inBIT;

void add(int i) {
    i += 1;
    for(; i <= N; i += (i &- i))
        bit[i]++;
    inBIT++;
}

int read(int i) {
    i += 1;
    int answer = 0;
    for(; i > 0; i -= (i & -i))
        answer += bit[i];
    return answer;
}

int main() {
    ifstream fin("bphoto.in");
    ofstream fout("bphoto.out");
    fin >> N;

    priority_queue<pair<ll, int>> pq;
    F0R(i, N) {
        ll height;
        fin >> height;
        pq.push(MP(height, i));
    }

    int num = 0;
    while(!pq.empty()) {
        int loc = pq.top().S;
        pq.pop();
        int l = read(loc);
        int r = inBIT - l;
        if(max(r,l) > 2*min(r,l))
            num++;
        add(loc);
    }
    fout << num;

    return 0;
}
