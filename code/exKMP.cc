/*
 * Author: nuchenghao
 * 复杂度: O(n+m)
 * 功能: 解决如下问题：定义母串s和子串p，设s的长度为n,p的长度为m,求p与s的每一个后缀的最长公共前缀
 *      extend[i]表示p与s[i,n-1]的最长公共前缀。（0<=i<n）
 *      一个辅助工具为nxt[i]表示p[i,m-1]和p本身的最长公共前缀长度
 *      下标都从0开始
 */

int nxt[maxn], ex[maxn]; /*ex数组即为extend数组 */
/*预处理计算next数组 */
void getnxt(char *s) {
    memset(nxt,0,sizeof(nxt));
    int i = 0, j, po, len = strlen(s);
    nxt[0] = len;   /*初始化next[0] */
    while (s[i] == s[i + 1] && i + 1 < len) i++; /*计算next[1] */
    nxt[1] = i; po = 1; /*初始化po的位置 */
    for (i = 2; i < len; i++) {
        if (nxt[i - po] + i < nxt[po] + po) nxt[i] = nxt[i - po];/*第一种情况，可以直接得到next[i]的值 */
        else { /*第二种情况，要继续匹配才能得到next[i]的值 */
            j = nxt[po] + po - i;
            if (j < 0) j = 0; /*如果i>po+nxt[po],则要从头开始匹配 */
            while (i + j < len && s[j] == s[j + i]) j++; /*计算next[i] */
            nxt[i] = j;
            po = i; /*更新po的位置 */
        }
    }
}
/*计算extend数组 */
void exkmp(char *s, char *p) {
    memset(ex,0,sizeof(ex));
    int i = 0, j, po, len = strlen(s), l2 = strlen(p);
    getnxt(p); /*计算子串的next数组 */
    while (s[i] == p[i] && i < l2 && i < len) i++;/*计算ex[0] */
    ex[0] = i; po = 0; //初始化po的位置
    for (i = 1; i < len; i++) {
        if (nxt[i - po] + i < ex[po] + po) ex[i] = nxt[i - po]; /*第一种情况，直接可以得到ex[i]的值 */
        else {  /*第二种情况，要继续匹配才能得到ex[i]的值 */
            j = ex[po] + po - i;
            if (j < 0) j = 0; /*如果i>ex[po]+po则要从头开始匹配 */
            while (i + j < len && j < l2 && s[j + i] == p[j]) j++;  /*计算ex[i] */
            ex[i] = j; po = i; //更新po的位置
        }
    }
}