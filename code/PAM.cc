/*
 * Author: Simon
 * 复杂度: O(n·log(n))
 * 1.求串S前缀0~i内本质不同回文串的个数（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同） 
 * 2.求串S内每一个本质不同回文串出现的次数 
 * 3.求串S内回文串的个数（其实就是1和2结合起来） 
 * 4.求以下标i结尾的回文串的个数
 */
struct PAM{
/*Int */int tree[maxn][30]  /*和字典树类似，指向的串为当前串两端加上同一个字符构成 */,
        fail[maxn]      /*失配后跳转到fail指针指向的节点,其为最长回文后缀 */,
        cnt[maxn]       /*表示节点i表示的回文串的个数 (建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的) */,
        num[maxn]       /*表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数，num[idx+2]表示以str[idx]为结尾的回文串的种类数 */,
        len[maxn]       /*len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串） */,
        s[maxn]         /*存放添加的字符 */, lst/*指向新添加一个字母后所形成的最长回文串表示的节点。 */,
        n               /*表示添加的字符个数。 */,p/*表示添加的节点个数。 */;
    int newNode(int l){	/*新增一个节点，其最长回文串长度为l */
        for(int i=0;i<26;i++) tree[p][i]=0;
        cnt[p]=num[p]=0,len[p]=l;
        return p++;
    }
    void init(){
        n=p=lst=0;
        newNode(0)/*偶节点 */,newNode(-1)/*奇节点 */;
        s[0]=-1,fail[0]=1/*偶节点失配指针指向奇节点 */;
    }
    int getFail(int x){
        while(s[n-len[x]-1]!=s[n]) x=fail[x];
        return x;
    }
    void add(int c){
        c-='a'; s[++n]=c;
        int now=getFail(lst);/*找到最长的回文子串，并且前后添加c字符后还是回文子串 */
        if(!tree[now][c]){/*如果树中未存在此回文串 */
            int next=newNode(len[now]+2);/*为此串建立新节点 */
            fail[next]=tree[getFail(fail[now])][c];/*为新节点添加失配指针的指向 */
            tree[now][c]=next;/*记录新串指向的节点 */
            num[next]=num[fail[next]]+1;/*更新num数组（num数组含义在上面） */
        }
        lst=tree[now][c];/*c字母所形成的最长回文子串所在的节点为lst */
        cnt[lst]++;/*统计此回文串出现的次数 */
        //return num[lst] /*正序插入表示以str[i]为结尾的回文串的个数,倒序插入表示以str[i]为起点的回文串的个数*/
    }
    void count(){
        for(int i=p-1;i>=0;i--) cnt[fail[i]]+=cnt[i];/*节点i表示的回文串的个数要加上包含此回文串的串的个数，cnt[aa]+=cnt[baab] */
    }
}pam;