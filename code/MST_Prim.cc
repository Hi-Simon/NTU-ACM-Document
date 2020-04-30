/*
 * Author: Simon
 * 复杂度: nlog(m)
 * 功能: 适用于求稠密图求MST
 */
namespace Prim{
    int head[maxn],cnt=0;
    bool vis[maxn];
    struct node{
        int v,w,next;
        node(){}
        node(int v,int w,int next):v(v),w(w),next(next){}
        bool operator <(const node a)const{
            return w>a.w;
        }
    }g[maxm];
    void init(){
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));cnt=0;
    }
    void addedge(int u,int v,int w){
        g[cnt]=node(v,w,head[u]);
        head[u]=cnt++;
    }
    int Run(int s,int n){
        priority_queue<node>q;
        q.push(node(s,0));int ans=0;
        while(!q.empty()){
            node now=q.top();q.pop();
            if(vis[now.v]) continue;
            vis[now.v]=1;ans+=now.w;
            for(int i=head[now.v];~i;i=g[i].next){
                if(!vis[g[i].v]) q.push(g[i]);
            }
        }
        return ans;
    }
}