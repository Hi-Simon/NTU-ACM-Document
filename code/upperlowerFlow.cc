/*
		首先建立一个源S和一个汇T，一般称为附加源和附加汇。
		对于图中的每条弧<u,v>，假设它容量上界为c，下界b，那么把这条边拆为三条只有上界的弧。
		一条为<S,v>，容量为b；
　　一条为<u,T>，容量为b；
　　一条为<u,v>，容量为c-b。
		其中前两条弧一般称为附加弧。
		然后对这张图跑最大流，以S为源，以T为汇，如果所有的附加弧都满流，则原图有可行流;否则就是无解。 
		这时，每条非附加弧的流量加上它的容量下界，就是原图中这条弧应该有的流量。
		
		对于原图中的每条弧，我们把c-b称为它的自由流量，意思就是只要它流满了下界，这些流多少都没问题。
　　既然如此，对于每条弧<u,v>，我们强制给v提供b单位的流量，并且强制从u那里拿走b单位的流量，这一步对应着两条附加弧。
　　如果这一系列强制操作能完成的话，也就是有一组可行流了。
　　注意：这张图的最大流只是对应着原图的一组可行流，而不是原图的最大或最小流。
*/
using namespace std;
const int oo = (1LL << 31) - 1;
const int LEN = 1e5 + 5;
struct node {
		int x, y, l, r;
} a[LEN];
namespace ISAP {
		int flow, tot, n, m, src, tar, qh, qt, cnt, ans;
		struct edge {
				int vet, next, len;
		} E[LEN * 2];
		int dis[LEN], gap[LEN], head[LEN], cur[LEN], q[LEN], vis[LEN], IN[LEN];
		void add(int u, int v, int c) {
				E[++tot] = (edge){v, head[u], c};
				head[u] = tot;
		}
		void join(int u, int v, int c) {
				add(u, v, c);
				add(v, u, 0);
		}
		void bfs(int s) {
				qh = qt = 0;
				q[++qt] = s;
				dis[s] = 0;
				vis[s] = 1;
				while (qh < qt) {
						int u = q[++qh];
						gap[dis[u]]++;
						for (int e = head[u]; e != -1; e = E[e].next) {
								int v = E[e].vet;
								if (E[e ^ 1].len && !vis[v]) {
										dis[v] = dis[u] + 1;
										vis[v] = 1;
										q[++qt] = v;
								}
						}
				}
		}
		int isap(int u, int aug) {
				if (u == tar) return aug;
				int flow = 0;
				for (int e = head[u]; e != -1; e = E[e].next) {
						int v = E[e].vet;
						if (E[e].len && dis[v] == dis[u] - 1) {
								int tmp = isap(v, min(aug - flow, E[e].len));
								E[e].len -= tmp;
								E[e ^ 1].len += tmp;
								flow += tmp;
								head[u] = e;
								if (flow == aug || dis[src] == cnt) return flow;
						}
				}
				if (!--gap[dis[u]++]) dis[src] = cnt;
				++gap[dis[u]];
				head[u] = cur[u];
				return flow;
		}
		void init() {
				tot = -1, gap[0] = 0;
				for (int i = 1; i <= cnt; i++) {
						dis[i] = gap[i] = vis[i] = IN[i] = 0;
						head[i] = -1;
				}
		}
		int maxflow(int s, int t) {
				src = s, tar = t;
				int res = 0;
				for (int i = 1; i <= cnt; i++) cur[i] = head[i];
				bfs(tar);
				while (dis[src] < cnt) res += isap(src, oo);
				return res;
		}
}
using namespace ISAP;
int main() {
		scanf("%d %d", &n, &m);
		cnt = n;
		src = ++cnt, tar = ++cnt;
		init();
		for (int i = 1; i <= m; i++) {
				int x, y, l, r;
				scanf("%d %d %d %d", &x, &y, &l, &r);
				a[i] = (node){x, y, l, r};
				join(x, y, r - l);
				IN[y] += l, IN[x] -= l;
		}
		for (int i = 1; i <= n; i++) {
				if (IN[i] < 0) join(i, tar, -IN[i]);
				else {
						join(src, i, IN[i]);
						flow += IN[i];
				}
		}
		int ans = maxflow(src, tar);
		if (flow == ans) {
				puts("YES");
				for (int i = 1; i <= m; i++) printf("%d\n", a[i].l + E[i * 2 - 1].len);
		} else puts("NO");
		return 0;
}

