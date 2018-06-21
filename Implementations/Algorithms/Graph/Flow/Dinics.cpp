int n, m, level[MAXN];
bool vis[MAXN];
map<int, ll> adj[MAXN];
vector<pair<int, ll>> lg[MAXN];

bool buildLG(int s, int t) {
	F0R(i, n) lg[i].clear(), vis[i] = level[i] = 0;
	queue<int> q; q.push(s);
	vis[s] = 1;
	while(!q.empty()) {
		int i = q.front(); q.pop();
		for(const pair<int, ll> next : adj[i]) if(!vis[next.F]) {
			vis[next.F] = 1;
			level[next.F] = level[i] + 1;
			q.push(next.F);
		}
	}
	F0R(i, n) for(const pair<int, ll> edge : adj[i]) if(level[edge.F] == 1 + level[i]) lg[i].PB(edge);
	return level[t];
}

ll greedyFlow(int node, int sink, ll flow) {
	if(node == sink) return flow;
	if(!sz(lg[node])) return 0;
	pair<int, ll> next = lg[node].back();
	ll f = greedyFlow(next.F, sink, min(flow, next.S));
	if(f) {
		lg[node].back().S -= f;
		if(!lg[node].back().S) lg[node].pop_back();
		adj[next.F][node] += f;
		adj[node][next.F] -= f;
		if(!adj[node][next.F]) adj[node].erase(next.F);
	} else if(!sz(lg[next.F])) lg[node].pop_back();
	return f;
}

ll dinics(int s, int t) {
	ll flow = 0;
	while(buildLG(s, t)) while(sz(lg[s])) flow += greedyFlow(s, t, ~(1LL << 63));
	return flow;
}
