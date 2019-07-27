/*
 * Author: Simon
 * 复杂度: O(ne)
 */
bool SPFA(int n,int r){
    memset(dis,INF,sizeof(dis));dis[r]=0;
    memset(vis,0,sizeof(vis));vis[r]=1;
    memset(ccnt,0,sizeof(ccnt));ccnt[r]=1;
    queue<int>q;q.push(r);
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        for(int i=head[u];~i;i=g[i].next){
            int &v=g[i].v,&w=g[i].w;
            if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    q.push(v);vis[v]=1;
                    if(++ccnt[v]>n) return 1;
                }
            }
        }
    }
    return 0;
}