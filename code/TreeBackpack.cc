/*
 * Author: Simon
 * 功能: 树形依赖背包问题
 * 定义dp[u][i]表示，以u为根节点的子树中保留i条树枝所获得的最大权值
 * 则转移方程为dp[u][i]=max(dp[u][i],dp[left[u]][i-j-1]+left[u].w+dp[right[u]][j-1]+right[u].w)
 * 表示u的右儿子保留j-1条边，u的左儿子保留剩下的i-j-1条边，此时总共有i-2条边，还要加上u-left[u],u-right[u]这两条边。
 * 另外一种转移状态dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j-1]+w)
 * 跟上面类似，只不过将u与其中一个儿子节点的状态放在一起。此时需要倒序枚举i来保证只选择一次（类似01背包）。
 * 没有访问过的子树不会保存在dp[u][i]中，所以不会出现重复计算的情况。
 */
void dfs(int u,int p=-1){
	sz[u]=1;
	for(auto t:g[u]){
		int &v=t.first,&w=t.second;
		if(v==p) continue;
		dfs(v,u);sz[u]+=sz[v];
		for(int i=min(q,sz[u]);i>=1;i--){
			for(int j=1;j<=min(sz[v],i);j++){
				dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j-1]+w);
			}
		}
	}
}