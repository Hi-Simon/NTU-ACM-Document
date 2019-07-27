// ---
// 模数p为费马素数，g为p的原根。
// $g^{\frac{p-1}{n}}$具有和$w_n=e^{\frac{2i\pi}{n}}$相似的性质。
// 具体的p和g可参考1.11
// ---
const int mod = 119 << 23 | 1;
const int g = 3;
int wn[23];
void getwn() { 
	for (int i = 0; i < 20; i++) wn[i] = fpow(g, (mod - 1) / (1 << i), mod);
}
void change(int y[],int len){
    for(int i=1,j=len>>1;i<len-1;i++){
        if(i<j) swap(y[i],y[j]);
        int k=len>>1;
        while(j>=k) j-=k,k>>=1;
        if(j<k) j+=k;
    }
}
void ntt(int y[],int len,int on,int p){
    change(y,len);
    for(int mid=1;mid<len;mid<<=1){
        int wn=fpow(g,(p-1)/(mid<<1),p);
        for(int R=mid<<1,j=0;j<len;j+=R){
            int w=1;
            for(int k=0;k<mid;k++,w=w*wn%p){
                int u=y[j+k],v=w*y[j+mid+k]%p;
                y[j+k]=(u+v)%p;
                y[j+mid+k]=(u-v+p)%p;
            }
        }
    }
    if(on==-1) {
        int inv = fpow(len, p - 2, p);
        for(int i=1;i<len/2;i++) swap(y[i],y[len-i]);
        for(int i=0;i<len;i++) (y[i]*=inv)%=mod;
    }
}