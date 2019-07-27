//Author: Simon
#define maxn 16 
const int mod=1e9+7;
struct Matrix{ //矩阵类
    int m[maxn][maxn];
    Matrix(){
        for(int i=0;i<maxn;i++) for(int j=0;j<maxn;j++) m[i][j]=0;
    }
    void init(){
        for(int i=0;i<maxn;i++) m[i][i]=1;
    }
    void set(int len){ //构造矩阵，根据题目变化
        for(int i=0;i<len;i++){
            for(int j=i-1;j<=i+1;j++){
                if(j<0||j>=len) continue;
                m[i][j]=1;
            }
        }
    }
    int *operator [](int x){
        return m[x];
    }
};
Matrix operator *(Matrix a,Matrix b){ //矩阵乘法,多组数据可以加个全局变量len控制矩阵大小O(len^3)
    Matrix c;
    for(int i=0;i<maxn;i++){
        for(int j=0;j<maxn;j++){
            for(int k=0;k<maxn;k++){
                c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
            }
        }
    }
    return c;
}
Matrix fpow(Matrix a,int b){ //矩阵快速幂
    Matrix c;c.init();
    while(b){
        if(b&1) c=c*a;
        a=a*a;
        b>>=1;
    }
    return c;
}
Matrix ans; //答案矩阵，仅第一列有用，ans[0][0]=f(n)
void init(int x){ //若题目类型为分段求和，则可能使用
    for(int i=x;i<maxn;i++){
        ans[i][0]=0;
    }
}