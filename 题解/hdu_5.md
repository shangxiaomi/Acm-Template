[TOC]
# [permutation 1(DFS)](http://acm.hdu.edu.cn/showproblem.php?pid=6628)
## 题意
给定一个数$n$,求出$p_2-p_1,p_3-p_2,...,p_n-p_{n-1}$中字典序第$k$小的排列，$1\leq p_i\leq n$
## 题解
第一位定为一个较大的值，枚举[high-n+1,low+n-1]，然后控制数列最大值-最小值<=n-1,这样就能保证按顺序dfs,最后输出的时候所有值减去最小值。

```c
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
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
#define ll(o) (o<<1)
#define rr(o) (o<<1|1)
const LL INF = 0x3f3f3f3f ;
const int maxn = 10000;
const double pi = acos(-1.0);
int T,n,m;
int d[100];
int k;
bool vis[100];
bool dfs(int pos,int low,int high)
{
    if(pos==n+1)
    {
        k--;
        if(k==0)
        {
            for(int i=1;i<=n;i++)
            {
                printf("%d%c",d[i]-low+1,i==n?'\n':' ');
            }
            return 1;
        }
        return 0;
    }
    for(int i=high-n+1;i<=low+n-1;i++)
    {
        if(vis[i])continue;
        vis[i]=1;
        d[pos]=i;
        if(dfs(pos+1,min(i,low),max(i,high)))return 1;
        vis[i]=0;
    }
    return 0;
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        mem0(vis);
        d[1]=n;
        vis[n]=1;
        dfs(2,n,n);
    }
    system("pause");
    return 0;
}
```