# [I Love Palindrome String](http://acm.hdu.edu.cn/showproblem.php?pid=6599)
## 题意
给一个字符串S，对于每个$1 \leq i \leq S.size()$，输出符合下列条件的字符串个数：
1.长度为i
2.为回文串
3.s[l,(l+r)/2]也是回文串
## 题解
基本可以说是pam板子题。建立邻接表统计fail指向每个节点的节点，一遍dfs统计长度合法的串个数。
第一个是要找的是前缀不是后缀，这个把串翻转输入就能解决。
第二个是遍历的时间复杂度。可以通过建立vis数组统计出现过的长度，只有一般长度的回文串出现过当前串才是合法的。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=3e5+10;
struct PAM
{
    int next[maxn][30]; //类似sam的next指针
    int fail[maxn];       //类似sam的fail指针
    int cnt[maxn];        //类似sam的right集
    int num[maxn];        //该串包含了多少不同的回文子串
    int len[maxn];        //len[i]表示节点i表示的回文串的长的
    int chr[maxn];        //存放添加的字符
    int last;             //类似sam的last
    int n;                //字符数组指针
    int p;                //节点指针

    int ans[maxn];
    vector<int>edge[maxn];
    int vis[maxn];
    int newnode(int l) //新建节点
    {
        for (int i = 0; i < 30; i++)
            next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        edge[p].clear();
        return p++;
    }
    void init() //初始化
    {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        chr[n] = -1; //开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }

    int get_fail(int x) //失配后找一个尽量最长的
    {
        while (chr[n - len[x] - 1] != chr[n])
            x = fail[x];
        return x;
    }
    void add(int c)
    {
        c -= 'a';
        chr[++n] = c;
        int cur = get_fail(last); //通过上一个回文串照这个回文串的匹配位置
        if (!next[cur][c])
        { //如果这个回文串没有出现过，说明出现离一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);
            fail[now] = next[get_fail(fail[cur])][c]; //建立fail指针
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }
    void count()
    {
        for (int i = p - 1; i >= 1; i--)
        {
            cnt[fail[i]] += cnt[i];
            edge[fail[i]].push_back(i);
        }    
        //父亲累加儿子的cnt，以为如果fail[v]=u,则u一定是v的回文子串
    }

    void dfs(int u)
    {
        int l=len[u];
        vis[l]++;
        if(l>=1 && vis[(l+1)/2])
            ans[l]+=cnt[u];
        for(int v:edge[u])
            dfs(v);
        vis[l]--;
    }
}TT;
int main()
{
    string s;
    while(cin>>s)
    {
        TT.init();
        reverse(s.begin(),s.end());
        for(int i=0;i<s.size();i++)      
        {
            TT.add(s[i]);
        }
        TT.count();
        memset(TT.ans,0,sizeof(TT.ans));
        TT.dfs(0);
        int n=s.size();
        for(int i=1;i<n;i++)
            cout<<TT.ans[i]<<' ';
        cout<<TT.ans[n]<<endl;
    }
    return 0;
}
```