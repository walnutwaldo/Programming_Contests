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
#define MAXN 300000

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<ll> point;

int n, q, a[MAXN];
unordered_map<int, vi> occurences;

int getCount(int num, int l, int r) {
    int leftMost = LB(occurences[num].begin(), occurences[num].end(), l) - occurences[num].begin();
    int rightOver = LB(occurences[num].begin(), occurences[num].end(), r)- occurences[num].begin();
    return rightOver - leftMost;
}

struct Node {

    int s, e;
    vi *leftTop, *rightTop;
    Node *lChild, *rChild;

    Node(int s, int e) {
        this->s = s;
        this->e = e;
        int mid = (s + e) >> 1;
        rightTop = new vi[e - mid];
        unordered_map<int, int> occ;
        unordered_set<int> in;
        FOR(i, mid, e) {
            occ[a[i]]++;
            if(!in.count(a[i]) && occ[a[i]] > (double)(i - mid + 1) / 5) {
                rightTop[i - mid].PB(a[i]);
                in.insert(a[i]);
            }
            if(i > mid) for(const int k : rightTop[i - mid - 1]) if(occ[k] > (double)(i - mid + 1) / 5) rightTop[i - mid].PB(k);
                    else in.erase(k);
        }
        leftTop = new vi[mid - s];
        occ.clear();
        in.clear();
        ROF(i, s, mid) {
            occ[a[i]]++;
            if(!in.count(a[i]) && occ[a[i]] > (double)(mid - i) / 5) {
                leftTop[mid - i - 1].PB(a[i]);
                in.insert(a[i]);
            }
            if(i < mid - 1) for(const int k : leftTop[mid - i - 2]) if(occ[k] > (double)(mid - i) / 5) leftTop[mid - i - 1].PB(k);
                    else in.erase(k);
        }
        if(e > s + 1) {
            lChild = new Node(s, mid);
            rChild = new Node(mid, e);
        }
    }

    int solve(int l, int r, int k) {
        int mid = (s + e) >> 1;
        if(l < mid && r > mid) {
            double toPass = (double)(r - l) / k;
            int minAnswer = -1;
            for(const int i : rightTop[r - 1 - mid]) if((minAnswer == -1 || i < minAnswer) && getCount(i, l, r) > toPass) minAnswer = i;
            for(const int i : leftTop[mid - l - 1]) if((minAnswer == -1 || i < minAnswer) && getCount(i, l, r) > toPass) minAnswer = i;
            return minAnswer;
        } else if(r <= mid) return lChild->solve(l, r, k);
        else return rChild->solve(l, r, k);
    }

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    F0R(i, n) {
        cin >> a[i];
        if(!occurences.count(a[i])) occurences.insert(MP(a[i], vi()));
        occurences[a[i]].PB(i);
    }
    Node root(0, n);
    F0R(i, q) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        if(r == l + 1) {
            cout << a[l] << "\n";
        } else {
            int answer = root.solve(l, r, k);
            cout << answer << "\n";
        }
    }
    return 0;
}
