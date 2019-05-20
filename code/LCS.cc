int dp[maxn][maxn];

void LCS(int n1, int n2, int A[], int B[]) {
	for(int i=1; i<=n1; i++) {
		for(int j=1; j<=n2; j++) {
			dp[i][j] = dp[i-1][j];
			if (dp[i][j-1] > dp[i][j]) {
				dp[i][j] = dp[i][j-1];
			}
			if (A[i] == B[j] && dp[i-1][j-1] + 1 > dp[i][j]) {
				dp[i][j] = dp[i-1][j-1] + 1;
			}
		}
	}
}