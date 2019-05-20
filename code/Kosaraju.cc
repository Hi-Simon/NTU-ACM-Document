#include <vector>
#include <algorithm>

const int maxn = "Edit";

class Kosaraju {
private:
	std::vector<int> s[maxn],g[maxn];
	bool vis[maxn]={0};
public:
	int st[maxn], top=0, contract[maxn]={0};
	int n, m;
	void dfs(int x){
		vis[x]=1;
		for(int i=0;i<(int)s[x].size();++i){
			if(!vis[s[x][i]])dfs(s[x][i]);
		}
		st[top++]=x;
	}
	void dfs2(int x,int k){
		if(contract[x])return;
		contract[x]=k;/*x屬於第k個contract*/
		for(int i=0;i<(int)g[x].size();++i){
			dfs2(g[x][i],k);
		}
	}	
	void addedge(int a, int b) {
		s[a].push_back(b);
		g[b].push_back(a);
	}
	void kosaraju() {
		for(int i=0;i<n;++i){
			if(!vis[i]) {
				dfs(i);
			}
		}
		for(int i=top-1,t=0;i>=0;--i){
			if(!contract[st[i]]) {
				dfs2(st[i],++t);
			}
		}
	}
};