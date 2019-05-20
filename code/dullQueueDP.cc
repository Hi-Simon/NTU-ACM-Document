int head,tail;
struct node
{
	int val,k;
}q[maxm*2];
void right(int i,int j) {
	while(head<tail&&dp[i-1][j]-sum[i][j-1]>=q[tail-1].val) tail--;//dp[i-1][k]-sum[i][k]
	q[tail].val=dp[i-1][j]-sum[i][j-1];
	q[tail++].k=j;
	while(head==-1||(head<tail&&j-q[head].k>t)) head++;//保证步数不大于限制条件
	dp[i][j]=max(dp[i][j],q[head].val+sum[i][j]);//dp[i][j]=max(dp[i][j],dp[i-1][k]-sum[i][k-1]+sum[i][j])
}
void left(int i,int j) {
	while(head<tail&&dp[i-1][j]+sum[i][j]>=q[tail-1].val) tail--;//dp[i-1][k]+sum[i][k];
	q[tail].val=dp[i-1][j]+sum[i][j];
	q[tail++].k=j;
	while(head==-1||(head<tail&&q[head].k-j>t)) head++;//保证步数不大于限制条件
	dp[i][j]=max(dp[i][j],q[head].val-sum[i][j-1]);//dp[i][j]=max(dp[i][j],dp[i-1][j]+sum[i][k]-sum[i][j-1])
}
void solve() {
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) dp[i][j]=-INF;
	for(int i=1;i<=m;i++){//第一行初始化
		if(abs(x-i)>t) continue;
		if(i<=x) dp[1][i]=sum[1][x]-sum[1][i-1];
		else dp[1][i]=sum[1][i]-sum[1][x-1];
	}
	for(int i=2;i<=n;i++) {
		head=tail=0;
		for(int j=m;j>=1;j--) left(i,j);
		head=tail=0;
		for(int j=1;j<=m;j++) right(i,j);
	}
}