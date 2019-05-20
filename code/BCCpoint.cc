//Author: CookiC
#include <stack>
#include <vector>
#define maxn 1000
using namespace std;

class BCC{
private:
	int clk, cnt;
	int pre[maxn];
	stack<int> s;
	
	int DFS(int u,int f){
		int lowu = pre[u] = ++clk;
		int child = 0;
		s.push(u);
		for (auto it = G[u].begin(); it != G[u].end(); ++it){
			int v = *it;
			if (!pre[v]){
				s.push(u);
				++child;
				int lowv = DFS(v, u);
				if (lowu > lowv)
					lowu = lowv;
				if (lowv >= pre[u]){
					iscut[u] = 1;
					++cnt;
					int x;
					do{
						x = s.top();
						s.pop();
						if (num[x] != cnt)
							num[x] = cnt;
					}while (x != u);
				}
			}
			else if (pre[v] < pre[u] && v != f){
				if (lowu > pre[v])
					lowu = pre[v];
			}
		}
		if (f < 0 && child == 1)
			iscut[u] = 0;
		return lowu;
	}
public:
	vector<int> G[maxn];
	bool iscut[maxn];
	int num[maxn];
	
	void Clear(int n){
		for (int i = 0; i < n; ++i)
			G[i].clear();
	}

	void AddEdge(int u,int v){
		G[u].push_back(v);
		G[v].push_back(u);
	}

	void Find(){
		int i;
		memset(pre, 0, sizeof(pre));
		memset(iscut, 0, sizeof(iscut));
		memset(num,0,sizeof(num));
		clk = cnt = 0;
		for (i = 0; i < n; ++i)
			if (!pre[i]){
				while(!s.empty())
					s.pop();
				DFS(i,-1);	
			}
	}
};