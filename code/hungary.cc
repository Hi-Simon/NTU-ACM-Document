int n, m;		
int g[maxn][maxn];	//0-labeled
int linker[maxn];
bool used[maxn];

bool dfs(int u) {
	int v;
	for(v = 0; v < m; v++) {
		if(g[u][v] && !used[v]) {
			used[v] = true;
			if(linker[v] == -1 || dfs(linker[v])) {
				linker[v] = u;
				return true;
			}    
		} 
	}
	return false;  
}   
 
int hungary() {
	int res = 0;
	int u;
	memset(linker, -1, sizeof(linker)); 
	for(u = 0; u < n; u++) {
		memset(used, 0, sizeof(used));
		if(dfs(u)) {
			res++;
		}
	} 
	return res;   
}   
