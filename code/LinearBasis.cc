/*
 * Author: Simon
 * 功能: 线性基的插入
 */
int a[maxn];
void insert(int val){
    for(int i=60;i>=0;i--){
        if(val&(1LL<<i)){
            if(!a[i]){a[i]=val;break;}
            else val^=a[i];
        }
    }
}
/*
 * Author: Simon
 * 功能: 将上三角矩阵线性基化为对角矩阵形式
 */
int p[maxn],cnt=0;
void rebuild(int n){ 
    for(int i=60;i>=0;i--){
        for(int j=i-1;j>=0;j--){
            if(a[i]&(1LL<<j)) a[i]^=a[j];
        }
    }cnt=0;
    for(int i=60;~i;i--){
        if(a[i]) p[cnt++]=a[i];
    }
}
/*
 * Author: Simon
 * 功能: 线性基的合并
 */
void merge(int *g){
    for(int i=0;i<=60;i++){
        if(g[i]) insert(g[i]);
    }
}
/*
 * Author: Simon
 * 功能: 线性基查询最大值
 */
int query(){
    int ans=0;
    for(int i=60;~i;i--){
        if(ans^a[i])>ans) ans^=a[i];
    }
    return ans;
}
/*
 * Author: Simon
 * 功能: 线性基查询最小值
 */
int query(){
    for(int i=0;i<=60;i++){
        if(a[i]) return a[i];
    }
    return 0;
}
/*
 * Author: Simon
 * 功能: 线性基化查询第k小值（无重复）
 */
int query(int k,int cnt) /*需先化为对角矩阵 */
    int ans=0;
    for(int i=0;i<cnt;i++){}
        if(k>>i&1LL) ans^=p[i];
    }
}
/*
 * Author: Simon
 * 功能: 在线查询区间最大异或和
 * 按右端点分类，构造n个线性基，并记录每个值插入的位置
 * 同时保证插入时靠右的值具有优先插入权
 */
int a[maxn],base[maxn][25]/*最大位置到i的线性基 */,pos[maxn][25];
void insert(int val,int p){
    int k=p;
    for(int i=0;i<=20;i++) base[p][i]=base[p-1][i],pos[p][i]=pos[p-1][i]; /*复制最大位置为p-1的线性基，在此基础上插入 */
    for(int i=20;i>=0;i--) if(val>>i&1){
        if(!base[p][i]){
            base[p][i]=val;
            pos[p][i]=k;
            break;
        }
        if (k > pos[p][i]) {
            swap(pos[p][i], k); /*位置大的优先,注意交换的位置是k，不是原数p */
            swap(base[p][i], val);
        }
        val ^= base[p][i];
    }
}
int query(int l,int r){
	int ans=0;
	for(int i=20;i>=0;i--){
		if((ans^base[r][i])>ans&&pos[r][i]>=l) ans^=base[r][i];
	}
	return ans;
}
/*
 * Author: Simon
 * 功能: 线性基查询q在n个数的任意组合的异或值的排名(有重复)
 * n个数，它们随意组合的异或值有2^n个数，但是去重后只有2^r个数，r为线性基的个数。
 * 所以对于每个数它们出现的次数一定相同，为2^(n-r)次。
 */
void rebuild(int n){ /*线性基的重建，将上三角矩阵转化为对角矩阵 */
    for(int i=60;i>=0;i--){
        for(int j=i-1;j>=0;j--){
            if(a[i]&(1LL<<j)) a[i]^=a[j];
        }
    }cnt=0;
    for(int i=0;i<=60;i++){
        if(a[i]) p[cnt++]=i;
    }
}
int query(int q){
	int ans=0;
	for(int i=0;i<cnt;i++) if(q&(1LL<<p[i])) ans=(ans+(1<<i));
	return ans;
}