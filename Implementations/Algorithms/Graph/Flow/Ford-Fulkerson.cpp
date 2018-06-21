int m, m;
bool vis[MAXN];
map<int, ll> adj[MAXN];

ll dfsFlow(int node, int sink, ll flow) {
	if(vis[node]) return 0;
	vis[node] = 1;
	if(node == sink) return flow;
	for(const pair<int, ll> p : adj[node]) if(ll f = dfsFlow(p.F, sink, min(p.S, flow))) {
			adj[p.F][node] += f;
			adj[node][p.F] -= f;
			if(!adj[node][p.F]) adj[node].erase(p.F);
			return f;
	}
	return 0;
}

ll fordFulk(int s, int t) {
	ll flow = 0;
	while(1) {
		memset(vis, 0, n * sizeof(bool));
		ll maxFlow = dfsFlow(s, t, ~(1LL << 63));
		if(!maxFlow) break;
		flow += maxFlow;
	}
	return flow;
}
