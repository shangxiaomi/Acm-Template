# [Acesrc and Travel](http://acm.hdu.edu.cn/showproblem.php?pid=6662)
https://blog.csdn.net/qq_21073811/article/details/99652064
## 题意
有一棵树，每个节点有权值$a_u,b_u$,如果走到了$u$点，$zhang和liu$分别获得$a_u,b_u$的分数，现在这两个人开始旅游，他们不会走已经走过的点，并且每个人都想让自己的减去对方的分数最大，$zhang$先决定起点，然后两个人轮流选择，问最后$zhang$的分数减去$liu$的分数最大是多少。
## 题解（换根树形dp）
我们先任意选择起点，设$dp[0][u]$为$zhang$在该点能获得的最大的$\sum_{i}a_i-b_i$，$dp[1][u]$为$liu$在该点能获得的最小的$\sum_{i}(a_i-b_i)$。
父节点的值是由孩子节点转移过去的，对于$dp[0][u]$,下一步选择的是$liu$，很明显$liu$要让$dp[0][u]$尽量小,所以$dp[0][u]=a_u-b_u+min(dp[1][son])$.
对于$dp[1][u]$,也是从儿子节点向父节点转移，可以得到$dp[1][u]=a_u-b_u+max(dp[0][son])$.

这样来我们就可以获得选择的起点$dp[0][u]$，但我们还需要获得以其他节点为根节点的值，我们肯定不能再以其他每一个节点为起点都进行一次dfs,事实上我们可以选择$换根dp$

我们再进行第二次$dfs$，在每次到达新节点的时候使当前的$dp[0][u]$就为我们想要的值

假设我们第一次$dfs$后转移情况如下，箭头表示父亲是由这个儿子转移过去的
![nUz4Te.png](https://s2.ax1x.com/2019/09/10/nUz4Te.png)
对节点$1$更新完答案之后
假设我们接下来要以节点$3$为根进行答案更新，因为$1$不是由$3$转移过去的,所以我们很容易就能找到节点$3$的答案值,从$1$或者$7$转移过去。
但是假设我们要更新的不是节点3而是节点2，那么情况就有些复杂了，因为$1$的值是由$2$的值转移过去的，所以我们不能直接对$2$进行答案更新，我们需要先把$1和2$之间的转移关系消除，并且重新对$1$进行转移，重新转移的规则很简单，只要不是从节点$2$转移过去的就可以，因为第一遍$dfs$的转移关系肯定是最值，所以第二遍$dfs$中我们需要保存次值进行更新。
很明显，我们需要$dfs$一个儿子节点前，我们需要建立新的转移关系，只要转移关系不是从要$dfs$的儿子转移到父亲节点的就可以。
假设节点1重现确定转移关系后的情况图如下
![napeDf.png](https://s2.ax1x.com/2019/09/10/napeDf.png)
此时节点2需要确定从哪个儿子节点转移过来，转移关系确定后的答案即为我们要更新的答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define sc(x) scanf("%d",&x)
#define scc(x,y) scanf("%d%d",&x,&y)
#define sccc(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define mkp(a,b) make_pair(a,b)
#define F first
#define pb(a) push_back(a)
#define S second
#define pii pair<LL,LL>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
#define ll(o) (o<<1)
#define rr(o) (o<<1|1)
const LL INF = 0x3f3f3f3f3f3f3f3f ;
const int maxn = 100100;
const double pi = acos(-1.0);
int T,n,m;
int a[maxn];
int b[maxn];
vector<int>G[maxn];
LL ans;
LL dp[2][maxn];
void dfs(int u,int fa)//随机选点进行dfs
{
    dp[0][u]=INF,dp[1][u]=-INF;
    for(auto v:G[u])
    {
        if(fa==v)continue;
        dfs(v,u);
        dp[0][u]=min(dp[0][u],dp[1][v]);
        dp[1][u]=max(dp[1][u],dp[0][v]);
    }
    if(dp[0][u]==INF)dp[0][u]=dp[1][u]=0;
    dp[0][u]+=a[u]-b[u];
    dp[1][u]+=a[u]-b[u];
}
void dfs2(int u,int fa)
{
    dp[0][u]=INF;
    dp[1][u]=-INF;
    vector<pii>vec;//用于保存最值前缀
    for(auto v:G[u])
    {
        dp[0][u]=min(dp[0][u],dp[1][v]);
        dp[1][u]=max(dp[1][u],dp[0][v]);
        vec.pb(mkp(dp[0][u],dp[1][u]));//first为最小值，second为最大值
    }
    dp[0][u]+=a[u]-b[u];
    dp[1][u]+=a[u]-b[u];
    ans=max(dp[0][u],ans);//更新答案
    LL sufmin=INF;//用于保存最值后缀
    LL sufmax=-INF;
    for(int i=vec.size()-1;i>=0;i--)
    {
        int v=G[u][i];
        dp[0][u]=sufmin;
        dp[1][u]=sufmax;
        if(i)//进入儿子节点之前，需要重新确定转移关系，只更新这个最值的前缀和后缀就能满足要求
        {
            dp[0][u]=min(dp[0][u],vec[i-1].first);
            dp[1][u]=max(dp[1][u],vec[i-1].second);
        }
        if(dp[0][u]==INF)dp[0][u]=0,dp[1][u]=0;
        dp[0][u]+=a[u]-b[u];
        dp[1][u]+=a[u]-b[u];
        sufmin=min(sufmin,dp[1][v]);//跟新最值后缀
        sufmax=max(sufmax,dp[0][v]);
        if(fa!=v)dfs2(v,u);
    }
}
int main()
{
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)scanf("%d",&b[i]);
        for(int i=1;i<=n;i++)G[i].clear();
        int u,v;
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].pb(v);
            G[v].pb(u);
        }
        ans=-INF;
        dfs(1,0);
        dfs2(1,0);
        cout<<ans<<endl;
    }
    return 0;
}
```