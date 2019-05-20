//written by kuangbin
const int maxn = "Edit";
const int maxm = "Edit";

struct node {
	int to, next;
} edge[maxm];

int head[maxn], tot;
int low[maxn], dfn[maxn], stack[maxn], belong[maxn];
int cur, top, scc;
bool instack[maxn];
int num[maxn];

int in[maxn], out[maxn];

void init() {
	tot = 0;
	std::fill(head, head+maxn, -1);
	std::fill(in, in+maxn, 0);
	std::fill(out, out+maxn, 0);
}

void addedge(int u, int v) {
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}

void tarjan(int u) {
	int v;
	low[u] = dfn[u] = ++cur;
	stack[top++] = u;
	instack[u] = 1;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		v = edge[i].to;
		if (!dfn[v]) {
			tarjan(v);
			if (low[u] > low[v]) low[u] = low[v];
		} else if (instack[v] && low[u] > dfn[v]) {
			low[u] = dfn[v];
		}
	}
	if (low[u] == dfn[u]) {
		scc++;
		do {
			v = stack[--top];
			instack[v] = 0;
			belong[v] = scc;
			num[scc]++;
		} while (v != u);
	}
}

void solve(int n) {
	std::fill(dfn, dfn+maxn, 0);
	std::fill(instack, instack+maxn, 0);
	std::fill(num, num+maxn, 0);
	cur = scc = top = 0;
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
}

void in_out(int n) {
	for (int u = 1; u <= n; u++) {
		for (int i = head[u]; i != -1; i = edge[i].next) {
			if (belong[u] != belong[edge[i].to]) {
				in[belong[edge[i].to]]++;
				out[belong[u]]++;
			}
		}
	}
}