// 0-indexed
bool vis[maxn];
int d[maxn][maxn];
int lowc[maxn];
int pre[maxn];
int Max[maxn][maxn];	// Max[i][j]表示i到j的路径上的最大边权
bool used[maxn][maxn];
int Prim(int n) {
	int ans = 0;
	memset(vis, false, sizeof(vis));
	memset(Max, 0, sizeof(Max));
	memset(used, false, sizeof(used));
	vis[0] = true;
	pre[0] = -1;
	for (int i = 1; i < n; i++) {
		lowc[i] = d[0][i];
		pre[i] = 0;
	}
	lowc[0] = 0;
	for (int i = 1; i < n; i++) {
		int minc = INF;
		int p = -1;
		for (int j = 0; j < n; j++)
			if (!vis[j] && minc > lowc[j]) {
				minc = lowc[j];
				p = j;
			}
		if (minc == INF)return -1;
		ans += minc;
		vis[p] = true;
		used[p][pre[p]] = used[pre[p]][p] = true;
		for (int j = 0; j < n; j++) {
			if (vis[j]) Max[j][p] = Max[p][j] = max(Max[j][pre[p]], lowc[p]);
			if (!vis[j] && lowc[j] > d[p][j]) {
				lowc[j] = d[p][j];
				pre[j] = p;
			}
		}
	}
	return ans;
}
int SMST(int n, int ans) {
	int Min = INF;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (d[i][j] != INF && !used[i][j])
				Min = min(Min, ans + d[i][j] - Max[i][j]);
	if (Min == INF) return -1;
	return Min;
}