int t=maxn-1;
memset(dp,-1,sizeof(dp));dp[0][0]=0;
for(int i=0;i<t;i++){//枚举每一个起点
	for(int j=0;j<(1<<n);j++) dp[i+1][j]=max(dp[i+1][j],dp[i][j]); //更新所有状态的值
	for(int j=0;j<g[i].size();j++){//枚举当前起点的所有终点
		for(int k=0;k<(1<<n);k++){
			if(dp[i][k]!=-1){
				dp[g[i][j].fin][k|(1<<g[i][j].num)]=max(dp[g[i][j].fin][k|(1<<g[i][j].num)],dp[i][k]+g[i][j].val);
				//枚举所有结束时间，结束时间由起始时间转移过来
			}
		}
	}
}