/*
 * Author: Simon
 * 功能: 求强连通分量
 */
int dfn[maxn],low[maxn],Stack[maxn],Belong[maxn];
int index=0,scnt=0,bcnt=0;
void Tarjan(int u){
    dfn[u]=low[u]=++index;
    Stack[++scnt]=u;vis[u]=1;
    for(int i=head[u];~i;i=g[i].next){
        int &v=g[i].v;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        bcnt++;int t;
        do{
            t=Stack[scnt--];vis[t]=0;
            Belong[t]=bcnt;
        }while(t!=u);
    }
}
void solve(int n){
    memset(dfn,0,sizeof(dfn));
    index=bcnt=scnt=0;
    for(int i=1;i<=n;i++){
        if(!dfn[i]) Tarjan(i);
    }
}
/*
 * Author: Simon
 * 功能: 缩点建立新图
 */
 for(int u=1;u<=n;u++){
	for(int i=head1[u];~i;i=g[i].next){
		int &v=g[i].v;
		if(Belong[u]!=Belong[v]){
			addedge(g2,head2,cnt2,Belong[v],Belong[u]);
			rdu[Belong[u]]++;
		}
	}
}
/*
 * Author: Simon
 * 功能: 双联通算法
 */
int dfn[maxn],low[maxn],Stack[maxn],Belong[maxn];
int index=0,scnt=0,bcnt=0; 
int tarjan(int u,int fa)
{
    dfn[u]=low[u]++index;
    for(int i=head[u];~i;i=g[i].next){
        int &v=g[i].v;
        if(!dfn[v])
        {
            Stack[++scnt]=v;/*搜索到的点入栈  */
            tarjan(edges[i].to,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])/*是割点或根  */
            {
                bcnt++;int t;
                do{
                    t=Stack[scnt--];
                    Belong[t]=bcnt;
                }while(t!=v);
                while(stack[top]!=edges[i].to)/*将点出栈直到目标点  */
                    bcc[num].push_back(stack[top--]);
                bcc[num].push_back(stack[top--]);/*目标点出栈  */
                bcc[num].push_back(u);/*不要忘了将当前点存入bcc  */
            }
        }
        else if(edges[i].to!=fa)
            lowu=min(lowu,dfn[edges[i].to]);
    }
}