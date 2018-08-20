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
#define NMAX 10000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N, tmax, duration[NMAX];

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");

    fin >> N >> tmax;

    F0R(i, N) fin >> duration[i];

    int lo = 1, hi = N;
    while(lo < hi) {
        int mid = (lo+hi)/2;
        priority_queue<int,vector<int>,greater<int>> pq;
        int curr = mid;
        int t;
        F0R(i, mid) pq.push(duration[i]);
        while(!pq.empty()) {
            t = pq.top();
            pq.pop();
            if(curr < N) pq.push(t + duration[curr++]);
            if(t > tmax) {
                lo = mid + 1;
                break;
            }
        }
        if(t <= tmax)
            hi = mid;
    }
    fout << lo;
    return 0;
}
