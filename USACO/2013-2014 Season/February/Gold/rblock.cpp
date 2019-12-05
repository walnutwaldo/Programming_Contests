#include <bits/stdc++.h>

using namespace std;

struct edge {
    int a, b;
    long long w;
};

int n, m;
edge edges[25000];
vector<int> adj[250];
vector<int> spEdges;

struct pqstate {
    long long dis;
    int node;
    int prev;
    
    bool operator<(const pqstate& o) const {
        return make_tuple(dis, node, prev) > make_tuple(o.dis, o.node, o.prev);
    }
    
};

long long shortestPath(bool store = false) {
    long long dis[n];
    int prev[n];
    for (int i = 0; i < n; i++) {
        dis[i] = (1LL << 63) - 1;
        prev[i] = -1;
    }
    priority_queue<pqstate> pq;
    dis[0] = 0;
    pq.push({ 0, 0, -1 });
    while (!pq.empty()) {
        pqstate state = pq.top(); pq.pop();
        if (state.dis > dis[state.node]) { continue; }
        dis[state.node] = state.dis;
        prev[state.node] = state.prev;
        for (const int eId : adj[state.node]) {
            edge e = edges[eId];
            int next = e.a ^ e.b ^ state.node;
            pq.push({ state.dis + e.w, next, eId });
        }
    }
    if (store) {
        spEdges.clear();
        int curr = n - 1;
        while (curr != 0) {
            edge e = edges[prev[curr]];
            spEdges.push_back(prev[curr]);
            curr = e.a ^ e.b ^ curr;
        }
    }
    return dis[n - 1];
}

int main() {
    ifstream cin("rblock.in");
    ofstream cout("rblock.out");
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
        edges[i].a--;
        edges[i].b--;
        adj[edges[i].a].push_back(i);
        adj[edges[i].b].push_back(i);
    }
    long long initLen = shortestPath(true);
    long long res = 0;
    for (const int eId : spEdges) {
        edges[eId].w <<= 1;
        res = max(res, shortestPath() - initLen);
        edges[eId].w >>= 1;
    }
    cout << res << endl;
    return 0;
}
