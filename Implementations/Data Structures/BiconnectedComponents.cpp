struct BCC {

    bool *visited;
    int *depth, *lowpoint, numNodes;
    vi *connections;
    vector<vector<pii>> components;

    BCC(int sz) {
        numNodes = sz;
        depth = new int[numNodes];
        lowpoint = new int[numNodes];
        visited = new bool[numNodes];
        connections = new vi[numNodes];
        memset(depth, 0, numNodes);
    }

    void addEdge(int a, int b) {
        connections[a].PB(b);
        connections[b].PB(a);
    }

    void calculateBCCs() {
        memset(visited, 0, numNodes);
        vector<pii> *s = new vector<pii>();
        F0R(i, numNodes) if(!visited[i]) dfs(i, 0, -1, s);
    }

    void dfs(int node, int d, int parent, vector<pii>* s) {
        visited[node] = true;
        depth[node] = lowpoint[node] = d;
        for(const int next : connections[node]) {
            pii edge = MP(min(node, next), max(node, next));
            if(visited[next] && next != parent) {
                lowpoint[node] = min(lowpoint[node], depth[next]);
                if(depth[next] < d) s->PB(edge);
            } else if (!visited[next]) {
                s->PB(edge);
                dfs(next, d + 1, node, s);
                lowpoint[node] = min(lowpoint[node], lowpoint[next]);
                if(lowpoint[next] >= d) {
                    vector<pii> v;
                    while(true) {
                        pii p = s->back();
                        s->pop_back();
                        v.PB(p);
                        if(p == edge) break;
                    }
                    components.PB(v);
                }
            }
        }
    }
};
