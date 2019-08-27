#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define F first
#define ep(a) emplace_back(a)
#define S second
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MID(l, r) (l + ((r - l) >> 1))
#define ll(o) (o << 1)
#define rr(o) (o << 1 | 1)
const int INF = 0x3f3f3f3f;
const int maxn = 10000;
const double pi = acos(-1.0);
int T, n, m;
const int N_ch = 26;
struct PAM
{
    int next[maxn][N_ch]; //类似sam的next指针
    int fail[maxn];       //类似sam的fail指针
    int cnt[maxn];        //类似sam的right集
    int num[maxn];        //该串包含了多少不同的回文子串
    int len[maxn];        //len[i]表示节点i表示的回文串的长的
    int chr[maxn];        //存放添加的字符
    int last;             //类似sam的last
    int n;                //字符数组指针
    int p;                //节点指针
    int newnode(int l) //新建节点
    {
        for (int i = 0; i < N_ch; i++)
            next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
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
            cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，以为如果fail[v]=u,则u一定是v的回文子串
    }
}TT;
int main()
{
    string s;
    while(cin>>s)
    {
        TT.init();
        for(int i=0;i<s.size();i++)      
        {
            TT.add(s[i]);
        }
        TT.count();
        for(int i=0;i<=TT.p;i++)
        {
            cout<<i<<" "<<TT.num[i]<<endl;
        }
    }
    system("pause");
    return 0;
}