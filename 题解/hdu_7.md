# [Kejin Player](http://acm.hdu.edu.cn/showproblem.php?pid=6656)
## 题意
有$n+1$个等级，在$i$级时升级需要花费$a[i]$,有$p[i]$的几率升到$i+1$级，否则就退回$x[i]$级,给出$1~n$级的$a[i],p[i],x[i]$，给出$m$次查询，每次查询需要输出从$l$升到$r$级的花费期望是多少。


## 题解
用一个dp数组表示前缀和
从设$i$级升到$i+1$级的期望为$E$

$E=p[i]*a[i]+(1-p[i])*(a[i]+E+dp[i]-dp[x[i])$  

$dp[i+1]=dp[i]+E$

因为每一次如果升级成功，花费的期望为$p[i]*a[i]$。  
如果不成功则从$x[i]$升级到$i$级中间花的代价就白费了，所以用前缀和相减就能得到这部分的数值，再加上这次升级所需的费用$a[i]$，最后就是再加上这次升级的总体期望E。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef long long int ll;
#define sc(x) scanf("%d",&x)
#define scc(x,y) scanf("%d%d",&x,&y)
#define sccc(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define mkp(a,b) make_pair(a,b)
#define F first
#define ep(a) emplace_back(a)
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))

#define rr(o) (o<<1|1)
const LL INF = 0x3f3f3f3f ;
const int maxn = 510000;
const double pi = acos(-1.0);
const LL mod=1e9+7;
int T,n,m;
LL r[maxn],s[maxn],x[maxn],a[maxn];
LL dp[maxn];
LL pow(LL a,LL b)
{
    LL aa=1ll*a;
    LL res=1;
    while(b)
    {
        if(b&1)res=(res*aa)%mod;
        aa=(aa*aa)%mod;
        b=(b>>1);
    }
    return res;
}
LL inv(LL a)
{
    return pow(a,mod-2);
}
int main()
{
    cin>>T;
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%lld%lld%lld%lld",&r[i],&s[i],&x[i],&a[i]);
        }
        for(int i=2;i<=n+1;i++)
        {
            LL tmp=(((dp[i-1]-dp[x[i-1]]+a[i-1]+mod)%mod)*(s[i-1]))%mod;
            tmp=(tmp*(inv(r[i-1])))%mod;
            dp[i]=(dp[x[i-1]]+tmp)%mod;
        }
        int l,r;
        while(m--)
        {
            scanf("%d%d",&l,&r);
            printf("%lld\n",(mod+dp[r]-dp[l])%mod);
        }
    }
    return 0;
}
```