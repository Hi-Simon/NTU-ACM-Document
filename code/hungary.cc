// 二分图最大团=补图最大独立集=两边所有的顶点-补图最大匹配数
#include <iostream>
using namespace std;
#define maxn 25
bool map[maxn][maxn];   //存图
bool mark[maxn];        //寻找增广路时的标志数组
int n, m;               //A,B集合中的点数
int cx[maxn], cy[maxn]; //匹配到的顶点序号

int findpath(int u) {
    int i, j;
    for (int i = 0; i < n; ++i) {
        if (map[u][i] && !mark[i]) {
            mark[i] = 1;
            if (cy[i] == -1 || findpath(cy[i])) {
                cy[i] = u;
                cx[u] = i;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch() {
    int ans = 0, i, j;
    for (int i = 0; i < n; ++i) cx[i] = -1;
    for (int i = 0; i < n; ++i) cy[i] = -1;
    for (int i = 0; i < n; ++i) {
        if (cx[i] == -1) {
            for (int j = 0; j < n; ++j) mark[j] = 0;
            ans += findpath(i);
        }
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++)
                map[i][j] = 1;
        }
        for (int i = 1; i <= m; i++) {
            int x, y; cin >> x >> y;
            map[x - 1][y - 1] = 0;
        }
        cout << 2 * n - maxmatch() << endl;
    }
    return 0;
}