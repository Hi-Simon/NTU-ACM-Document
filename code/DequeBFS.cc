/*
 * Author: Simon
 * 功能: 双端队列BFS
 * 适用范围: 边权值为可能有，也可能没有（由于 BFS 适用于权值为 1 的图，所以一般是 0 or 1）
 *      或者能够转化为这种边权值的最短路问题。例一束光线从(n,m)点向左射出，遇到#可以选择方向不变
 *      或者向上下左右反射光线，问最少选择反射几次能从第一行向左射出
 */
char a[maxn][maxn];
struct node{
    int x,y,step,d;
};
int dir[4][2]={1,0,-1,0,0,1,0,-1};
bool vis[maxn][maxn][4];
bool bfs(int n,int m){
    deque<node>q;
    q.push_front({n,m,0,3});
    while(!q.empty()){
        node now=q.front(),next;q.pop_front();
        if(now.x==1&&now.d==3){cout<<now.step<<endl;return 1;}
        if(vis[now.x][now.y][now.d]) continue;
        vis[now.x][now.y][now.d]=1;
        next=now;
        next.x+=dir[now.d][0],next.y+=dir[now.d][1];
        if(next.x>=1&&next.x<=n&&next.y>=1&&next.y<=m) q.push_front(next); 
        if(a[now.x][now.y]=='#'){
            for(int i=0;i<4;i++){
                next=now;
                next.x+=dir[i][0];
                next.y+=dir[i][1];
                next.step++;next.d=i;
                if(next.x<1||next.x>n||next.y<1||next.y>m||vis[next.x][next.y][i]) continue;
                q.push_back(next);
            }
        }
    }
    return 0;
}