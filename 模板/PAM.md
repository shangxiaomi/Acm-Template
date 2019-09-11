2.71 介绍
顾名思义，回文自动机嘛，就是拿来解决回文串问题的，方便起见，我们定义如下变量：
len[i]，表示节点i所代表的回文串的长度
next[i][ch]，表示在节点i所代表的回文串两边添加字符ch后形成的新回文串编号
fail[i]，保存失配边，表示节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串（熟悉AC自动机的应该很熟悉这个数组啦）
cnt[i]，表示互不相同的回文串的个数
last，表示添加一个字母后最长回文串的节点
s[i]表示新添加的字符
size表示节点个数
n表示字符个数
----------------------更新----------------------
今天又看了一下网上大神的博客，发现还有个num[i]，表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。

那么回文自动机具体可以干那些事呢？
求字符串S前缀0~i内不同回文串的个数
统计不同回文串出现的次数
统计回文串的个数
求以i结尾的回文串的个数

一开始的时候，回文自动机里有两个节点：0表示长度为偶数的回文串，1代表长度为奇数的回文串（貌似也有说一个是空串，一个是root的呢）。回文自动机也同时拥有两种边：字母边和后缀边（失配边）。如果节点i和节点j之间有一条字母边x相连，则表示在i的两边加上x可以变成j。如果变成后缀边，那么就表示j是i的最大后缀回文串，大概像下面这样。请注意，回文树的节点中并不存储回文串。
![](https://pic4.zhimg.com/80/v2-9fc6d3fb065500c07c4bec01c4505a93_hd.png)
2.718 构造
好了，下面我们来构造回文自动机吧！上文说了：

一开始的时候，回文自动机里有两个节点：0表示长度为偶数的回文串，1代表长度为奇数的回文串
因此，一开始的时候，len[0] = 0, len[1] = -1, last = 0, s[0] = -1, n = 0, p = 2

接下来我们从第一个字母开始构造，假设我们已经有了一个字符串S0的回文自动机，ch是待插入字符，last此时正指向上一个构造好的回文串节点。现在我们在串的最后加上x，如果串首也是x那么我们可以继续了——这是一个新的回文串。如果不是，就沿着后缀边走，直到形成一个回文串为止。

如果我们找到的回文串的中间（去掉开头和结尾的x）已经有字母边x了，那就说明这个串已经出现过了，不用再处理了。如果没有，那么意味着这是一个新的回文串，我们为它加一条字母边x。加一条字母边的方法还是容易想到的，而后缀边的话重复上个步骤，设置一下然后更新last就行了。注意到在上一个步骤中我们找到的这个回文串如果是已经出现过的，就不用进行这一步了，可以往下递归。

比如说我们添加字符ch，s[++n] = ch，然后判断s[n-len[last]-1]是否等于是s[n]，如果等于，那么这是一个新的回文串，否则last = fail[last]。如果next[last][ch]没有后继，我们就新建一个节点（++p），让now = 新节点编号，len[now] = len[last] + 2，fail[now] = next[get_fail(fail[last])][ch]，其中get_fail是失配函数（相信熟悉匹配算法的对这个函数也不陌生），next[last][ch] = now。最后我们令last = next[last][ch]，cnt[last]++。

于是通过这种递归，我们就可以构造出一个回文自动机了。回文自动机的时间复杂度是O(n*|Alphabet|)，空间复杂度是O(n*log(|Alphabet|))，效率很不错，很妙妙啊！作者的论文链接：Palindromic tree: behind the scenes - Codeforces

2.7182 代码
下面是我的引入中例题的AC代码，只有60行不到，很便捷。其中回文自动机我并没有模板化。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ri register int
using namespace std;

const int maxn = 300010;
int n, m, tot, cnt[maxn], len[maxn], fail[maxn], last, son[maxn][27], cur;
char s[maxn];
long long ans;

inline int new_node(ri x)
{
	len[tot] = x; cnt[tot] = 0;
	return tot++;
}

inline int get_fail(ri x, ri n)
{
	while(s[n-len[x]-1] != s[n]) x = fail[x];
	return x;
}

inline void init()
{
	scanf("%s", s+1);
	n = strlen(s+1);
	new_node(0); new_node(-1);
	fail[0] = 1; last = 0;
}

inline void write(long long x)
{
	if(x > 9) write(x/10);
	putchar(x%10+'0');
}

int main()
{
	init();
	for(ri i=1;i<=n;i++){
		ri x = s[i] - 'a';
		cur = get_fail(last, i);
		if(!son[cur][x]){
			ri nw = new_node(len[cur]+2);
			fail[nw] = son[get_fail(fail[cur],i)][x];
			son[cur][x] = nw;
		}
		last = son[cur][x];
		cnt[last]++;
	}
	for(int i=tot-1;i>=0;i--) cnt[fail[i]] += cnt[i];
	for(int i=2;i<tot;i++) ans = max(ans, (long long)len[i]*cnt[i]);
	write(ans);
	return 0;
}
```