const int maxn = "Edit";
int ans, nexr[maxn], ex[maxn];
void getnexr(char s[]) {
	int i = 0, j, po, len = strlen(s);
	nexr[0] = len;
	while (s[i] == s[i+1] && i + 1 < len) i++;
	nexr[1] = i;
	po = 1;
	for (i = 2; i < len; i++) {
		if (nexr[i-po] + i < nexr[po] + po) {
			nexr[i] = nexr[i - po];
		} else {
		 	j = nexr[po] + po - i;
		 	if (j < 0) j = 0;
		 	while (i + j < len && s[j] == s[i+j]) j++;
		 	nexr[i] = j;
		 	po = i;
		 }
	}
}

void exkmp(char s1[], char s2[]) {
	int i = 0, j, po = 0, len = strlen(s1), l2 = strlen(s2);
	while (s1[i] == s2[i] && i < l2 && i < len) i++;
	ex[0] = i;
	for (i = 1; i < len; i++) {
		if (nexr[i - po] + i < ex[po] + po) {
			ex[i] = nexr[i-po];
		} else {
		 	j = ex[po] + po - i;
		 	if (j < 0) j = 0;
		 	while (i + 1 < len && s1[j+i] == s2[j]) j++;
		 	ex[i] = j;
		 	po = i;
		 }
	}
}
