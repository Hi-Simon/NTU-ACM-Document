// 时间复杂度 O(n+q)
// By CSL

#include <iostream>
#include <algorithm>
#include <vector>

const int maxn = "Edit";
int par[maxn];          					 	//并查集
int ans[maxn];           						//存储答案
std::vector<int> G[maxn];     					//邻接表
std::vector<std::pair<int, int>> query[maxn];	//存储查询信息
bool vis[maxn];          						//是否被遍历

inline void init(int n) {
	for (int i = 1; i <= n; i++) {
		G[i].clear(), query[i].clear();
		par[i] = i, vis[i] = 0;
	}
}

int find(int u) {
	return par[u] == u ? par[u] : par[u] = find(par[u]);
}

void unite(int u, int v) {
	par[find(v)] = find(u);
}

inline void add_edge(int u, int v) { 
	G[u].push_back(v); 
}

inline void add_query(int id, int u, int v) {
	query[u].push_back(std::make_pair(v, id));
	query[v].push_back(std::make_pair(u, id));
}

void tarjan(int u) {
	vis[u] = 1;
	for (auto& v : G[u]) {
		if (vis[v]) continue;
		tarjan(v);
		unite(u, v);
	}
	for (auto& q : query[u]) {
		int &v = q.first, &id = q.second;
		if (!vis[v]) continue;
		ans[id] = find(v);
	}
}