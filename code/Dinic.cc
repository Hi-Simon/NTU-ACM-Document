/*
 * Author: Simon,Ttmq36
 * 复杂度: O(V^2·E)
 */
namespace Dinic{
    struct node{
        int v,w,next;
        node(){}
        node(int v,int w,int next):v(v),w(w),next(next){}
    }g[maxn<<1];
    int head[maxn],cur[maxn],cnt=0;
    int dep[maxn];
    void init(){
        memset(head,-1,sizeof(head));cnt=0;
    }
    void addedge(int u,int v,int w){
        g[cnt]=node(v,w,head[u]);
        head[u]=cnt++;
        g[cnt]=node(u,0,head[v]);
        head[v]=cnt++;
    }
    bool bfs(int s,int t){
        memset(dep,0,sizeof(dep));
        queue<int>q;q.push(s);
        dep[s]=1; cur[s]=head[s];
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];~i;i=g[i].next){
                int &v=g[i].v,&w=g[i].w;
                if(!dep[v]&&w>0){
                    dep[v] = dep[u] + 1;
                    cur[v] = head[v];
                    q.push(v);
                }
            }
        }
        if(!dep[t]) return 0;
        return 1;
    }
    int dfs(int s,int t,int f){
        if(s==t) return f;
        int flow=0,u=s;
        for(int &i=cur[u];~i;i=g[i].next){
            int &v=g[i].v,&w=g[i].w;
            if(dep[u]+1==dep[v]&&w>0){
                int d=dfs(v,t,min(f,w));
                if(d>0){
                    flow+=d; f-=d;
                    g[i].w-=d,g[i^1].w+=d;
                    if(f<=0) break;
                }
            }
        }
        if(!flow) dep[u]=-INF;
        return flow;
    }
    int maxFlow(int s,int t){
        int ans=0;
        while(bfs(s,t)){
            ans+=dfs(s,t,INF);
        }
        return ans;
    }
}