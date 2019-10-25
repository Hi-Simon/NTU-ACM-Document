/*
 * Author: Simon
 * 复杂度: O(e·log(n))
 */
namespace Dijkstra{
    struct node{
        int v,w,next;
        node(){}
        node(int v,int w,int next=-1):v(v),w(w),next(next){}
        bool operator <(const node&a)const{
            return w>a.w;
        }
    }g[maxn];
    int head[maxn],cnt=0,dis[maxn];
    bool vis[maxn];
    void addedge(int u,int v,int w){
        g[cnt]=node(v,w,head[u]);
        head[u]=cnt++;
    }
    void init(){
        memset(head,-1,sizeof(head)); cnt=0;
    }
    void Run(int n,int r){
        fill(dis,dis+n+5,INF);dis[r]=0;
        memset(vis,0,sizeof(vis));
        priority_queue<node>q;
        q.push({r,0});
        while(!q.empty()){
            node now=q.top();q.pop();
            int &u=now.v;
            if(vis[u]) continue; vis[u]=1;
            for(int i=head[u];~i;i=g[i].next){
                int &v=g[i].v,&w=g[i].w;
                if(!vis[v]&&dis[u]+w<dis[v]){
                    dis[v]=dis[u]+w;
                    q.push({v,dis[v]});
                }
            }
        }
	}
}