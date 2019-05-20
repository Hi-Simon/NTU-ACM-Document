const int inf = ~0U>>1;
const int N = "Edit";

typedef struct seg{
	int to,op,cost,nxt,f;
}seg;

seg v[N*40]; 

int ans =0,tot,dis[N],base[N],vis[N],ttf = 0;

int S,T; int cur[N];

void inti() {
	memset(base,0,sizeof(base));
	memset(dis,0,sizeof(dis));
	tot = 0; ans = 0; ttf = 0;
	memset(vis,0,sizeof(vis));
}

int aug(int u,int flow){
	if (u == T){
		ans += flow * dis[S];
		ttf += flow;
		return flow;
	}
	vis[u] = 1;
	int now = 0;
	for (int i = base[u];i;i = v[i].nxt){
		int x = v[i].to;
		if (vis[x] || v[i].f <= 0 || dis[u] != dis[x] + v[i].cost)
			continue;
		int tmp = aug(x,std::min(flow - now,v[i].f));
		v[i].f -= tmp; v[v[i].op].f += tmp;
		now += tmp;
		if (now == flow) return flow;
	}
	return now;
}


int modlabel() {
	int del = inf;
	for (int i = S; i <= T; i++) {
		if (vis[i]) for (int j = base[i];j;j = v[j].nxt) {
			if (v[j].f){
				int x = v[j].to;
				if (!vis[x]) del = std::min(del,dis[x] + v[j].cost - dis[i]);
			}
		}
	}
	if (del == inf) {
		return 0;
	}
	for (int i = S;i <= T;i++) {
		if (vis[i]) {
			vis[i] = 0,dis[i] += del,cur[i] = base[i];
		}
	}
	return 1;
}


int zkw() {
	for (int i = S;i <= T;i++) cur[i] = base[i];
	int fl, t = 0;
	do {
		t = 0;
		while((t = aug(S,inf))) memset(vis,0,sizeof(vis));
	} while(modlabel());
	return ans;
}

void add(int x, int y, int c, int f){
	v[++tot].to = y; v[tot].op = tot + 1;
	v[tot].f = f; v[tot].cost = c;
	v[tot].nxt = base[x]; base[x] = tot;
	v[++tot].to = x; v[tot].op = tot - 1;
	v[tot].f = 0; v[tot].cost = -c;
	v[tot].nxt = base[y]; base[y] = tot;
}