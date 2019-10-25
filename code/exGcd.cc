/*
 * Author: Simon
 * 复杂度: O(log(max(a,b)))
 * 功能: 求解a*x+b*y=c
 */

/*解a*x+b*y=gcd(a,b)*/
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
/*
 * 解a*x+b*y=c
 * 假设有一对特解x=n,y=m
 * 则其通解为：x=n-b*t or y=m+a*t
 */
void solve(int n, int A, int B, int C) {
    int x, y;
    int g = exgcd(A, B, x, y);
    if (C % g != 0) {
        cout << "-1" << endl;
        return;
    }
    A /= g, B /= g, C /= g;
    x *= C % B;
    x = (x % B + B) % B; y = (C - A * x) / B; /*求最小非负整数x，则y=(c-a*x)/b */
    // y *= C % A;
    // y = (y % A + A) % A; x = (C - B * y) / A; /*求最小非负整数y，则x=(c-b*y)/a */
    /*
        具体题目
    */
}