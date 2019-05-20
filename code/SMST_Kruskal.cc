//1-indexed
struct edge {
	int s, t, w;	//从s到t 权值w
	bool vis;
	edge() {}
	edge(int s, int t, int w) :s(s), t(t), w(w) {}
	bool operator < (const edge e) const {
		return w < e.w;
	}
}e[maxm];

int pre[maxn];
int Max[maxn][maxn];	// Max[i][j]表示从i到j路径上的最大边权

int find(int x) {
	int r = x, i = x, j;
	while (pre[r] != r)
		r = pre[r];
	while (i != r) {	// 状态压缩
		j = pre[i];
		pre[i] = r;
		i = j;
	}
	return r;
}

int kruskal(int n, int m) {	// n为边数 m为点数
	int lef = m - 1, ans = 0;
	memset(Max, 0, sizeof(Max));
	vector<int>v[maxn];
	for (int i = 1; i <= m; i++) {
		pre[i] = i;
		v[i].push_back(i);
	}
	sort(e + 1, e + n + 1);
	for (int i = 1; i <= n; i++) {
		int fs = find(e[i].s), ft = find(e[i].t), len1, len2;
		if (fs != ft) {
			pre[fs] = ft;
			ans += e[i].w;
			lef--; e[i].vis = true;
			len1 = v[fs].size(), len2 = v[ft].size();
			for (int j = 0; j < len1; j++)
				for (int k = 0; k < len2; k++)
					Max[v[fs][j]][v[ft][k]] = Max[v[ft][k]][v[fs][j]] = e[i].w;
			int tmp[maxn];
			for (int j = 0; j < len1; j++)
				tmp[j] = v[fs][j];
			for (int j = 0; j < len2; j++)
				v[fs].push_back(v[ft][j]);
			for (int j = 0; j < len1; j++)
				v[ft].push_back(tmp[j]);
		}
		if (!lef)break;
	}
	if (lef) ans = -1;	// 图不连通
	return ans;
}

int SMST(int n, int ans) {	// n为边数,ans为最小生成树权值
	int ret = INF;
	for (int i = 1; i <= n; i++)
		if (!e[i].vis)
			ret = min(ret, ans + e[i].w - Max[e[i].s][e[i].t]);
	if (ret == INF) return -1;
	return ret;
}