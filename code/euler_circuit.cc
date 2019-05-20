const int maxn = 100;

int n;
int step;
int path[maxn];

void find_path_u(int now, int mat[][maxn]) {
	for (int i=n-1; i>=0; i--) {
		while (mat[now][i]) {
			mat[now][i]--, mat[i][now]--; 
			find_path_u(i, mat); 
		}
	}
	path[step++] = now; 
}

void find_path_d(int now, int mat[][maxn]) {  
	for (int i=n-1; i>=0; i--) {
		while (mat[now][i]) { 
			mat[now][i]--; 
			find_path_d(i, mat); 
		} 
	}
	path[step++] = now; 
}


int euler_circuit(int start, int mat[][maxn]) { 
	step = 0;
	find_path_u(start, mat); 
	// find_path_d(start, mat); 
	return step; 
}

int main() {
	
}