/*
		先来看有源汇可行流
　　建模方法：
　　建立弧<t,s>，容量下界为0，上界为oo。 
　　然后对这个新图（实际上只是比原图多了一条边）按照无源汇可行流的方法建模，
		如果所有附加弧满流，则存在可行流。
　　求原图中每条边对应的实际流量的方法，同无源汇可行流，只是忽略掉弧<t,s>就好。
　　而且这时候弧<t,s>的流量就是原图的总流量。
　　理解方法：
　　有源汇相比无源汇的不同就在于，源和汇是不满足流量平衡的，那么连接<t,s>之后，
		源和汇也满足了流量平衡，就可以直接按照无源汇的方式建模。
　　注意：这张图的最大流只是对应着原图的一组可行流，而不是原图的最大或最小流。

		有源汇最大流
　　建模方法：
　　首先按照有源汇可行流的方法建模，如果不存在可行流，更别提什么最大流了。
　　如果存在可行流，那么在运行过有源汇可行流的图上（就是已经存在流量的那张图，流量不要清零），
		跑一遍从s到t的最大流（这里的s和t是原图的源和汇，不是附加源和附加汇），就是原图的最大流。
　　理解方法：
　　为什么要在那个已经有了流量的图上跑最大流？因为那张图保证了每条弧的容量下界，在这张图上跑最大流，
		实际上就是在容量下界全部满足的前提下尽量多得获得“自由流量”。
　　注意，在这张已经存在流量的图上，弧<t,s>也是存在流量的，千万不要忽略这条弧。
		因为它的相反弧<s,t>的流量为<t,s>的流量的相反数，且<s,t>的容量为0，所以这部分的流量也是会被算上的。
*/
using namespace std;
typedef long long ll;
const int LEN = 1e5 + 5;
const int oo = (1LL << 31) - 1;
namespace DINIC {
		int tot, n, m, src, tar, qh, qt, cnt, s, t, S, T;
		int ans, flow;
		struct edge {
				int vet, next, len;
		} E[LEN * 2];
		int dis[LEN], gap[LEN], head[LEN], cur[LEN], q[LEN], vis[LEN], IN[LEN];
		void add(int u, int v, int c) {
				E[++tot] = (edge){v, head[u], c};
				head[u] = tot;
		}
		void join(int u, int v, int c) {
				add(u, v, c);
				add(v, u, 0);
		}
		void init() {
				tot = -1;
				for (int i = 1; i <= cnt; i++) head[i] = -1;
		}
		bool bfs() {
				for (int i = 1; i <= cnt; i++) dis[i] = 0;
				qh = qt = 0;
				q[++qt] = src;
				dis[src] = 1;
				while (qh < qt) {
						int u = q[++qh];
						for (int e = head[u]; e != -1; e = E[e].next) {
								int v = E[e].vet;
								if (E[e].len && !dis[v]) {
										dis[v] = dis[u] + 1;
										if (v == tar) return 1;
										q[++qt] = v;
								}
						}
				}
				return dis[tar];
		}
		int dfs(int u, int aug) {
				if (u == tar || !aug) return aug;
				int tmp = 0;
				for (int &e = cur[u]; e != -1; e = E[e].next) {
						int v = E[e].vet;
						if (dis[v] == dis[u] + 1) {
								if (tmp = dfs(v, min(aug, E[e].len))) {
										E[e].len -= tmp;
										E[e ^ 1].len += tmp;
										return tmp;
								}
						}
				}
				return 0;
		}
		int maxflow(int s, int t) {
				src = s, tar = t;
				int res = 0, flow = 0;
				while (bfs()) {
						for (int i = 1; i <= cnt; i++) cur[i] = head[i];
						while (flow = dfs(src, oo)) res += flow;
				}
				return res;
		}
}
using namespace DINIC;
int main() {
		scanf("%d %d %d %d", &n, &m, &s, &t);
		cnt = n;
		S = ++cnt, T = ++cnt;
		init();
		for (int i = 1; i <= m; i++) {
				int x, y, l, r;
				scanf("%d %d %d %d", &x, &y, &l, &r);
				join(x, y, r - l);
				IN[y] += l, IN[x] -= l;
		} 
		for (int i = 1; i <= n; i++) {
				if (IN[i] < 0) join(i, T, -IN[i]);
				else if (IN[i] > 0) {
						flow += IN[i];
						join(S, i, IN[i]);
				}
		}
		join(t, s, oo);
		ans = maxflow(S, T);
		if (ans != flow) puts("please go home to sleep");
		else {
				ans = maxflow(s, t);
				printf("%lld\n", ans);
		}
		return 0;
}

