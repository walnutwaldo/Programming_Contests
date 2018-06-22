int n;
vi adj[MAXN];
bool vis[MAXN];

void dfs(int node, const vi &topo) {
  if(vis[node]) return;
  vis[node] = 1;
  for(const int next : adj[node]) dfs(next);
  topo.PB(node);
}

vi topoSort() {
  vi topo;
  F0R(i, n) if(!vis[i]) dfs(i, topo);
  reverse(all(topo));
}
