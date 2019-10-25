/* 
 * Author: Simon
 * 复杂度: O(n)
 * 功能: 求解x=ai(mod mi)同余方程组
 * 某些计数问题或数论问题出于加长代码、增加难度、或者是一些其他不可告人的原因 给出的模数：不是质数！
 * 但是对其质因数分解会发现它没有平方因子，也就是该模数是由一些不重复的质数相乘得到。
 * 那么我们可以分别对这些模数进行计算，最后用 CRT 合并答案。
 */
int crt(int ai[], int mi[], int len) {
    int ans = 0, lcm = 1;
    for (int i = 0; i < len; i++) lcm *= mi[i];
    for (int i = 0; i < len; i++) {
        int Mi = lcm / mi[i];
        int inv = fpow(Mi, mi[i] - 2, mi[i]);
        int x = fmul(fmul(inv, Mi, lcm), ai[i], lcm); //若lcm大于1e9需要用快速乘fmul
        ans = (ans + x) % lcm;
    }
    return ans;
}