/*
		先来看有源汇可行流
　　建模方法：
　　建立弧<t,s>，容量下界为0，上界为oo。 
　　然后对这个新图（实际上只是比原图多了一条边）按照无源汇可行流的方法建模，
		如果所有附加弧满流，则存在可行流。
　　求原图中每条边对应的实际流量的方法，同无源汇可行流，只是忽略掉弧<t,s>就好。
　　而且这时候弧<t,s>的流量就是原图的总流量。
　　理解方法：
　　有源汇相比无源汇的不同就在于，源和汇是不满足流量平衡的，那么连接<t,s>之后，
		源和汇也满足了流量平衡，就可以直接按照无源汇的方式建模。
　　注意：这张图的最大流只是对应着原图的一组可行流，而不是原图的最大或最小流。

		有源汇最小流
　　有源汇最小流的常见建模方法比较多，我就只说我常用的一种。
　　建模方法：
　　首先按照有源汇可行流的方法建模，但是不要建立<t,s>这条弧。
　　然后在这个图上，跑从附加源ss到附加汇tt的最大流。
　　这时候再添加弧<t,s>，下界为0，上界oo。
　　在现在的这张图上，从ss到tt的最大流，就是原图的最小流。
　　理解方法：
　　我们前面提到过，有源汇可行流的流量只是对应一组可行流，并不是最大或者最小流。
　　并且在跑完有源汇可行流之后，弧<t,s>的流量就是原图的流量。
　　从这个角度入手，我们想让弧<t,s>的流量尽量小，就要尽量多的消耗掉那些“本来不需要经过<t,s>”的流量。
　　于是我们在添加<t,s>之前，跑一遍从ss到tt的最大流，就能尽量多的消耗那些流量啦QwQ。
*/
using namespace std;
typedef long long ll;
const int LEN = 2e5 + 5;
const int oo = (1LL << 31) - 1;
namespace DINIC {
		int tot, n, m, src, tar, qh, qt, cnt, s, t, S, T, ans, flow;
		struct edge {
				int vet, next, len;
		} E[LEN * 2];
		int dis[LEN], gap[LEN], head[LEN], cur[LEN], q[LEN], vis[LEN], IN[LEN];
		void add(int u, int v, int c) {
				E[++tot] = (edge){v, head[u], c};
				head[u] = tot;
		}
		void join(int u, int v, int c) {
				add(u, v, c);
				add(v, u, 0);
		}
		void init() {
				tot = -1;
				for (int i = 1; i <= cnt; i++) head[i] = -1;
		}
		bool bfs() {
				for (int i = 1; i <= cnt; i++) dis[i] = 0;
				qh = qt = 0;
				q[++qt] = src;
				dis[src] = 1;
				while (qh < qt) {
						int u = q[++qh];
						for (int e = head[u]; e != -1; e = E[e].next) {
								int v = E[e].vet;
								if (E[e].len && !dis[v]) {
										dis[v] = dis[u] + 1;
										if (v == tar) return 1;
										q[++qt] = v;
								}
						}
				}
				return dis[tar];
		}
		int dfs(int u, int aug) {
				if (u == tar || !aug) return aug;
				int tmp = 0;
				for (int &e = cur[u]; e != -1; e = E[e].next) {
						int v = E[e].vet;
						if (dis[v] == dis[u] + 1) {
								if (tmp = dfs(v, min(aug, E[e].len))) {
										E[e].len -= tmp;
										E[e ^ 1].len += tmp;
										return tmp;
								}
						}
				}
				return 0;
		}
		int maxflow(int s, int t) {
				src = s, tar = t;
				int res = 0, flow = 0;
				while (bfs()) {
						for (int i = 1; i <= cnt; i++) cur[i] = head[i];
						while (flow = dfs(src, oo)) res += flow;
				}
				return res;
		}
}
using namespace DINIC;
int main() {
		scanf("%d %d %d %d", &n, &m, &s, &t);
		cnt = n;
		S = ++cnt, T = ++cnt;
		init();
		for (int i = 1; i <= m; i++) {
				int x, y, l, r;
				scanf("%d %d %d %d", &x, &y, &l, &r);
				join(x, y, r - l);
				IN[y] += l, IN[x] -= l;
		} 
		for (int i = 1; i <= n; i++) {
				if (IN[i] < 0) join(i, T, -IN[i]);
				else if (IN[i] > 0) {
						flow += IN[i];
						join(S, i, IN[i]);
				}
		}
		ans = maxflow(S, T);
		flow -= ans;
		join(t, s, oo);
		ans = maxflow(S, T);
		if (ans != flow) puts("please go home to sleep");
		else printf("%d\n", ans);
		return 0;
}