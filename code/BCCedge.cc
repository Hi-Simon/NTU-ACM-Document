//Author: XieNaoban
//在求桥的基础上修改
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>

class CutEdge {
private:
	int N;
	int clk, pre[Maxn];

	int DFS(int u, int f) {
		int lowu = pre[u] = ++clk;
		for (auto e = G[u].begin(); e != G[u].end(); ++e) {
			int v = *e;
			if (!pre[v]) {
				int lowv = DFS(v, u);
				lowu = min(lowu, lowv);
				if (lowv > pre[u]) {
					Cut[u].insert(v);
					Cut[v].insert(u);
				}
			}
			else if (pre[u] > pre[v]) {
				int cnt = 0; //重复边的处理
				for (const auto &e : G[u]) if (e == v) ++cnt;
				if (cnt > 1 || v != f) {
					lowu = min(lowu, pre[v]);
				}
			}
		}
		return lowu;
	}

	void DFS2(int u, int id) {
		ID[u] = id;
		for (const auto &v : G[u]) if (!ID[v]) {
			if (Cut[u].count(v)) {
				++Num;
				G2[id].push_back(Num);
				G2[Num].push_back(id);
				DFS2(v, Num);
			}
			else DFS2(v, id);
		}
	}

public:
	vector<int> G[Maxn];
	set<int> Cut[Maxn];

	vector<int> G2[Maxn]; //缩点后的图（以ID为结点）
	int ID[Maxn]; //每个点所在的子图
	int Num; //ID个数

	void Clear(int n) {
		N = n;
		memset(ID, 0, sizeof(ID));
		memset(pre, 0, sizeof(pre));
		for (int i = 1; i <= N; ++i) {
			G[i].clear();
			G2[i].clear();
			Cut[i].clear();
		}
		clk = 0;
		Num = 1;
	}

	void AddEdge(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(u);
	}

	void Find() {
		for (int i = 1; i <= N; ++i)
			if (!pre[i])
				DFS(i, -1);
	}

	//求边双联通部分
	int BCC() { //要求先运行Find
		DFS2(1, Num);
		return Num;
	}
};