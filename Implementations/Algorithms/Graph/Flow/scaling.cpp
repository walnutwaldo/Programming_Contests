int n, m;
bool vis[MAXN];
map<int, ll> adj[MAXN];

bool dfsFlow(int node, int sink, ll minCap) {
	if(vis[node]) return 0;
	vis[node] = 1;
	if(node == sink) return 1;
	for(const pair<int, ll> p : adj[node])
		if(p.S >= minCap && dfsFlow(p.F, sink, minCap)) {
			adj[node][p.F] -= minCap;
			if(!adj[node][p.F]) adj[node].erase(p.F);
			adj[p.F][node] += minCap;
			return 1;
		}
	return 0;
}

ll scalingFlow(int s, int t) {
	ll minCap = 0;
	F0R(node, n) for(const pair<int, ll> p : adj[node]) minCap = max(minCap, p.S);
	ll flow = 0;
	while(minCap) {
		memset(vis, 0, n * sizeof(bool));
		if(!dfsFlow(s, t, minCap)) minCap /= 2;
		else flow += minCap;
	}
	return flow;
}
