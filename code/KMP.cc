/*
 * Author: Simon
 * 复杂度: O(n)
 */
int Next[maxn]; /*i之前相同前缀后缀的长度，例ababc,Next[5]=2; */
void getNext(int m,char p[]){
    memset(Next,0,sizeof(int)*(m+5));
    int k=-1,j=0;
    Next[0]=-1;
    while(j<m){
        if(k==-1||p[k]==p[j]){
            k++,j++;
            if(p[k]!=p[j]) Next[j]=k;
            else Next[j]=Next[k];
        }
        else k=Next[k];
    }
}
int KMP(int n,int m,char s[],char p[]){
    int i=0,j=0,ans=0;
    while(i<n){
        if(j==-1||s[i]==p[j]) i++,j++;
        else j=Next[j];
        if(j==m) ans++; /*计数（可重叠）*/
        //if(j==m) ans++,j=0;/*计数（不可重叠）*/
        //if(j==m) return i-m+1; /*返回第一个匹配的位置 */
    }
    //return j;/*返回s后缀与p前缀匹配的最长长度 */
    return ans;
}