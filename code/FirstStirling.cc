int seq[60][maxn << 1] , ptr = 0;
long long B[maxn << 1] , C[maxn << 1];

int DFS( int l , int r ){
	if( l == r ){
		int id = ptr ++ ;
		seq[id][1] = l ;
		seq[id][0] = 1 ;
		return id;
	} else {
		int mid = l + r >> 1;
		int lid = DFS( l , mid );
		int rid = DFS( mid + 1 , r );
		ptr -= 2;
		int newid = ptr ++ ;
		int len = 1;
		while( len <= r - l + 1 ) len <<= 1;
		for(int i = 0 ; i < len ; ++ i) B[i] = seq[lid][i] , C[i] = seq[rid][i] , seq[lid][i] = seq[rid][i] = 0;
		ntt( B , len , 1 );
		ntt( C , len , 1 );
		for(int i = 0 ; i < len ; ++ i) B[i] = B[i] * C[i] % Mod;
		ntt( B , len , -1 );
		for(int i = 0 ; i < len ; ++ i) seq[newid][i] = B[i];
		return newid;
	}
}

//int id = DFS( 0 , N - 1 );
//for(int i = N ; i >= 0 ; -- i) {
//	printf( "f[%d] is %d \n" , N - i , seq[id][i] );
//}
