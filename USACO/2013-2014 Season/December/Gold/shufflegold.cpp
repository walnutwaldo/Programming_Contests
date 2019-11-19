#include <bits/stdc++.h>

using namespace std;

int func[100000];
int revfunc[100000];
int invfromnegone[100000];
int stepsto[100000];
int lastM[100000];

int n, m, q;

int main() {
    ifstream cin("shufflegold.in");
    ofstream cout("shufflegold.out");
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> func[i];
        func[i] -= 2;
        revfunc[func[i] + 1] = i;
        stepsto[i] = -1;
    }
    int processtime = 0;
    int curr = m - 1;
    while (curr != -1) {
        stepsto[curr] = processtime;
        curr = func[curr];
        processtime++;
    }
    curr = -1;
    for (int i = 0; i < m; i++) {
        curr = revfunc[curr + 1];
        invfromnegone[i] = curr;
    }
    
    for (int i = 0; i < m; i++) { lastM[i] = -1; }
    for (int i = 0; i < m - 1; i++) {
        if (stepsto[i] == -1 && lastM[i] == -1) {
            int cyclelen = 1;
            curr = func[i];
            while (curr != i) {
                cyclelen++;
                curr = func[curr];
            }
            
            int numShifts = (n - m + 1) % cyclelen;
            for (int j = 0; j < numShifts; j++) { curr = func[curr]; }
            int curr2 = i;
            while (lastM[curr] == -1) {
                lastM[curr] = curr2;
                curr = func[curr];
                curr2 = func[curr2];
            }
        }
    }
    curr = m - 1;
    if (processtime > n - m + 1) {
        for (int i = 0; i < n - m + 1; i++) { curr = func[curr]; }
        int curr2 = m - 1;
        while (curr != -1) {
            lastM[curr] = curr2;
            curr = func[curr];
            curr2 = func[curr2];
        }
    }
    
    for (int i = 0; i < q; i++) {
        int pos;
        cin >> pos;
        if (pos < m) {
            pos = m - 1 - pos;
            if (lastM[pos] != -1) {
                cout << lastM[pos] + 1 << "\n";
            } else {
                cout << n - stepsto[pos] + 1 << "\n";
            }
        } else {
            pos = n - pos;
            if (pos <= processtime - 1) {
                cout << invfromnegone[pos] + 1 << "\n";
            } else {
                cout << pos + m - processtime + 1 << "\n";
            }
        }
    }
    return 0;
}
