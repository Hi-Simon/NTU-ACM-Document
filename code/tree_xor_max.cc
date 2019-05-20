// 可持久化01Trie+DFS序 子树上的点抑或最大值：
// written by calabash_boy

#include <iostream>
#include <cstdio>
using namespace std;  
const int MAX = 1e5+100;  
int bas[35];  int nxt[MAX<<5][2];  
int root[MAX];  int sum[MAX<<5];  
int n,q;  vector<int>E[MAX];  
int st[MAX],en[MAX],rk[MAX];  
int a[MAX];  int cnt;  int tot;  
void sheet(){  
	bas[0]=1;  
	for (int i=1;i<=30;i++){  
		bas[i] = bas[i-1]<<1;  
	}  
}  
void init(){  
	for (int i=0;i<=n;i++){  E[i].clear(); }  
	cnt =tot=0;  
	memset(nxt[0],0,sizeof nxt[0]);  
}  
void input(){  
	for (int i=1;i<=n;i++){  scanf("%d",a+i);  }  
	for (int u=2;u<=n;u++){  
		int v;  scanf("%d",&v);  
		E[u].push_back(v);  E[v].push_back(u);  
	}  
}  
void dfs(int node ,int  father ){  
	st[node] = ++tot;  rk[tot] = node;  
	for (int des:E[node]){  
		if(des==father){  continue; }  
		dfs(des,node);  
	}  
	en[node] = tot;  
}  
int create(){  
	cnt++;  
	memset(nxt[cnt],0,sizeof nxt[cnt]);  
	return cnt;  
}  
int insert(int rt,int val){  
	int y = ++cnt;  int x = rt;  int res = y;  
	for (int i=30;i>=0;i--){  
		sum[y] = sum[x]+1;  
		nxt[y][0] = nxt[x][0];  nxt[y][1] = nxt[x][1];  
		int t = val&bas[i];  
		t>>=i;  
		nxt[y][t] = create();  
		y = nxt[y][t];  x = nxt[x][t];  
	}  
	sum[y] = sum[x]+1;  
	return res;  
}  
int query(int l,int r,int val){  
	int res =0; int x = l; int y = r;  
	for (int i=30;i>=0;i--){  
		int t = val&bas[i];  
		t>>=i;  
		if (sum[nxt[y][!t]]-sum[nxt[x][!t]]){  
			y = nxt[y][!t];  x = nxt[x][!t];  
			res+=bas[i];  
		}else{  
			y = nxt[y][t];  x = nxt[x][t];  
		}   
	}  
	return res;  
}  
void solve(){  
	dfs(1,0);  
	for (int i=1;i<=n;i++){  
		root[i] = insert(root[i-1],a[rk[i]]);  
	}  
	while (q--){  
		int nod,x;  
		scanf("%d%d",&nod,&x);  
		printf("%d\n",query(root[st[nod]-1],root[en[nod]],x));  
	}  
}  
int main(){  
	sheet();  
	while (scanf("%d%d",&n,&q)!=EOF){  
		init();  
		input();  
		solve();  
	}   
	return 0;  
}  

