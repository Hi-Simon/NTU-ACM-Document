const int maxn = "Edit";

struct Edge {
	int to, nxt, dis;
} g[maxn];
int head[maxn], cnt, f[maxn], dd[maxn], size[maxn], d[maxn];
int n, k, rt, ans, con, len;
bool vis[maxn];

void add(int u, int v, int dis) { 
	g[++ cnt] = (Edge){v, head[u], dis}; 
	head[u] = cnt;
}

void add_edge(int u, int v, int dis) {
	add(u, v, dis); 
	add(v, u, dis);
}

void clr(){
	for(int i = 1; i <= n; i ++) {
		vis[i] = f[i] = size[i] = head[i] = dd[i] = 0;
	}
	cnt = rt = 0, f[0] = 1e9, con = n, len = ans = 0;
}

void getrt(int u, int fafa){
	size[u] = 1; 
	f[u] = 0;
	for(int i = head[u]; i; i = g[i].nxt){
		int v = g[i].to; if(v == fafa || vis[v]) continue;
		getrt(v, u); 
		size[u] += size[v];
		f[u] = std::max(f[u], size[v]);
	}
	f[u] = std::max(f[u], con - size[u]);
	if(f[u] < f[rt]) {
		rt = u;
	}
}

void getdis(int u, int fafa){
	size[u] = 1;
	dd[++ len] = d[u];
	for(int i = head[u]; i; i = g[i].nxt){
		int v = g[i].to; if(v == fafa || vis[v]) continue;
		d[v] = d[u] + g[i].dis; getdis(v, u);
		size[u] += size[v];
	}
}

int cal(int u, int w){
	len = 0; d[u] = w; getdis(u, 0);
	std::sort(dd + 1, dd + len + 1);
	int l = 1, r = len, sum = 0;
	while(l < r){
		if(dd[l] + dd[r] <= k) sum += r - l, l ++;
		else r --;
	}
	return sum;
}

void solve(int u){
	vis[u] = 1; ans += cal(u, 0);
	for(int i = head[u]; i; i = g[i].nxt){
		int v = g[i].to; if(vis[v]) continue;
		ans -= cal(v, g[i].dis);
		rt = 0; con = size[v];
		getrt(v, 0); 
		solve(rt);
	}
}