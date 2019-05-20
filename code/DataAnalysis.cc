struct Date_Analysis {
	int bit[6];
	inline void Clear(){memset(bit,0,sizeof(bit));}
	Date_Analysis(){Clear();}
	inline void Set(int t){Clear(); while(t)bit[++bit[0]]=t%cube, t/=cube; }
	inline int &operator [] (int x){ return bit[x];}
	inline void print() {
		printf("%d",bit[bit[0]]);
		for(int i=bit[0]-1;i>0;i--)printf("%09d",bit[i]);
		printf("\n");
	}
	inline Date_Analysis operator + (Date_Analysis b) {
		Date_Analysis c;c.Clear();
		c[0]=max(bit[0],b[0])+1;
		for(int i=1;i<=c[0];i++)
			c[i]+=b[i]+bit[i],c[i+1]+=c[i]/cube,c[i]%=cube;
		while(!c[c[0]]) c[0]--;
		return c;
	}
	inline void operator += (Date_Analysis b){*this=*this+b;}
	inline void operator = (int x){Set(x);}
};