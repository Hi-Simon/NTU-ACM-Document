int Phi(int n) {
    int m = sqrt(n + 0.5);
    int ans = n;
    for (int i = 2; i <= m; ++i) {
        if (n % i == 0) {
            ans = ans - ans / i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans - ans / n;
    return ans;
}
/*
 * Author: Simon
 * 复杂度: O(n)
 * 功能: 求[1,n]小于i且与i互质的数的个数phi(i)
 */
int prime[maxn], phi[maxn], cnt = 0;
bool vis[maxn];
void Euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}