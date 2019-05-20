int a[maxn],bit[maxn];//a为分解整数数组，bit数组为10^(i-1)
pair<int,int>dp[maxn][2000];//first=满足条件的数个数，second=满足条件的数的和
bool vis[maxn][2000];
pair<int,int> dfs(int pos,int sta,int num,bool lead,bool limit){//求满足条件的所有数的和
	if(pos==0) return make_pair(1,0);//计数
	if(!limit&&!lead&&vis[pos][sta]) return dp[pos][sta];
	if(!limit&&!lead) vis[pos][sta]=1;
	int up=limit?a[pos]:9,t,tt; pair<int,int>tmp,ans;
	for(int i=0;i<=up;i++){
		if(num>=k&&!(sta&(1<<i))) continue;//不满足条件，跳出
		if(lead&&!i) t=0,tt=0;
		else t=(sta|(1<<i)),tt=(sta&(1<<i))?num:num+1;
		tmp=dfs(pos-1,t,tt,lead&&!i,limit&&i==up);
		ans.first+=tmp.first;ans.first%=mod;//满足条件的数的个数
		ans.second+=tmp.first*bit[pos]%mod*i%mod+tmp.second;ans.second%=mod;//满足条件的数的和 10+11+...+19=9*(10*1)+45
	}
	if(!limit&&!lead) dp[pos][sta]=ans;
	return ans;
}