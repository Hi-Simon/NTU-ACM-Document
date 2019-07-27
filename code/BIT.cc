/*
 * Author: Simon
 * 功能: 单点修改,区间查询
 */
int tree[maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void update(int x,int val){ /*将x处的值增加val */
    for(int i=x;i<maxn;i+=lowbit(i)){
        tree[i]+=val;
    }
}
inline int query(int x){ /*求[1,x]的所有值的和 */
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        ans+=tree[i];
    }
    return ans;
}
/*
 * Author: Simon
 * 功能: 区间修改，单点查询
 */
int a[maxn];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i),update(i,a[i]-a[i-1]); /*初始化 */
   	update(2,10);update(8,-10); /*将区间[2,7]的所有数的值增加10 */
   	printf("%d\n%",query(4)); /*查询[4]处的值 */
}
/*
 * Author: Simon
 * 功能: 单点修改,区间最值
 */
int tree[maxn],a[maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void update(int x,int val,int n){
    for(int i=x;i<=n;i+=lowbit(i)){
        tree[i]=val;
        for(int j=1;j<lowbit(i);j<<=1){
            tree[i]=max(tree[i],tree[i-j]);
        }
    }
}
inline int query(int x,int y){
    int ans=0;
    while(x<=y){
        ans=max(ans,a[y]);
        for(y-=1;y-lowbit(y)>=x;y-=lowbit(y)){
            ans=max(ans,tree[y]);
        }
    }
    return ans;
}
/*
 * Author: Simon
 * 功能: 区间修改，区间查询
 * 若要修改的区间为[x,y]，则要更新的为update(x,val);update(y+1,-val);
 * 若要查询的区间为[x,y]，则查询的为query(y)-query(x-1);
 */
int tree1[maxn],tree2[maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void update(int x,int val){
    for(int i=x;i<maxn;i+=lowbit(i)){
        tree1[i]+=val;tree2[i]+=x*val;
    }
}
inline int query(int x){
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        ans+=(x+1)*tree1[i]-tree2[i];
    }
    return ans;
}
int a[maxn];
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i),update(i,a[i]-a[i-1]); /*初始化 */
    update(2,10);update(8,-10); /*将区间[2,7]所有的值增加10 */
    printf("%d\n",query(6)-query(4-1)); /*查询区间[4,6]的和 */
}
/*
 * Author: Simon
 * 功能: 求第k小值
 */
int tree[maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void update(int x,int val){ /*将x处的值增加val，此处val一般为1 */
    for(int i=x;i<maxn;i+=lowbit(i)){
        tree[i]+=val;
    }
}
inline int query(int x){ /*求[1,x]的所有值的和 */
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i)){
        ans+=tree[i];
    }
    return ans;
}
inline get_kth(int k,int n){ /*求第k小的数的值，n为最大的数的值，一般比最大数的值大1 */
    int ans=0,cnt=0; /*ans为当前是哪个数，cnt为上个数排名为多少 */
    for(int i=log2(n);i>=0;i--){
        ans+=1<<i;
        if(ans>=n||cnt+tree[ans]>=k) ans-=1<<i; /*若当前数大于最大的数，或者排名大于k，回退 */
        else cnt+=tree[ans];
    }
    return ans+1;
}