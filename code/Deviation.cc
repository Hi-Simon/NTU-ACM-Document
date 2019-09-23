
/*
 * Author: Simon
 * 功能: 求满足p1/x1<b/y<p2/x2,最小分母(且分子也最小)的分数b/y
 * 复杂度: O(log(n))
 */
void solve(int p1,int x1,int p2,int x2,int &b,int &y){
    int l=p1/x1,r=(p2+x2-1)/x2;
    if(l+1<r){/*若两分数之间有整数，直接返回 */
        b=l+1,y=1;
        return ;
    }
    solve(x2,p2-l*x2,x1,p1-l*x1,y,b);/*否则同时减去l后，分子分母互换 */
    b+=l*y; /*回溯，加回减去的值 */
}