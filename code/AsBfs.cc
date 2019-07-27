/*
 * Author: Simon
 * 功能: A*启发式搜索（例：八数码问题）
 */
int Hash[9]={1,1,2,6,24,120,720,5040,40320};
int dir[4][2]={-1,0,1,0,0,-1,0,1};
char d[5]="udlr";
int vis[maxn];
struct node{
    int f[3][3];
    int g,h,hashval,x,y;
    bool operator <(const node a) const{
        return a.g+a.h<g+h;
    }
};
struct path{
    int pre;
    char ch;
}p[maxn];
int get_h(int f[][3]){
    int ans=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(f[i][j]){
                ans+=abs(i-(f[i][j]-1)/3)+abs(j-(f[i][j]-1)%3);
            }
        }
    }
    return ans;
}
bool checkedge(node next){
    if(next.x>=0&&next.y>=0&&next.x<3&&next.y<3) return 1;
    return 0;
}
void As_bfs(node e){
    priority_queue<node>q;
    node now,next;
    for(int i=0;i<9;i++) now.f[i/3][i%3]=(i+1)%9;
    int end_ans=get_hash(now);
    e.h=get_h(e);e.g=0;
    e.hashval=get_hash(e);
    p[e.hashval].pre=-1;
    q.push(e);
    while(!q.empty()){
        now=q.top(); q.pop();
        if (now.hashval == end_ans) {
        	print(now.hashval);
            cout << endl;
            return;
        }
        if(vis[now.hashval]) continue;vis[now.hashval]=1;
        for(int i=0;i<4;i++){
            next=now;
            next.x=now.x+dir[i][0];
            next.y=now.y+dir[i][1];
            if(checkedge(next)){
                swap(next.f[now.x][now.y], next.f[next.x][next.y]);
                next.hashval = get_hash(next);
                if(vis[next.hashval]) continue;
                next.g++; next.h = get_h(next);
                p[next.hashval].pre=now.hashval;
                p[next.hashval].ch=d[i];
                q.push(next);
            }
        }
    } 
}