#include <bits/stdc++.h>

using namespace std;

int n, m, k, q, hubnum[200], hubid[20000];
long long distohub[20000][200], distononhub[200][20000];
vector<pair<int, long long>> adj[20000];
vector<pair<int, long long>> hubadj[200];

long long disbw[200][200];
long long disTo[200];

int main() {
    ifstream cin("vacationgold.in");
    ofstream cout("vacationgold.out");
    cin >> n >> m >> k >> q;
    for (int i = 0; i < n; i++) {
        hubid[i] = -1;
        for (int j = 0; j < k; j++) {
            distohub[i][j] = INT_MAX;
            distononhub[j][i] = INT_MAX;
        }
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long d;
        cin >> u >> v >> d;
        u--, v--;
        adj[u].emplace_back(v, d);
    }
    for (int i = 0; i < k; i++) {
        cin >> hubnum[i];
        hubnum[i]--;
        hubid[hubnum[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (const pair<int, long long> edge : adj[i]) {
            int next = edge.first;
            long long dis = edge.second;
            if (hubid[next] != -1) {
                distohub[i][hubid[next]] = min(distohub[i][hubid[next]], dis);
            } else if (hubid[i] != -1 && hubid[next] == -1) {
                distononhub[hubid[i]][next] = min(distononhub[hubid[i]][next], dis);
            }
        }
    }
    for (int i = 0; i < k; i++) {
        int node = hubnum[i];
        for (const pair<int, long long> edge : adj[node]) {
            int next = edge.first;
            long long dis = edge.second;
            if (hubid[next] == -1) {
                for (int j = 0; j < k; j++) {
                    distohub[node][j] = min(distohub[node][j], dis + distohub[next][j]);
                }
            }
        }
        for (int j = 0; j < k; j++) {
            if (distohub[node][j] < INT_MAX) {
                hubadj[i].emplace_back(j, distohub[node][j]);
            }
            disbw[i][j] = distohub[node][j];
            disbw[i][i] = 0;
        }
    }
    
    for (int mid = 0; mid < k; mid++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (disbw[i][mid] + disbw[mid][j] < disbw[i][j]) { disbw[i][j] = disbw[i][mid] + disbw[mid][j]; }
            }
        }
    }
    
    vector<int> queries[n];
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        queries[u].push_back(v);
    }
    int res = 0;
    long long total = 0;
    for (int strt = 0; strt < n; strt++) {
        for (int i = 0; i < k; i++) {
            if (hubid[strt] == -1) {
                disTo[i] = INT_MAX;
            } else {
                disTo[i] = disbw[hubid[strt]][i];
            }
        }
        for (const pair<int, long long> edge : adj[strt]) {
            if (hubid[edge.first] != -1) {
                for (int j = 0; j < k; j++) {
                    disTo[j] = min(disTo[j], edge.second + disbw[hubid[edge.first]][j]);
                }
            }
        }
        for (const int endp : queries[strt]) {
            if (hubid[endp] == -1) {
                long long dis = INT_MAX;
                for (int i = 0; i < k; i++) {
                    dis = min(dis, distononhub[i][endp] + disTo[i]);
                }
                if (dis < INT_MAX) {
                    res++;
                    total += dis;
                }
            } else {
                if (disTo[hubid[endp]] < INT_MAX) {
                    res++;
                    total += disTo[hubid[endp]];
                }
            }
        }
    }
    cout << res << "\n" << total << endl;
    return 0;
}
