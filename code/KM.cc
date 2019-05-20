const int maxn = "Edit";
const int inf = 2e9;

int n, cost[maxn][maxn];
int lx[maxn], ly[maxn], match[maxn], slack[maxn], prev[maxn];
bool vy[maxn];

void augment(int root) {
	std::fill(vy + 1, vy + n + 1, false);
	std::fill(slack + 1, slack + n + 1, inf);
	int py;
	match[py = 0] = root;
	do {
		vy[py] = true;
		int x = match[py], delta = inf, yy;
		for (int y = 1; y <= n; y++) {
			if (!vy[y]) {
				if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
					slack[y] = lx[x] + ly[y] - cost[x][y];
					prev[y] = py;
				}
				if (slack[y] < delta) {
					delta = slack[y];
					yy = y;
				}
			}
		}
		for (int y = 0; y <= n; y++) {
			if (vy[y]) {
				lx[match[y]] -= delta;
				ly[y] += delta;
			} else {
				slack[y] -= delta;
			}
		}
		py = yy;
	} while (match[py] != -1);
	do {
		int pre = prev[py];
		match[py] = match[pre];
		py = pre;
	} while (py);
}

int KM() {
	for (int i = 1; i <= n; i++) {
		lx[i] = ly[i] = 0;
		match[i] = -1;
		for (int j = 1; j <= n; j++) {
			lx[i] = std::max(lx[i], cost[i][j]);
		}
	}
	int answer = 0;
	for (int root = 1; root <= n; root++) {
		augment(root);
	}
	for (int i = 1; i <= n; i++) {
		answer += lx[i];
		answer += ly[i];
		//printf("%d %d\n", match[i], i);
	}
	return answer;
}