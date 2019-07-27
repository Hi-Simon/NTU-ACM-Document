/*
Author: Simon
平均复杂度O(loglog(p))
若不存在原根则返回-1
对于所有素数p>2,正整数e，当前仅当n=1，2，4，p^e,2p^e有原根
若g是p的原根，对于1<=i<p, g^i mod p，互不相同，即唯一。
*/
int proot(int p){ //fac为（p-1）的所有质因子。
    for(int a=2;a<p;a++){
        bool flag=0;
        for(int i=0;i<fac.size();i++){
            int v=fac[i];
            if(fpow(a,(p-1)/v,p)==1){ //如果存在d，a^{p-1/d} %p=1则a不是p的原根。
                flag=1;break;
            }
        }
        if(!flag) return a;
    }
    return -1;
}