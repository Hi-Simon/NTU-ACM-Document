/*
 * Author: Simon
 * 功能: 求最长回文子串或回文子串的个数
 * 复杂度: O(n)
 */
string Manacher(string s) {
    /*Insert '#'*/
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) { /*预处理*/
        t += s[i]; t += "#";
    }
    /*Process t*/
    vector<int> p(t.size(), 0); /*p[i]表示以t[i]为中心的最长回文字串的半径长度*/
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
	/*其中id为能延伸到最右端的位置的那个回文子串的中心点位置，mx是回文串能延伸到的最右端的位置，最大半径，中心位置*/
	int ans=0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i]; //枚举
        if (mx < i + p[i]) { 
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
		ans+=p[i]/2;
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
	//return ans; /*返回回文子串的个数*/
}