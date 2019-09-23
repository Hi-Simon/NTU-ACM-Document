/*
 * Author: Simon
 * 复杂度: O(N·V),O(N·V),O(V·Sigma( log(Ci) ))
 * 说明: 利用单调队列还可以优化时间复杂度
 */
/*01背包 */
void ZeroOnepark(int V/*背包容量*/,int val/*物品价值*/, int vol/*物品体积*/) {
    for (int j = V; j >= vol; j--) {
        dp[j] = max(dp[j], dp[j - vol] + val);
    }
}

/*完全背包 */
void Completepark(int V/*背包容量*/,int val/*物品价值*/, int vol/*物品体积*/) {
    for (int j = vol; j <= V; j++) {
        dp[j] = max(dp[j], dp[j - vol] + val);
    }
}

/*多重背包 */
void Multiplepark(int val/*物品价值*/, int vol/*物品体积*/, int amount/*物品数量*/) {
    if (vol * amount >= v) {
        Completepark(val, vol);
    } else {
        int k = 1;
        while (k < amount) {
            ZeroOnepark(k * val, k * vol);
            amount -= k; k <<= 1;
        }
        if (amount > 0) {
            ZeroOnepark(amount * val, amount * vol);
        }
    }
}
int main(){
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        Multiplepark(value[i], volume[i], num[i]);
    }
}

/*
 * Author: Simon
 * 功能: 单调队列优化多重背包
 * 复杂度: O(N·V)
 */
int solve(int volume[],int value[],int n,int V){
    pair<int,int> q[maxn];int head=1,tail=0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < volume[i]; j++) {
            q[head = tail = 1] = make_pair(dp[j], 0);
            for (int k = j + volume[i]; k <= V; k += volume[i]) {
                int a = k / volume[i], t = dp[k] - a * value[i];
                while (head <= tail && q[tail].first <= t) tail--;
                q[++tail] = make_pair(t, a);
                while (head <= tail && q[head].second + num[i] < a) head++;
                dp[k] = max(dp[k], q[head].first + a * value[i]);
            }
        }
    }
}