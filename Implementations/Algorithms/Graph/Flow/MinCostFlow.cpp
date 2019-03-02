namespace MinFlow {

    struct FlowEdge { int next, revIdx; ll flow, cap, cost; };
    struct Edge { int next; ll cost, cap; };
    struct PrevData { int node, backIdx; };

    vector<PrevData> prev;
    vector<pair<ll, ll>> dis;
    vector<vector<FlowEdge>> adj;
    ll minCost;
    pair<ll, ll> res;

    void createAdj(vector<Edge> *flowAdj, const int& n) {
        adj.clear(); adj.resize(n);
        vector<map<pair<int, ll>, int>> v; v.resize(n);
        F0R(i, n) for(const Edge e : flowAdj[i]) {
            bool newNode = 0, newNext = 0;
            if(!v[i].count({e.next, e.cost})) {
                v[i][{e.next, e.cost}] = sz(adj[i]);
                newNode = 1;
            }
            if(!v[e.next].count({i, -e.cost})) {
                v[e.next][{i, -e.cost}] = sz(adj[e.next]);
                newNext = 1;
            }
            if(newNode) adj[i].PB({e.next, v[e.next][{i, -e.cost}], 0, 0, e.cost});
            adj[i][v[i][{e.next, e.cost}]].cap += e.cap;
            if(newNext) adj[e.next].PB({i, v[i][{e.next, e.cost}], 0, 0, -e.cost});
        }
    }

    void calcPotential(const int& s, const int& t) {
        F0R(i, sz(adj)) dis[i] = MP(-INF, 0);
        dis[s] = MP(0, INF);
        priority_queue<pair<pair<ll, ll>, int>> pq;
        pq.push({dis[s], s});
        while (!pq.empty()) {
            int node = pq.top().S;
            pair<ll, ll> d = pq.top().F;
            pq.pop();
            if(d < dis[node]) continue;
            for (const FlowEdge e: adj[node]) if (e.flow < e.cap) {
                pair<ll, ll> newDis = MP(dis[node].F - e.cost, min(e.cap - e.flow, dis[node].S));
                if(newDis > dis[e.next]) {
                    prev[e.next] = {node, e.revIdx};
                    dis[e.next] = newDis;
                    pq.push({dis[e.next], e.next});
                }
            }
        }
        F0R(i, sz(adj)) dis[i].F = -dis[i].F;
        minCost += dis[t].F;
    }

    void backtrack(const int& s, const int& t) {
        res.F += dis[t].S;
        res.S += dis[t].S * minCost;
        for(int curr = t; curr != s; curr = prev[curr].node) {
            adj[curr][prev[curr].backIdx].flow -= dis[t].S;
            int idx = adj[curr][prev[curr].backIdx].revIdx;
            adj[prev[curr].node][idx].flow += dis[t].S;
        }
    }

    pair<ll, ll> calcMinFlow(vector<Edge> *flowAdj, const int& n, const int& s, const int& t) {
        createAdj(flowAdj, n); dis.resize(n); prev.resize(n);
        minCost = 0;
        res = MP(0LL, 0LL);
        calcPotential(s, t);
        while (1) {
            F0R(i, sz(adj)) for (FlowEdge& e: adj[i]) e.cost += dis[i].F - dis[e.next].F;
            calcPotential(s, t);
            if(dis[t] == MP((ll)INF, 0LL)) break;
            backtrack(s, t);
        }
        return res;
    }

};
