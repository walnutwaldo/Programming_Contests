#include <bits/stdc++.h>

#define F0R(i, a) for(int i =0 ; i < a; i++)
#define FOR(i, a, b) for(int i = a; i < b; i++)

typedef long long ll;

using namespace std;

const ll MOD = 1000000009;

int n, m, k;
ll maxTeam[1001][1001][11];
vector<ll> scores1, scores2;

int main() {
    ifstream fin("team.in");
    ofstream fout("team.out");

    fin >> n >> m >> k;

    F0R(i, n) {
        ll x;
        fin >> x;
        scores1.push_back(x);
    }
    F0R(i, m) {
        ll x;
        fin >> x;
        scores2.push_back(x);
    }

    sort(scores1.begin(), scores1.end());
    sort(scores2.begin(), scores2.end());
    F0R(i, n+1) F0R(j, m+1)
    maxTeam[i][j][0] = 1;

    FOR(sizeOfTeam, 1, k+1) FOR(j, 1, m+1) FOR(i, 1, n+1) {
        maxTeam[i][j][sizeOfTeam] = ((maxTeam[i-1][j][sizeOfTeam] + maxTeam[i][j-1][sizeOfTeam] - maxTeam[i-1][j-1][sizeOfTeam])%MOD+MOD)%MOD;
        if(scores1[i-1] > scores2[j-1])
            maxTeam[i][j][sizeOfTeam]=(maxTeam[i][j][sizeOfTeam]+maxTeam[i-1][j-1][sizeOfTeam-1])%MOD;
    }

    fout << maxTeam[n][m][k];

    return 0;
}
