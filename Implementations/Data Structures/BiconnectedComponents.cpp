struct BCC {

    bool *visited, *isAP;
    int *depth, *lowpoint, numNodes;
    vi *components, *connections, APs;

    BCC(int sz) {
        numNodes = sz;
        depth = new int[numNodes];
        lowpoint = new int[numNodes];
        visited = new bool[numNodes];
        isAP = new bool[numNodes];
        connections = new vi[numNodes];
        components = new vi[numNodes];
        memset(isAP, 0, numNodes);
    }

    void addEdge(int a, int b) {
        connections[a].PB(b);
        connections[b].PB(a);
    }

    void calculateBCCs() {
        memset(visited, 0, numNodes);
        F0R(i, numNodes) if(depth[i] == 0) calcAPs(i, 0, -1);
        int curr = 0;
        for(const int i : APs)
            for(const int j : connections[i])
                if(isAP[j]) {
                    components[i].PB(curr);
                    components[j].PB(curr++);
                }
        F0R(i, numNodes) if(components[i].size() == 0) {
            dfs(i, curr);
            curr++;
        }
    }

    void dfs(int node, int component) {
        components[node].PB(component);
        if(!isAP[node])
            for(const int next : connections[node]) {
                if(components[next].size() > 0) continue;
                dfs(next, component);
            }
    }

    void calcAPs(int node, int d, int parent) {
        visited[node] = true;
        depth[node] = d;
        lowpoint[node] = d;
        int numChildren = 0;
        for(const int next : connections[node]) {
            if(visited[next]) {
                if(next != parent) lowpoint[node] = min(lowpoint[node], depth[next]);
                continue;
            }
            calcAPs(next, d + 1, node);
            numChildren++;
            if(lowpoint[next] >= d) isAP[node] = true;
            lowpoint[node] = min(lowpoint[node], lowpoint[next]);
        }
        if(node == 0 && numChildren > 1) isAP[node] = true;
        if(isAP[node]) APs.PB(node);
    }
};
