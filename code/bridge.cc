class bcc_bridges {
	public:
		struct edge {
			int y;
			edge * next;
		};
		edge e[M], *li[N];
		int etop;
		void init() {
			memset(li, 0, sizeof(li));
			etop = 0;
		}
		inline void add_edge(int u, int v) {
			e[etop].y = v;
			e[etop].next = li[u];
			li[u] = &e[etop++];
		}
		std::vector<std::pair<int, int>> briges;
		int dfn[N],low[N];
		int clk;
		void dfs(int u, int fa) {
			dfn[u]=low[u]=++clk;
			int v;
			for (edge * t = li[u]; t; t = t->next) {
				v = t->y;
				if (!dfn[v]) {
					dfs(v,u);
					low[u]=std::min(low[u],low[v]);
					if(low[v] > dfn[u])
						briges.emplace_back(u, v); // u <-> v is a bridge
				}
				else if(dfn[v] < dfn[u] && v != fa)
					low[u]=std::min(low[u],dfn[v]);
			}
		}
		void find_bridge(int n) {
			clk = 0;
			std::fill(dfn + 1, dfn + n + 1, 0);
			std::fill(low, low + n + 1, 0);
			for (int i = 1; i <= n; ++i) {
				if (!dfn[i])
					dfs(i, 0);
			}
		}
	};
