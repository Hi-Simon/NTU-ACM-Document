int arr[maxn], n;

template<class Cmp>  
int LIS (Cmp cmp) {  
	static int m, end[maxn];  
	m = 0;  
	for (int i=0; i<n; i++) {  
		int pos = lower_bound(end, end+m, arr[i], cmp)-end;  
		end[pos] = arr[i], m += pos==m;  
	}  
	return m;  
}  

bool greater1(int value) {  
	return value >=1;  
}  

/*********
	std::cout << LIS(std::less<int>()) << std::endl;         //严格上升  
    std::cout << LIS(std::less_equal<int>()) << std::endl;   //非严格上升  
    std::cout << LIS(std::greater<int>()) << std::endl;      //严格下降  
    std::cout << LIS(std::greater_equal<int>()) << std::endl;//非严格下降  
    std::cout << count_if(a,a+7,std::greater1) << std::endl; //计数  
**********/
/*
 * Author: Simon
 * 功能: 求最长不下降子序列的长度
 * 复杂度: O(nlog(n))
 */
int solve(int n,int a[]){
    int dp[maxn]; memset(dp, INF, sizeof(dp));
    for(int i=1;i<=n;i++){
        *upper_bound(dp+1,dp+n+1,a[i])=a[i];
    }
    int ans=lower_bound(dp+1,dp+n+1,INF)-dp;
    return ans;
}
/*
 * Author: Simon
 * 功能: 求最长上升子序列
 * 复杂度: O(nlog(n))
 */
vector<int> solve(int n,int p[]){
    vector<int>f;f.push_back(0);
    int a[n+5]; /*记录每个数的前一个数是多少 */
    for(int i=1;i<=n;i++){
        auto it=lower_bound(f.begin(),f.end(),p[i]);
        if(it==f.end()){
            a[p[i]]=f.back();
            f.push_back(p[i]);
        }
        else{
            *it=p[i];it--;
            a[p[i]]=*it;
        }
    }
    vector<int>vis; /*最长上升子序列 */
    for(int t=f.back();t;t=a[t]) vis.push_back(t);
    reverse(vis.begin(),vis.end());
    return vis;
}
/*
 * Author: Simon
 */
int a[maxn];/*原始数组 */
memset(f,INF,sizeof(int)*(n+2));
for(int i=1;i<=n;i++){ //nlog(n)求最长上升子序列
    int j = lower_bound(f + 1, f + n + 1, a[i]) - f;
    End[i] = j; //以i为终点的最长严格上升子序列长度为j
    f[j] = a[i];
}
memset(g,0,sizeof(int)*(n+2));
for (int i = n; i >= 1; i--) {
    int j=lower_bound(g+1,g+n+1,-a[i])-g;
    Start1[i]=j; //以i为起点的最长严格上升子序列的长度为j
    g[j]=-a[i];
}
memset(g,INF,sizeof(int)*(n+2));
reverse(a+1,a+n+1);
for(int i=1;i<=n;i++){ //nlog(n)求最长上升子序列
    int j = lower_bound(g + 1, g + n + 1, a[i]) - g;
    Start[n-i+1] = j; //以i为起点的最长严格下降子序列长度为j
    g[j] = a[i];
}
memset(f,0,sizeof(int)*(n+2));
for (int i = n; i >= 1; i--) {
    int j = lower_bound(f + 1, f + n + 1, -a[i]) - f;
    End1[n-i+1] = j; //以i为终点的最长严格下降子序列的长度为j
    f[j] = -a[i];
}