int nxt[MAXN];
bool vis[MAXN];
map<int, ll> adj[MAXN];

ll dfsFlow(int node, int sink) {
	if(vis[node]) return 0;
	vis[node] = 1;
	if(node == sink) return ~(1LL << 63);
	for(const pair<int, ll> p : adj[node]) {
		ll f = dfsFlow(p.F, sink);
		if(f) {
			nxt[node] = p.F;
			return min(f, p.S);
		}
	}
	return 0;
}

ll fordFulk(int s, int t) {
	ll flow = 0;
	while(1) {
		memset(vis, 0, n * sizeof(bool));
		ll maxFlow = dfsFlow(s, t);
		if(!maxFlow) break;
		flow += maxFlow;
		int curr = s;
		while(curr != t) {
			adj[curr][nxt[curr]] -= maxFlow;
			if(adj[curr][nxt[curr]] == 0) adj[curr].erase(nxt[curr]);
			adj[nxt[curr]][curr] += maxFlow;
			curr = nxt[curr];
		}
	}
	return flow;
}
