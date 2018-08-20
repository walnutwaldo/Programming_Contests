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

int N, leftEnd[MAXN + 1], rightEnd[MAXN + 1], answer[MAXN + 1], counter = 1;
ll score[MAXN + 1];
vi children[MAXN + 1];

void work(int node) {
    leftEnd[node] = counter;
    for(int child: children[node]) {
        work(child);
        counter++;
    }
    rightEnd[node] = counter;
}

int main() {
    ifstream fin("promote.in");
    ofstream fout("promote.out");

    fin >> N;
    FOR(i, 1, N + 1) fin >> score[i];
    FOR(i, 2, N + 1) {
        int manager;
        fin >> manager;
        children[manager].PB(i);
    }
    work(1);
    int bit[counter + 1];
    F0R(i, counter + 1) {
        bit[i] = 0;
    }
    vector<pair<pair<ll, int>,pair<int,int>>> cows;
    FOR(i, 1, N + 1) {
        cows.PB(MP(MP(score[i], i), MP(leftEnd[i], rightEnd[i])));
    }
    sort(cows.rbegin(), cows.rend());
    F0R(i, N) {
        int sum = 0;
        for(int index = cows[i].S.S; index > 0; index -= (index & -index))
            sum+=bit[index];
        for(int index = cows[i].S.F - 1; index > 0; index -= (index & -index))
            sum-=bit[index];
        answer[cows[i].F.S] = sum;
        for(int index = cows[i].S.S; index <= counter; index += (index & -index))
            bit[index]++;
    }
    FOR(i, 1, N + 1) fout << answer[i] << endl;
    return 0;
}
