/*
Author: Simon
返回自由变量个数，-1表示无解。
若矩阵的秩=增广矩阵的秩=变量个数，则有唯一解
若矩阵的秩=增广矩阵的秩<变量个数，则有无穷多解
若矩阵的秩<增广矩阵的秩,则无解

注：若用于开关问题，则使用注释部分。
复杂度: O(n^3)
*/
const double/*开关问题：int*/ eps = 1e-10;
// int n/*方程个数*/, m/*变量个数*/;
double/*开关问题：int*/ a[maxn][maxn]/*增广矩阵(n*(m+1)),开关问题：a[i][j]表示与j关联的开关为i*/, x[maxn]/*解*/; 
bool free_x[maxn]; /*是否为自由变量*/
int free_xx[maxn]/*用于自由变量*/,free_num=0/*自由变量个数*/;

void printMatrix(double/*开关问题：int*/ a[maxn][maxn],int n,int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++){
			cout<<left<<setw(20)<<a[i][j];
		}
		cout<<endl;
	}
}

inline int sgn(double/*开关问题：int*/ x) { return (x > eps) - (x < -eps)/*开关问题：x?1:0*/; } //若x不接近0，返回1，否则返回0。

int Gauss(double/*开关问题：int*/ a[maxn][maxn]/*增广矩阵*/, int n/*方程个数*/, int m/*变量个数*/) {
    memset(free_x, 1, sizeof(free_x)); memset(x, 0, sizeof(x));
    int r = 0/*第r行*/, c = 0/*第c列*/;
    while (r < n && c < m) {/*化为上三角矩阵*/
        int m_r = r;
		for(int i=r+1;i<n;i++) if (fabs(a[i][c]) > fabs(a[m_r][c])) m_r = i; /*从第r行开始，找出第c列绝对值最大的 */
        if (m_r != r){
			for(int j=c;j<m+1;j++) swap(a[r][j], a[m_r][j]); /*将值最大的放到第r行*/
		}
        if (!sgn(a[r][c])) { /*判断a[r][c]是否为零*/
            free_xx[free_num++]=c; /*记录自由变量*/
            a[r][c] = 0; ++c;
            continue;
        }
		for(int i=r+1;i<n;i++){ /*将第c列化为上三角*/
            if (a[i][c]) {
                double/*开关问题：int*/ t = a[i][c] / a[r][c];/*开关问题：删除*/
                for(int j=c;j<m+1;j++) a[i][j] -= a[r][j] * t/*开关问题：a[i][j]^=a[r][j]*/;
            }
		}
		++r; ++c;
    }
    for(int i=r;i<n;i++) if(sgn(a[i][m])) return -1;/*若xi=0,b!=0则无解*/
    if (r < m) { /*此时r为矩阵的秩,也是增广矩阵的秩*/
		for(int i=r-1;i>=0;i--){
            int f_cnt = 0, k = -1;
			for(int j=0;j<m;j++){
                if (sgn(a[i][j]) && free_x[j]) {
                    ++f_cnt; k = j;
                }
			}
            if(f_cnt > 0) continue;
            double/*开关问题：int*/ s = a[i][m];
			for(int j=0;j<m;j++) if (j != k) s -= a[i][j] * x[j]/*开关问题：s^=(a[i][j]&x[j])*/;
            x[k] = s / a[i][k]/*开关问题：x[k]=s*/;/**/ free_x[k] = 0;
        }
		return m - r;/*有无穷多解，且自由变量的个数为m-r*/
    }
	for(int i=m-1;i>=0;i--){/*回代解方程组*/
        double/*开关问题：int*/ s = a[i][m];
		for(int j=i+1;j<m;j++) s -= a[i][j] * x[j]/*开关问题：s^=(a[i][j]&x[j])*/;
        x[i] = s / a[i][i]/*开关问题：x[i]=s*/;
    }
    return 0;/*有唯一解*/
}
/*
    当线性方程组的解有无穷多时，可给自由变量任意合理的值，
然后通过自由变量获得的值，回代求得其他变量的值。
可用于开关问题中，用最少的操作使得所有开关达到一定状态

位运算开关问题模板：
*/
int solve(int n,int m,int b/*自由变量的个数*/){
    int ans=INF;
    for(int i=0;i<(1<<b);i++){ /*枚举自由变量的 取值状态*/
        int num=0;
        for(int j=0;j<b;j++){
            if(i&(1<<j)) x[free_xx[j]]=1,num++; /*根据状态将自由变量赋值*/
            else x[free_xx[j]]=0;
        }
        for(int j=m-b-1;j>=0;j--){ /*根据自由变量的值回代求解其他变量*/
            int id; for(id=j;id<m;id++) if(a[j][id]) break;

            int s = a[j][m];
            for(int k=id+1;k<m;k++)  s^=(a[j][k]&x[k]);
            x[id]=s; 

            num+=x[id];
        }
        ans=min(ans,num);
    }
    return ans;
}