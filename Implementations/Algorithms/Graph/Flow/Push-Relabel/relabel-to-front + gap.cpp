// Uses LinkedList.cpp

int n, m, h[MAXN], cnt[MAXN];
ll e[MAXN], c[MAXN][MAXN], f[MAXN][MAXN];
vi neigh[MAXN];
vector<pair<int, ll>> adj[MAXN];

ll cf(int u, int v) { return c[u][v] - f[u][v]; }

void push(int u, int v) {
	ll flow = min(e[u], cf(u, v));
	f[u][v] += flow, f[v][u] -= flow;
	e[u] -= flow, e[v] += flow;
}

void gap(int k) {
	F0R(i, n) if(h[i] < n && h[i] >= k) {
		cnt[h[i]]--;
		h[i] = n;
	}
}

void relabel(int u) {
	cnt[h[u]]--;
	h[u] = n;
	for(const int v : neigh[u]) if(cf(u, v) > 0) h[u] = min(h[u], h[v] + 1);
	if(h[u] < n) cnt[h[u]]++;
}

void discharge(int u) {
	for(const int v : neigh[u])
		if(e[u] && cf(u, v) && h[v] + 1 == h[u]) push(u, v);
		else if(!e[u]) break;
	if(e[u] && cnt[h[u]] == 1) gap(h[u]);
	else if(e[u]) relabel(u);
}

ll flow(int s, int t) {
	F0R(i, n) for(const pair<int, ll> p : adj[i]) {
		if(!c[i][p.F] && !c[p.F][i]) neigh[i].PB(p.F), neigh[p.F].PB(i);
		c[i][p.F] += p.S;
	}
	for(const pair<int, ll> p : adj[s]) e[s] += p.S; 
	LinkedList<int> L;
	F0R(i, n) L.push(i);
	cnt[0] = n;
	Node<int> *it = L.head;
	while(it) {
		int u = it->val;
		int sh = h[u];
		if(h[u] < n && u != t) discharge(u);
		if(h[u] > sh) L.moveToFront(it);
		else it = it->next;
	}
	return e[t];
}
