for (int x = 0; x < n; x++){//枚举长度
	for (int i = 1; i + x <= n; i++){//枚举起点
		dp[i][i] = 1;
		int j = x + i;//终点
		dp[i][j] = dp[i + 1][j] + 1;
		for (int k = i + 1; k <= j; k++) {
			if (a[i] == a[k])
				dp[i][j] = min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
		}
	}
}
