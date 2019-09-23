/*
 * Author: Simon 
 * 功能: 求解a^x=b(mod p),其中p可达1e18,但p的质因数个数很少。
 * 复杂度: 复杂度O(k·e_i·log(p_i^{e_i})+k·log(p_i^{e_i}))
 * 其中k为p-1的质因子的个数，e_i为p-1的质因子的最高幂次。p_i最高幂次对应的质因子。
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int __int128_t  
#define INF 0x3f3f3f3f
#define maxn 200005
struct Istream {
    template <class T>
    Istream &operator >>(T &x) {
        static char ch;static bool neg;
        for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
        for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
        x=neg?-x:x;
        return *this;
    }
}fin;
struct Ostream {
    template <class T>
    Ostream &operator <<(T x) {
        x<0 && (putchar('-'),x=-x);
        static char stack[233];static int top;
        for(top=0;x;stack[++top]=x%10+'0',x/=10);
        for(top==0 && (stack[top=1]='0');top;putchar(stack[top--]));
        return *this;
    }

    Ostream &operator <<(char ch) {
        putchar(ch);
        return *this;
    }
}fout;
vector<pair<int,int> >fac;
void solve(int n){ /*求解质因数 */
    fac.clear();
    for(int i=2;i*i<=n;i++){
        int tmp=0;
        if(n%i==0){
            while(n%i==0) n/=i,tmp++;
            fac.push_back({i,tmp});
        }
    }
    if(n>1) fac.push_back({n,1});
}
int fpow(int a,int b,int mod){
    int ans=1;a%=mod;
    while(b){
        if(b&1) (ans*=a)%=mod;
        (a*=a)%=mod;
        b>>=1;
    }
    return ans;
}
int proot(int p){ //求原根
    for(int a=2;a<p;a++){
        bool flag=0;
        for(int i=0;i<fac.size();i++){
            int v=fac[i].first;
            if(fpow(a,(p-1)/v,p)==1){
                flag=1;break;
            }
        }
        if(!flag) return a;
    }
    return -1;
}
int cal(int a,int b,int p,pair<int,int>fac){
    int ans=0,t=fac.first;
    map<int,int>mp;
    for(int i=0;i<fac.first;i++) mp[fpow(a,i*(p-1)/t,p)]=i;
    for(int i=1;i<=fac.second;i++){
        int c=mp[fpow(b,(p-1)/t,p)];
        (ans+=c*t/fac.first)%=p;
        (b*=fpow(fpow(a,c*t/fac.first,p),p-2,p))%=p;
        (t*=fac.first)%=p;
    }
    return ans;
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
int excrt(int mi[],int ai[],int n){ //扩展中国剩余定理
    int M=mi[1],ans=ai[1];
    for(int i=2;i<=n;i++){
        int a=M,b=mi[i],c=((ai[i]-ans)%b+b)%b;
        int x,y;
        int gcd=exgcd(a,b,x,y);
        if(c%gcd!=0) return -1;
        a/=gcd,b/gcd;
        (x*=(c/gcd)%b)%=b; x=(x+b)%b;
        ans+=x*M;
        M*=b;
        ans%=M;
    }
    return (ans+M)%M;
}
int pohlig_hellman(int a,int b,int p,vector<pair<int,int> >fac){ /*求解a^x=b(mod p),a为p的原根 */
    int mi[fac.size()+5]={0},ai[fac.size()+5]={0};
    for(int i=0;i<fac.size();i++){
        mi[i+1]=fpow(fac[i].first,fac[i].second,p); /*pi^{ei} */
        ai[i+1]=cal(a,b,p,fac[i]); /*求解xi=x (mod pi^{ei}) */
    }
    return excrt(mi,ai,fac.size()); /*扩展中国剩余定理合并同余方程 */
}
Int main(){
    Int T;cin>>T;
    while(T--){
        int p,a,b;fin>>p>>a>>b; /*求a^x=b(mod p) */
        solve(p-1); /*求得p-1的质因数，及其幂次 */
        int root=proot(p); /*求得p的原根 */
        int pa=pohlig_hellman(root,a,p,fac)/*g^{pa}=a(mod p) */,pb=pohlig_hellman(root,b,p,fac);/*g^{pb}=b(mod p) */
        if(pa==0){ /*转换为求g^{pa·x}=g^{pb}(mod p),由欧拉定理得pa·x=pb(mod (p-1))*/
            if(pb==0) fout<<1;
            else fout<<-1;
        }
        else{ /*求解 pa·x=pb(mod (p-1)) */
            int x,y;
            int gcd=exgcd(pa,p-1,x,y);
            if(pb%gcd!=0){
                fout<<-1;
                cout<<endl;
                continue;
            }
            int B=(p-1)/gcd;pa/=gcd;
            x*=pb/gcd;
            fout<<((x%B+B)%B);
        }
        cout<<endl;
    }
    cin.get(),cin.get();
    return 0;
}