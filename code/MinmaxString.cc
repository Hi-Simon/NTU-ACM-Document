/*
 * Author: Simon
 * 复杂度: O(n)
 * 功能: 求字符串最小，最大表示法的起始下标
 *      最小表示法指一个循环串以某一位开始时对应的串的字典序最小  这个串就是该循环串的最小表示法 
 */

/*最小表示法 */
int get_minstring(char *s)
{
    int len = strlen(s);
    int i = 0, j = 1, k = 0;
    while(i<len && j<len && k<len) {
        int t=s[(i+k)%len]-s[(j+k)%len];
        if(t==0) k++;
        else {
            if(t > 0) i+=k+1;
            else j+=k+1;
            if(i==j) j++;
            k=0;
        }
    }
    return min(i,j);
}
 
/*最大表示法 */
int get_maxstring(char *s)
{
    int len = strlen(s);
    int i = 0, j = 1, k = 0;
    while(i<len && j<len && k<len) {
        int t=s[(i+k)%len]-s[(j+k)%len];
        if(t==0) k++;
        else {
            if(t > 0) j+=k+1;
            else i+=k+1;
            if(i==j) j++;
            k=0;
        }
    }
    return min(i,j);
}