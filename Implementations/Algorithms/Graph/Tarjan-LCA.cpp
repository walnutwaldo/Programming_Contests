// Uses DisjointUnion.cpp

int n, q, anc[MAXN], res[MAXQ];
vi children[MAXN];
vpii queries, nodeQueries[MAXN];
bool vis[MAXN];
DSU dsu;

void dfs(int node) {
	for(const int child : children[node]) {
		dfs(child);
		dsu.join(node, child);
		anc[dsu.root(node)] = node;
	}
	vis[node] = 1;
	for(const pii p : nodeQueries[node]) if(vis[p.S]) res[p.F] = anc[dsu.root(p.S)];
}

void lca(int root) {
	memset(vis, 0, n * sizeof(bool));
	F0R(i, n) nodeQueries[i].clear();
	F0R(i, q) {
		nodeQueries[queries[i].F].PB(MP(i, queries[i].S));
		nodeQueries[queries[i].S].PB(MP(i, queries[i].F));
	}
	dsu = DSU(n);
	dfs(root);
}
