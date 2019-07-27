/*
 * Author: Simon
 * 功能: 单调栈求某子序列中的最小值乘以子序列所有元素和最大
 * 最基础的应用就是给定一组数，针对每个数，寻找它和它右边第一个比它大的数之间有多少个数。
 * 给定一序列，寻找某一子序列，使得子序列中的最小值乘以子序列的长度最大。
 * 给定一序列，寻找某一子序列，使得子序列中的最小值乘以子序列所有元素和最大。
 * 给定一序列，在限定每个字母出现次数的情况下，求其字典序最小的k长子序列。可求后缀和，
 *      当一个字母出栈时，判断此后位置当前字母的个数是否满足限制条件，若满足出栈，否则不出栈。
 * 复杂度: O(n)
 */
int Stack[maxn],lft[maxn],top=0,ans=0,a[maxn];
a[n+1]=INF;
for(int i=1;i<=n+1;i++){
    int t=i;lft[i]=i;
    while(top&&a[i]<a[Stack[top]]){
        t=Stack[top--];
        ans=max(ans,(i-lft[t])*a[t]);
    }
    Stack[++top]=i;
    lft[i]=lft[t];
}
/*
 * Author: Simon
 * 功能: 求区间长度小于k的区间最小值
 * 复杂度: O(n)
 */
int q[maxn],l=1,r=0,a[maxn];
for(int i=1;i<=n;i++){
    while(l<=r&&a[i]<=a[q[r]]) r--; //维护单调递增区间
    q[++r]=i;
    while(l<=r&&i-q[l]>=k) l++; //维护不大于k的区间长度
    if(i-k>=0) return a[q[l]];
}