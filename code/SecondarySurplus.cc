/*
 * Author: Simon
 * 功能: 求解x^2=n(mod p),即x=sqrt(n)(mod p)
 * 复杂度: O(sqrt(p))
 */

/*类似复数 单位元为w(复数的单位元为-1)*/
struct Complex {
    int x, y, w;
    Complex() {}
    Complex(int x, int y, int w) : x(x), y(y), w(w) {}
};
/*类复数乘法 */
Complex mul(Complex a, Complex b, int p) {
    Complex ans;
    ans.x = (a.x * b.x % p + a.y * b.y % p * a.w % p) % p;
    ans.y = (a.x * b.y % p + a.y * b.x % p) % p;
    ans.w = a.w;
    return ans;
}
/*类复数快速幂 */
Complex Complexfpow(Complex a, int b, int mod) {
    Complex ans = Complex(1, 0, a.w);
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return ans;
}
int fpow(int a, int b, int mod) {
    int ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) (ans *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return ans;
}
/*求解x^2=n(mod p) */
int solve(int n, int p) {
    n %= p;
    if (n == 0) return 0;
    if (p == 2) return n;
    if (fpow(n, (p - 1) / 2, p) == p - 1) return -1; /*勒让德定理判断n不是p的二次剩余 */
    mt19937 rnd(time(0));
    int a, t, w;
    do {
        a = rnd() % p;
        t = a * a - n;
        w = (t % p + p) % p;                    /*构造w=a^2-n */
    } while (fpow(w, (p - 1) / 2, p) != p - 1); /*找到一个w不是p的二次剩余 */
    Complex ans = Complex(a, 1, w);
    ans = Complexfpow(ans, (p + 1) / 2, p); /*答案为(a+w)^{(p+1)/2} */
    return ans.x;
}
int exgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    int g=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return g;
}
/*求解x^2=n (mod p^k) */
int exsolve(int n,int p,int k,int pk){
    int r=solve(n,p);/*先求出x^2=n (mod p) */
    if(r==-1) return -1;
    Complex ans=Complex(r,1,n);
    ans=Complexfpow(ans,k,pk);/*求出(r+sqrt(n))^k=t+u·sqrt(n) */
    int a=ans.y,b=pk,c=ans.x,x,y;
    int g=exgcd(a,b,x,y);/*求解u·x=t (mod p^k) */
    if(c%g!=0) return -1;
    a/=g;b/=g;
    x*=c/g;
    return (x%b+b)%b;
}