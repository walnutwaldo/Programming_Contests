int n, m, prec[MAXN];
bool vis[MAXN];
map<int, ll> adj[MAXN];

ll edkarp(int s, int t) {
	ll flow = 0;
	while(1) {
		memset(vis, 0, n * sizeof(bool));
		queue<pair<int, ll>> q;
		q.push(MP(s, ~(1LL << 63))); vis[0] = 1;
		ll maxFlow = 0;
		while(!q.empty()) {
			pair<int, ll> p = q.front(); q.pop();
			if(p.F == t) {
				maxFlow = p.S;
				break;
			}
			for(const pair<int, ll> next : adj[p.F]) if(!vis[next.F]) {
				vis[next.F] = 1;
				prec[next.F] = p.F;
				q.push(MP(next.F, min(p.S, next.S)));
			}
		}
		if(!maxFlow) break;
		flow += maxFlow;
		int curr = t;
		while(curr != s) {
			adj[curr][prec[curr]] += maxFlow;
			adj[prec[curr]][curr] -= maxFlow;
			if(adj[prec[curr]][curr] == 0) adj[prec[curr]].erase(curr);
			curr = prec[curr];
		}
	}
	return flow;
}
