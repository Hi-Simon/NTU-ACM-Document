/* 
 * author：Simon
 * f[m]:可改变当前状态的方式，m为方式的种类，f[m]要在getSG之前先预处理
 * sg[]:0~n的SG函数值
 * mex[]:为x后继状态的集合
 * 若sg值为正数，则先手必赢，否则若为0，则先手必输。
 */
int f[maxn],sg[maxn],mex[maxn];
void getSG(int n/*需要求多少个sg值*/,int m/*有多少种操作方式*/){
    memset(sg,0,sizeof(sg));
    for(int i = 1; i <= n; i++){ /*因为SG[0]始终等于0，所以i从1开始*/
        memset(mex,0,sizeof(mex)); /*每一次都要将上一状态 的 后继集合 重置*/
        for(int j = 0; f[j] <= i && j < m; j++)
            mex[sg[i-f[j]]] = 1;  /*将后继状态的SG函数值进行标记*/
        for(int j = 0;; j++) if(!mex[j]){   /*查询当前后继状态SG值中最小的非零值*/
            sg[i] = j;
            break;
        }
    }
}