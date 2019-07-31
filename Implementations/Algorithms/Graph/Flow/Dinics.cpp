struct MaxFlow {

    struct edge {
        int startp, endp;
        ll cap;
        int revidx;
    };

    int sz;
    vector<bool> vis;
    vi level;
    vector<vector<edge>> adj;
    vector<vector<edge*>> lg;

    MaxFlow(int _sz) {
        sz = _sz;
        adj.resize(sz);
        vis.resize(sz);
        level.resize(sz);
        lg.resize(sz);
    }

    int size() const { return sz; }

    void addEdge(int u, int v, ll cap) {
        adj[u].PB({u, v, cap, sz(adj[v])});
        adj[v].PB({v, u, 0, sz(adj[u]) - 1});
    }

    bool build(int src, int snk) {
        F0R(i, sz) {
            lg[i].clear();
            vis[i] = level[i] = 0;
        }
        queue<int> q; q.push(src);
        vis[src] = 1;
        while(!q.empty()) {
            int node = q.front(); q.pop();
            for (const edge e : adj[node]) if(e.cap > 0 && !vis[e.endp]) {
                vis[e.endp] = 1;
                level[e.endp] = level[node] + 1;
                q.push(e.endp);
            }
        }
        F0R(i, sz)
            for(edge& e : adj[i])
                if (e.cap > 0 && level[e.endp] == level[i] + 1)
                    lg[i].PB(&e);
        return level[snk];
    }

    ll greedyFlow(int node, int snk, ll flow) {
        if (node == snk) return flow;
        while (!lg[node].empty()) {
            edge& e = *(lg[node].back());
            ll f = greedyFlow(e.endp, snk, min(flow, e.cap));
            if (f) {
                e.cap -= f;
                if (e.cap == 0) lg[node].pop_back();
                adj[e.endp][e.revidx].cap += f;
                return f;
            } else lg[node].pop_back();
        }
        return 0;
    }

    ll solve(int src, int snk) {
        ll flow = 0;
        while(build(src, snk)) while(!lg[src].empty()) {
            flow += greedyFlow(src, snk, INF);
        }
        return flow;
    }
};

