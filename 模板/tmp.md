[TOC]
# 字符串相关
### 序列自动机
[序列自动机](https://nanti.jisuanke.com/t/38232)
```c
#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
const int INF = 0x3f3f3f3f;
const int maxn = 101100;
const double pi = acos(-1.0);
int T, n, m;
char s[100500];
char a[1010];
int Next[100500][30];
int main()
{
    for (int i = 0; i <= 100000; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            Next[i][j] = -1;
        }
    }
    cin >> s;
    int len = strlen(s);
    for(int i=len-1;i>=0;i--){
        for(int j=0;j<26;j++){
            Next[i][j]=Next[i+1][j];
        }
        Next[i][s[i]-'a']=i+1;
    }
    cin >> n;
    while (n--)
    {
        scanf("%s", a);
        int l = strlen(a);
        int f = 1;
        int now=0;
        for (int i = 0; f && i < l; i++)
        {
            now = Next[now][a[i] - 'a'];
            if (now == -1)
            {
                f = 0;
                break;
            }
            
        }
        if(f)cout<<"YES\n";
        else cout<<"NO\n";
    }
    system("pause");
    return 0;
}
```
# 三分查找算法
```c
double solve(double parameter)
{
    // 计算函数值，即f(x)
}
 
double trisection_search(double left, double right)
{
    // 三分搜索，找到最优解（求函数最大值下的自变量值）
    double midl, midr;
    while (right-left > 1e-7)
    {
        midl = (left + right) / 3;
        midr = (midl + right) / 2;
        // 如果是求最小值的话这里判<=即可
        if(solve(midl) >= solve(midr)) right = midr;
        else left = midl;
    }
    return left;
}
```

# 数学相关模板
### 卢卡斯定理模板
```c
#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define mkp(a,b) make_pair(a,b)
#define pii pair<int ,int>
typedef long long LL;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 0x3f3f3f3f;
const int maxn = 100100;
int T,n,m;
int fact[maxn];//需要预处理出n!%mod
const int mod=1e5+3;
void init()//预处理出n!%mod
{
    fact[0]=1;
    for(int i=1;i<maxn;i++)
    {
        fact[i]=(fact[i-1]*i)%mod;
    }
}
int extgcd(int a,int b,int&x,int&y)
{
    int d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else {
        x=1;
        y=0;
    }
    return d;
}
int mod_inverse(int a,int m)
{
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
int mod_fact(int n,int p,int&e)
{
    e=0;
    if(n==0)return 1;
    int res=mod_fact(n/p,p,e);
    e+=n/p;
    if(n/p%2!=0)return res*(p-fact[n%p])%p;
    return res*fact[n%p]%p;
}
int mod_comb(int n,int k,int p)
{
    if(n<0||k<0||n<k)return 0;
    int e1,e2,e3;
    int a1=mod_fact(n,p,e1);
    int a2=mod_fact(k,p,e2);
    int a3=mod_fact(n-k,p,e3);
    if(e1>e2+e3)return 0;
    return a1*mod_inverse(a2*a3%p,p)%p;
}
int main()
{
    init();
    cout<<mod_comb(6,2,mod);
    system("pause");//提交题目之前注释掉这句话！！！
    return 0;
}
```
### 二分乘法
```c
LL multi(LL a,LL b,LL m)
{
    LL ans = 0;
    a %= m;
    while(b)
    {
        if(b & 1)
        {
            ans = (ans + a) % m;
            b--;
        }
        b >>= 1;
        a = (a + a) % m;
    }
    return ans;
}
```
### 快速幂
```c
long long modexp(long long  a, long long b, int mod)
{
    long long res=1;
    while(b>0)
    {

        if(b&1)
            res=res*a%mod;
        b=b>>1;
        a=a*a%mod;
    }
    return res;
}
```
### 矩阵快速幂
```c
/*
矩阵快速幂模板 
by chsobin
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 2;
const int mod = 10000;

//矩阵结构体 
struct Matrix{
    int a[maxn][maxn];
    void init(){    //初始化为单位矩阵 
        memset(a, 0, sizeof(a));
        for(int i=0;i<maxn;++i){
            a[i][i] = 1;
        }
    }
};

//矩阵乘法 
Matrix mul(Matrix a, Matrix b){
    Matrix ans;
    for(int i=0;i<maxn;++i){
        for(int j=0;j<maxn;++j){
            ans.a[i][j] = 0;
            for(int k=0;k<maxn;++k){
                ans.a[i][j] += a.a[i][k] * b.a[k][j];
                ans.a[i][j] %= mod; 
            }
        }
    } 
    return ans;
}

//矩阵快速幂 
Matrix qpow(Matrix a, int n){
    Matrix ans;
    ans.init();
    while(n){
        if(n&1) ans = mul(ans, a);
        a = mul(a, a);
        n /= 2;
    } 
    return ans;
}

void output(Matrix a){
    for(int i=0;i<maxn;++i){
        for(int j=0;j<maxn;++j){
            cout << a.a[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    Matrix a;
    a.a[0][0] = 1;
    a.a[0][1] = 0;
    a.a[1][0] = 0;
    a.a[1][1] = 1;
    
    Matrix ans = qpow(a, 10);
    cout << "a = ";
    output(ans);
    cout << "f(12) = [f(2), f(1)] = [1, 1] * a^10 = " << ans.a[0][0] + ans.a[1][0]; 
    
    cout << endl;
    system("pause");
    return 0;
}
```
---
# RMQ
```c
//也可以是区间最大值，倍增思想
void rmq_init()//RMQ初始化，数组下标从1开始
{
    for(int i=1;i<=N;i++)
        dp[i][0]=arr[i];//初始化
    for(int j=1;(1<<j)<=N;j++)
        for(int i=1;i+(1<<j)-1<=N;i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<j-1)][j-1]);
}

int rmq(int l,int r)//O(1)查询
{
    int k=log2(r-l+1);
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}

```
---
# 树状数组
### 一维
```c
int bit[maxn];//记录的节点从下标1开始
void add(int i,LL x)
{
    while(i<=n){
        shu[i]+=x;
        i+=i&-i;
    }
}
LL sum(int i)
{
    int s=0;
    while(i>0){
        s+=shu[i];
        i-=i&-i;
    }
    return s;
}
```
### 二维
```c
ll a[maxn][maxn];
ll c[maxn][maxn];
int lowbit(int x){
    return x&(-x);
}
void modify(int x, int y, int val){
    a[x][y] += val;
    for(int i=x;i<=row;i+=lowbit(i))
        for(int j=y;j<=col;j+=lowbit(j))
            c[i][j] += val;
}
ll sum(int x,int y){
   ll ans=0;
   for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            ans += c[i][j];
   return ans;
}
int main(){
    int i,j;
    int op;
    //freopen("F://2.txt","r",stdin);
    while(~scanf("%d",&op)){
        if(op==0){
            scanf("%d",&n);
            row=col=n;
            CL(c,0);
        }
        if(op==3)
            break;
        if(op==1){
            int x,y,t;
            scanf("%d %d %d",&x,&y,&t);
            modify(x+1,y+1,t);///BIT从1开始
        }
        if(op==2){
            int l,b,r,t;
            scanf("%d%d%d%d",&l,&b,&r,&t);
            printf("%lld\n",sum(r+1,t+1)+sum(l,b)-sum(l,t+1)-sum(r+1,b));///类似容斥
        }
    }
    return 0;
}
```
---
# 线段树

### 区间修改（加减）,区间求和
```c
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
const int INF = 0x3f3f3f3f ;
const int maxn = 200000+100;
const double pi = acos(-1.0);
int T,n,m;
LL a[maxn];
LL sum[maxn*3]={0};//线段树的区间和
LL add[maxn*3]={0};//懒惰标记，标记这个区间变化了多少
void pushup(int o)////pushup函数，该函数本身是将当前结点用左右子节点的信息更新，此处求区间和，用于update中将结点信息传递完返回后更新父节点
{
    sum[o]=sum[o<<1]+sum[o<<1|1];
}
void pushdown(int o,int l,int r)////pushdown函数，将o结点的信息传递到左右子节点上
{
    if(add[o])////当父节点有更新信息时才向下传递信息
    {
        LL c=add[o];
        add[o<<1]+=c;////左右儿子结点均加上父节点的更新值
        add[o<<1|1]+=c;
        int m=l+((r-l)>>1);
        sum[o<<1]+=1ll*(m-l+1)*c;////左右儿子结点均按照需要加的值总和更新结点信息
        sum[o<<1|1]+=1ll*(r-m)*c;
        add[o]=0;//信息传递完之后就可以将父节点的更新信息删除
    }
}
void build(int o,int l,int r)
{
    add[o]=0;
    sum[o]=a[l];
    if(l==r) return ;
    int m=(l+r)/2;
    build(o<<1,l,m);
    build((o<<1)|1,m+1,r);
    sum[o]=sum[o<<1]+sum[(o<<1)|1];
}
void Update(int o,int l,int r,int ql,int qr,LL c)//ql、qr为需要更新的区间左右端点，c为需要增加的值
{
    if(ql<=l&&qr>=r)//当前区间处于要修改的区间中
    {
        add[o]+=c;//修改懒惰标记
        sum[o]+=1ll*(r-l+1)*c;//修改区间和
        return ;
    }
    pushdown(o,l,r);//向下更新信息
    int m=l+((r-l)>>1);
    if(ql<=m)Update(o<<1,l,m,ql,qr,c);//更新区间与左半区间有重合部分
    if(qr>=m+1)Update((o<<1)|1,m+1,r,ql,qr,c);//更新区间与右半区间有重合部分
    pushup(o);//向上更新信息
    //cout<<o<<"!!"<<sum[o]<<"\n";
}
LL Query(int o,int l,int r,int ql,int qr)
{
    if(ql<=l&&qr>=r)return sum[o];//当前区间处于查询区间中，直接返回区间值
    pushdown(o,l,r);
    int m=l+((r-l)>>1);
    LL ans=0;
    if(ql<=m)ans+=Query(o<<1,l,m,ql,qr);
    if(qr>=m+1)ans+=Query(o<<1|1,m+1,r,ql,qr);//若所需查询的区间与当前结点的右子节点有交集，则结果加上查询其右子节点的结果
    return ans;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    build(1,1,n);
    string s;
    int a,b;
    while(m--)
    {
        cin>>s>>a>>b;
        if(s[0]=='Q')cout<<Query(1,1,n,a,b)<<endl;
        else 
        {
            int c;
            cin>>c;
            Update(1,1,n,a,b,c);
        }
    }
    return 0;
}
```
### 无区间修改，查询区间内最小值和最大值
```c
using namespace std;
#define LL int
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
const int INF = 0x3f3f3f3f ;
const int maxn = 100000+100;
const double pi = acos(-1.0);
int T,n;
int h[maxn];
int maxh[maxn*4];
int minh[maxn*4];
void build(int o,int l,int r)
{
    if(l==r)
    {
        maxh[o]=minh[o]=h[l];//建树时读入
        return ;
    }
    int m=l+((r-l)>>1);
    build(o<<1,l,m);
    build(o<<1|1,m+1,r);
    maxh[o]=max(maxh[o<<1],maxh[o<<1|1]);
    minh[o]=min(minh[o<<1],minh[o<<1|1]);
}
void Query(int o,int l,int r,int ql,int qr,int&minans,int&maxans)
{
    if(ql<=l&&qr>=r)
    {
        maxans=max(maxans,maxh[o]);
        minans=min(minans,minh[o]);
        return ;
    }
    int m=l+((r-l)>>1);
    if(ql<=m)Query(o<<1,l,m,ql,qr,minans,maxans);
    if(qr>m)Query(o<<1|1,m+1,r,ql,qr,minans,maxans);
}
int main()
{
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&h[i]);
    }
    build(1,1,n);
    int a,b;
    while(m--)
    {
        int c=INF;
        int d=0;
        scanf("%d%d",&a,&b);
        Query(1,1,n,a,b,c,d);
        cout<<d-c<<endl;
    }
    return 0;
}
```
### 区间覆盖，查询有多少不同颜色（贴海报问题）
```c
using namespace std;
#define LL int
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
const int INF = 0x3f3f3f3f ;
const int maxn = 2*10000+100;
const double pi = acos(-1.0);
int T,n,m;
int mp[10000000+10];//离散化端点坐标
bool book[maxn];//标记答案颜色是否出现
int f[maxn*4];//标记整个区间是什么颜色//0代表没有颜色或者区间颜色不相同
int l[maxn];//记录数据的左端点
int r[maxn];//记录数据的右端点
void build(int o,int l,int r)//建树
{
    if(l==r)
    {
        f[o]=0;//初始化标记
        return ;
    }
    int m=l+((r-l)>>1);
    build(o<<1,l,m);
    build(o<<1|1,m+1,r);
}
void pushdown(int o,int l,int r)//向下更新
{
    if(f[o]==0)return;//如果区间颜色相同，则向下更新，同时此区间的颜色置0，相当于把海报从中切开，完整的海报不存在了
    f[o<<1]=f[o<<1|1]=f[o];
    f[o]=0;
}
void Update(int o,int l,int r,int ql,int qr,int c)//区间更新颜色
{
    if(ql<=l&&qr>=r)
    {
        f[o]=c;
        return ;
    }
    pushdown(o,l,r);//向下更新
    int mid=(l+r)/2;
    if(ql<=mid)Update(o<<1,l,mid,ql,qr,c);
    if(qr>mid)Update(o<<1|1,mid+1,r,ql,qr,c);
}
void Query(int o,int l,int r)
{
    if(l==r)
    {
        book[f[o]]=1;
        return;
    }
    pushdown(o,l,r);
    int m=l+((r-l)>>1);
    Query(o<<1,l,m);
    Query(o<<1|1,m+1,r);
}
int main()
{
    cin>>T;
    while(T--)
    {
        qu.clear();
        mem0(f);
        mem0(book);
        cin>>n;
        m=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&l[i],&r[i]);
            a[m++]=l[i];
            a[m++]=r[i];
        }
        sort(a,a+m);
        m=unique(a,a+m)-a;
        int t=0;
        for(int i=0;i<m;i++)
        {
            mp[a[i]]=++t;
        }
        for(int i=1;i<=n;i++)
        {
            Update(1,1,t,mp[l[i]],mp[r[i]],i);
        }
        Query(1,1,t);
        int ans=0;
        for(int i=1;i<=t;i++)
        {
            if(book[i])ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}

```
### 区间每个数开根号（单点更新+剪枝），区间查询求和
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
const int INF = 0x3f3f3f3f ;
const int maxn = 100000+100;
const double pi = acos(-1.0);
int T,n,m;
LL sum[maxn*4];//线段树区间和，无懒惰标记
void pushup(int o)//向上更新函数
{
    sum[o]=sum[o<<1]+sum[o<<1|1];
}
void build(int o,int l,int r)//建树
{
    if(l==r)
    {
        scanf("%lld",&sum[o]);//建树时读入每个数据
        return;
    }
    int m=MID(l,r);
    build(o<<1,l,m);
    build(o<<1|1,m+1,r);
    pushup(o);//向上更新区间和（因为有非0的初始数据）
}
void update(int o,int l,int r,int ql,int qr)//更新函数，对区间内的每个数进行开根号
{
    if(ql<=l&&qr>=r&&sum[o]==r-l+1)return;//此区间处于查询区间中，且此区间的已经等于区间长度，就算再进行开根运算，也不会改变区间和，函数终止
    if(ql<=l&&qr>=r&&l==r)//进行点更新
    {
        sum[o]=sqrt(sum[o]);
        return ;
    }
    int m=MID(l,r);
    if(ql<=m)update(o<<1,l,m,ql,qr);
    if(qr>=m+1)update(o<<1|1,m+1,r,ql,qr);
    pushup(o);
}
LL query(int o,int l,int r,int ql,int qr)//普通区间求和函数
{
    if(ql<=l&&qr>=r)
    {
        return sum[o];
    }
    int m=MID(l,r);
    LL ans=0;
    if(ql<=m)ans+=1ll*query(o<<1,l,m,ql,qr);
    if(qr>m)ans+=1ll*query(o<<1|1,m+1,r,ql,qr);
    return ans;
}
int main()
{
    int kase=0;
    while(cin>>n)
    {
        printf("Case #%d:\n",++kase);
        build(1,1,n);
        cin>>m;
        int a,b,c;
        while(m--)
        {
            scanf("%d%d%d",&c,&a,&b);
            if(a>b)swap(a,b);
            if(c==0)
            {
                update(1,1,n,a,b);
            }
            else
            {
                cout<<query(1,1,n,a,b)<<endl;
            }
            
        }
        cout<<endl;
    }
   // system("pause");
    return 0;
}
```
### 区间修改加法，乘法，置换，区间查询每个数的幂的和
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
const int INF = 0x3f3f3f3f ;
const int maxn = 100010;
const double pi = acos(-1.0);
const int mod=10007;
int T,n,m;
bool flag[maxn*4];//此问题懒惰标记标记为此区间的所有数字是否相同，因为运算较多，难以对每种运算都进行懒惰标记处理
int num[maxn*4];//区间的数字
int quick_pow(int a,int b)//快速幂取模模板
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=((ans%mod)*(a%mod))%mod;
        a=(a%mod)*(a%mod)%mod;
        b>>=1;
    }
    return ans;
}
void pushdown(int o)//向下更新
{
    if(flag[o])//如果此区间的所有数相同，向下更新
    {
        num[o<<1]=num[o<<1|1]=num[o];
        flag[o<<1]=flag[o<<1|1]=1;
        flag[o]=0;//标记清零
    }
}
void pushup(int o)//向上更新
{
    if(flag[o<<1]&&flag[o<<1|1]&&num[o<<1]==num[o<<1|1]){
        flag[o]=1;
        num[o]=num[o<<1];
    }
    else flag[o]=0;
}
void update(int o,int l,int r,int ql,int qr ,int c,int op)//区间更新
{

    if(ql<=l&&qr>=r&&flag[o])//只有此区间的所有数字相同时才能进行运算
    {
        if(op==1)
        {
            num[o]=(num[o]%mod+c%mod)%mod;
        }
        else if(op==2)
        {
            num[o]=((num[o]%mod)*(c%mod))%mod;
        }
        else if(op==3)
        {
            num[o]=c;
        }
        return;
    }
    pushdown(o);
    int m=MID(l,r);
    if(ql<=m)update(o<<1,l,m,ql,qr,c,op);
    if(qr>m)update(o<<1|1,m+1,r,ql,qr,c,op);
    pushup(o);
}
int query(int o,int l,int r,int ql,int qr,int p)//区间查询
{   
    if(ql<=l&&qr>=r&&flag[o])//只有此区间的所有数字相同时才能进行幂的求和运算
    {
        
        int ans=quick_pow(num[o],p);
        ans=(ans*(r-l+1))%mod;
        return ans;
    }
    pushdown(o);
    int m=MID(l,r);
    int ans=0;
    if(ql<=m)ans+=query(o<<1,l,m,ql,qr,p);
    if(qr>m)ans+=query(o<<1|1,m+1,r,ql,qr,p);
    return ans%mod;
}
int main()
{
    while (cin >> n >> m)
    {
        if(n==0&&m==0)break;
        mem(flag,1);
        mem0(num);
        int a, b, c, d;
        while (m--)
        {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            if(a<=3)
            {
                update(1,1,n,b,c,d,a);
            }
            else
            {
                printf("%d\n",query(1,1,n,b,c,d));
            }
        }
    }
   // system("pause");
    return 0;
}
```
### 区间修改是否覆盖，区间查询相邻剩余空间左右端点值
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
const int INF = 0x3f3f3f3f ;
const int maxn = 50005;
const double pi = acos(-1.0);
int T,n,m;
int sum[maxn*4];//标记区间内已经覆盖范围的大小
void pushdown(int o,int l,int r)//向下更新
{
    if(sum[o]==r-l+1)//如果区间全覆盖
    {
        int m=MID(l,r);
        sum[o<<1]=m-l+1;
        sum[o<<1|1]=r-m;
    }
    if(sum[o]==0)//如果区间全没覆盖
    {
        sum[o<<1]=sum[o<<1|1]=0;
    }
}
void pushup(int o)//向上更新
{
    sum[o]=sum[o<<1]+sum[o<<1|1];
}
void update(int o,int l,int r,int ql,int qr,int c)//更新函数c={0,1}1代表覆盖了
{
    if(ql<=l&&qr>=r)
    {
        sum[o]=(r-l+1)*c;
        return;
    }
    pushdown(o,l,r);
    int m=MID(l,r);
    if(ql<=m)update(o<<1,l,m,ql,qr,c);
    if(qr>m)update(o<<1|1,m+1,r,ql,qr,c);
    pushup(o);
}
int query(int o,int l,int r,int ql,int qr)//查询函数
{
    if(ql<=l&&qr>=r)
    {
        return sum[o];
    }
    pushdown(o,l,r);
    int m=MID(l,r);
    int ans=0;
    if(ql<=m)ans+=query(o<<1,l,m,ql,qr);
    if(qr>m)ans+=query(o<<1|1,m+1,r,ql,qr);
    return ans;
}
int find(int qi,int num)//找从起点出发向右的端点，要想覆盖num的范围，需要覆盖到的最近的右端点
{
    //查询的区间内的剩余容量必须大于等于查询的容量，如果小于，需在调用find函数时修改查询的num的大小
    int l=qi,r=n;
    int ans=INF;
    while(l<=r)//二分查找
    {
        int m=MID(l,r);
        int shu=query(1,1,n,qi,m);
        int kong=m-qi+1-shu;
        if(kong>=num)
        {
            ans=min(ans,m);
            r=m-1;
        }
        else l=m+1;
    }
    return ans;
}
int main()
{
    cin>>T;
    while (T--)
    {
        mem0(sum);
        cin>>n>>m;
        int k,a,b;
        while(m--)
        {
            scanf("%d%d%d",&k,&a,&b);
            if(k==1)//charu
            {
                a++;
                int tmp=query(1,1,n,a,n);
                if(tmp==n-a+1)//如果查询区间全被覆盖
                {
                    printf("Can not put any one.\n");
                    continue;
                }
                int kong=n-a+1-tmp;
                if(kong<b)b=kong;//如果查询区间的剩余容量小于查询容量，修改查询容量
                int f1=find(a,1);
                int f2=find(a,b);
                update(1,1,n,f1,f2,1);
                cout<<f1-1<<" "<<f2-1<<endl;
            }
            else if(k==2)
            {
                a++,b++;
                cout<<query(1,1,n,a,b)<<endl;
                update(1,1,n,a,b,0);
            }
        }
        cout<<endl;
    }
    
    //system("pause");
    return 0;
}
```
### 区间修改覆盖/清空，区间查询相应长的连续空间是否存在
```c
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<bitset>
#include<cstdlib>
#include<cmath>
#include<set>
#include<list>
#include<deque>
#include<map>
#include<queue>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
const int INF = 0x3f3f3f3f ;
const int maxn = 50100;
const double pi = acos(-1.0);
int T,n,m;
int ls[maxn*3];//线段树区间从左端点开始最长连续区间的长度
int rs[maxn*3];//线段树区间从右端点开始向左最长连续区间的长度
int maxs[maxn*3];//此区间内最长连续区间的长度
int cover[maxn*3];//具体操作是当这个区间全部是1时color置1，全部为0时color置0，否则置-1。在pushup()的时候会用到。
void build(int o,int l,int r)
{
    cover[o]=-1;//建树
    ls[o]=r-l+1;
    rs[o]=r-l+1;
    maxs[o]=r-l+1;
    if(l==r)return ;
    int m=MID(l,r);
    build(o<<1,l,m);
    build(o<<1|1,m+1,r);
}
void pushdown(int o,int l,int r)
{
    int k=r-l+1;
    if(cover[o]!=-1)//如果区间内全为1或者0，则向下更新
    {
        cover[o<<1]=cover[o<<1|1]=cover[o];
        ls[o<<1]=rs[o<<1]=maxs[o<<1]=cover[o]?0:(k-(k>>1));
        ls[o<<1|1]=rs[o<<1|1]=maxs[o<<1|1]=cover[o]?0:(k>>1);
        cover[o]=-1;//标记清零
    }
}
void pushup(int o,int l,int r)
{   
    向上更新
    int k=r-l+1;
    ls[o]=ls[o<<1];
    rs[o]=rs[o<<1|1];
    if(ls[o]==k-(k>>1))ls[o]+=ls[o<<1|1];//如果当前ls长度等于左半区间的长度,ls加上右半区间的ls
    if(rs[o]==k>>1)rs[o]+=rs[o<<1];//同理
    maxs[o]=max(rs[o<<1]+ls[o<<1|1],max(maxs[o<<1],maxs[o<<1|1]));//区间的最大区间长度

}
void update(int o,int l,int r,int ql,int qr,int c)
{
    if(ql<=l&&qr>=r)
    {
        ls[o]=rs[o]=maxs[o]=c?0:(r-l+1);
        cover[o]=c;
        return;
    }
    pushdown(o,l,r);
    int m=MID(l,r);
    if(ql<=m)update(o<<1,l,m,ql,qr,c);
    if(qr>m)update(o<<1|1,m+1,r,ql,qr,c);
    pushup(o,l,r);
}
int query(int o,int l,int r,int len)
{
    if(l==r)return l;
    pushdown(o,l,r);
    int m=(l+r)>>1;
    if(maxs[o<<1]>=len)return query(o<<1,l,m,len);//左
    else if(rs[o<<1]+ls[o<<1|1]>=len)return m-rs[o<<1]+1;//中
    else return query(o<<1|1,m+1,r,len);//右
}
int main()
{
    while(cin>>n>>m)
    {
        build(1,1,n);
        while(m--)
        {
            int a,b,c;
            scanf("%d%d",&c,&a);
            if(c==1)
            {
                if(maxs[1]<a)
                {
                    cout<<"0"<<endl;
                    continue;
                }
                int pos=query(1,1,n,a);
                cout<<pos<<endl;
                update(1,1,n,pos,pos+a-1,1);
            }
            else 
            {
                scanf("%d",&b);
                update(1,1,n,a,a+b-1,0);
            }
        }
    }
    return 0;
}
```
### 求二维图形的边长（数据离散化）
```c
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <set>
#include <list>
#include <deque>
#include <map>
#include <queue>
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define F first
#define S second
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MID(l, r) (l + ((r - l) >> 1))
#define ll(o) (o << 1)
#define rr(o) (o << 1 | 1)
const int INF = 0x3f3f3f3f;
const int maxn = 10000 + 100;
const double pi = acos(-1.0);
int T, n, m;
struct Edge
{
    int l, r, f, h;
    bool operator<(const Edge &tmp) const
    {
        return h < tmp.h;
    }
    void get(int lt, int rt, int ht, int ft)
    {
        h = ht, l = lt, r = rt, f = ft;
    }
} edge1[maxn * 2], edge2[maxn * 2];
int x[maxn * 2], y[maxn * 2];
int xt, yt;
int len[maxn * 3];
int tag[maxn * 3];
void build(int o, int l, int r)
{
    len[o] = tag[o] = 0;
    if (l == r)
        return;
    int m = MID(l, r);
    build(ll(o), l, m);
    build(rr(o), m + 1, r);
}
void pushup(int o, int l, int r)
{
    if (tag[o])
        len[o] = x[r] - x[l - 1];
    else
        len[o] = len[ll(o)] + len[rr(o)];
}
void update(int o, int l, int r, int ql, int qr, int c)
{
    if(ql>r||qr<l)return;
    if (ql <= l && qr >= r)
    {
        tag[o] += c;
        pushup(o, l, r);
        return;
    }
    int m = MID(l, r);
    update(ll(o), l, m, ql, qr, c);
    update(rr(o), m + 1, r, ql, qr, c);
    pushup(o, l, r);
}

int t = 0;
int main()
{
    while (cin >> n)
    {
        t = 0;
        int a1, b1, a2, b2;
        xt = yt = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
            edge1[t].get(a1, a2, b1, 1);
            edge2[t++].get(b1, b2, a1, 1);
            edge1[t].get(a1, a2, b2, -1);
            edge2[t++].get(b1, b2, a2, -1);
            x[xt++] = a1;
            x[xt++] = a2;
            y[yt++] = b1;
            y[yt++] = b2;
        }
        sort(edge1, edge1 + t);
        sort(edge2, edge2 + t);
        sort(x, x + xt);
        sort(y, y + yt);
        xt = unique(x, x + t) - x;
        yt = unique(y, y + t) - y;
        int ans = 0;
        int last = 0;
        build(1,1,xt);
        for (int i = 0; i < t; i++)
        {
            
            int l = lower_bound(x, x + xt, edge1[i].l) - x + 1;
            int r = lower_bound(x, x + xt, edge1[i].r) - x;
            update(1,1,xt,l,r,edge1[i].f);
            int tmp = len[1];
            ans+=abs(tmp-last);
            last=tmp;
            
            
        }
        xt=yt;
        for(int i=0;i<xt;i++)x[i]=y[i];
        last=0;
        build(1,1,xt);
        for (int i = 0; i < t; i++)
        {
            int l = lower_bound(x, x + xt, edge2[i].l) - x + 1;
            int r = lower_bound(x, x + xt, edge2[i].r) - x;
            update(1,1,xt,l,r,edge2[i].f);
            int tmp = len[1];
            ans+=abs(tmp-last);
            last=tmp;
            
        }
        cout<<ans<<endl;
    }
  //  system("pause");
    return 0;
}
/*
2
10 10 20 20
15 15 25 25
 */
```
### 求二维空间的面积
```c++
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define F first
#define S second
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MID(l, r) (l + ((r - l) >> 1))
#define ll(o) (o << 1)
#define rr(o) (o << 1 | 1)
const int INF = 0x3f3f3f3f;
const int maxn = 10000 + 100;
const double pi = acos(-1.0);
int T, n, m;
struct Edge
{
    int l, r, f, h;
    bool operator<(const Edge &tmp) const
    {
        return h < tmp.h;
    }
    void get(int lt, int rt, int ht, int ft)
    {
        h = ht, l = lt, r = rt, f = ft;
    }
} edge1[maxn * 2], edge2[maxn * 2];
int x[maxn * 2], y[maxn * 2];
int xt, yt;

int len[maxn * 3];
int tag[maxn * 3];
void build(int o, int l, int r)
{
    len[o] = tag[o] = 0;
    if (l == r)
        return;
    int m = MID(l, r);
    build(ll(o), l, m);
    build(rr(o), m + 1, r);
}
void pushup(int o, int l, int r)
{
    if (tag[o])
        len[o] = x[r] - x[l - 1];
    else
        len[o] = len[ll(o)] + len[rr(o)];
}
void update(int o, int l, int r, int ql, int qr, int c)
{
    if(ql>r||qr<l)return;
    if (ql <= l && qr >= r)
    {
        tag[o] += c;
        pushup(o, l, r);
        return;
    }
    int m = MID(l, r);
    update(ll(o), l, m, ql, qr, c);
    update(rr(o), m + 1, r, ql, qr, c);
    pushup(o, l, r);
}

int t = 0;
int main()
{
    while (cin >> n)
    {
        t = 0;
        int a1, b1, a2, b2;
        xt = yt = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
            edge1[t].get(a1, a2, b1, 1);
            edge2[t++].get(b1, b2, a1, 1);
            edge1[t].get(a1, a2, b2, -1);
            edge2[t++].get(b1, b2, a2, -1);
            x[xt++] = a1;
            x[xt++] = a2;
            y[yt++] = b1;
            y[yt++] = b2;
        }
        sort(edge1, edge1 + t);
        sort(edge2, edge2 + t);
        sort(x, x + xt);
        sort(y, y + yt);
        xt = unique(x, x + t) - x;
        yt = unique(y, y + t) - y;
        int ans = 0;
        int last = 0;
        build(1,1,xt);
        for (int i = 0; i < t; i++)
        {
            
            int l = lower_bound(x, x + xt, edge1[i].l) - x + 1;
            int r = lower_bound(x, x + xt, edge1[i].r) - x;
            update(1,1,xt,l,r,edge1[i].f);
            int tmp = len[1];
            ans+=abs(tmp-last);
            last=tmp;
            
            
        }
        xt=yt;
        for(int i=0;i<xt;i++)x[i]=y[i];
        last=0;
        build(1,1,xt);
        for (int i = 0; i < t; i++)
        {
            int l = lower_bound(x, x + xt, edge2[i].l) - x + 1;
            int r = lower_bound(x, x + xt, edge2[i].r) - x;
            update(1,1,xt,l,r,edge2[i].f);
            int tmp = len[1];
            ans+=abs(tmp-last);
            last=tmp;
            
        }
        cout<<ans<<endl;
    }
  //  system("pause");
    return 0;
}
/*
2
10 10 20 20
15 15 25 25
 */
```
---
# 主席树
### 静态第k大
```c
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <bitset>
#include <cstdlib>
#include <cmath>
#include <set>
#include <list>
#include <deque>
#include <map>
#include <queue>
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define F first
#define S second
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MID(l, r) (l + ((r - l) >> 1))
#define ll(o) (o << 1)
#define rr(o) (o << 1 | 1)
const int INF = 0x3f3f3f3f;
const int maxn = 200010;
const double pi = acos(-1.0);
/*
将原始数组复制一份，然后排序好，然后去掉多余的数，即将数据离散化。推荐使用C++的STL中的unique函数；
以离散化数组为基础，建一个全0的线段树，称作基础主席树；
对原数据中每一个[1,i]区间统计，有序地插入新节点（题目中i每增加1就会多一个数，仅需对主席树对应的节点增加1即可）；
对于查询[1,r]中第k小值的操作，找到[1,r]对应的根节点，我们按照线段树的方法操作即可（这个根节点及其子孙构成的必定是一颗线段树）。
 */
int node_cnt, n, m;
int sum[maxn << 5], rt[maxn << 5], lc[maxn << 5], rc[maxn << 5]; //线段树相关 sum记录线段树权值
int a[maxn], b[maxn];                                            //原数组和离散数组
int p;                                                           //修改点
void build(int &t, int l, int r)//递归建树
{
    t = ++node_cnt;
    if (l == r)
        return;
    int mid = MID(l, r);
    build(lc[t], l, mid);
    build(rc[t], mid + 1, r);
}
int update(int o, int l, int r)
{
    int oo = ++node_cnt; //生成新的节点
    lc[oo] = lc[o];
    rc[oo] = rc[o];
    sum[oo]=sum[o]+1;//因为新的版本的线段树一定比旧的版本多一个数，所以权值加一
    //" "<<l<<" "<<r<<" "<<lc[oo]<<" "<<rc[oo]<<" "<<sum[oo]<<endl;
    if (l == r)
        return oo;
    int mid = MID(l, r);
    if (p <= mid)//更新的值在左半区间
        lc[oo] = update(lc[oo], l, mid);
    else//跟新的值在右半区间内
        rc[oo] = update(rc[oo], mid + 1, r);
    return oo;
}
int query(int u,int v,int l,int r,int k)
{   
    int ans,mid=MID(l,r);
    int x=sum[lc[v]]-sum[lc[u]];//获取区间[1,v]-[1,u-1]的左子树上的权值
    if(l==r)return l;
    if(x>=k)//权值大于查询的值，数在左半区间
        ans= query(lc[u],lc[v],l,mid,k);
    else
        ans= query(rc[u],rc[v],mid+1,r,k-x);
    return ans;
}
int main()
{
    int l, r, k, q, ans;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]), b[i] = a[i];
    }
    //进行数据离散化
    sort(b + 1, b + 1 + n);
    q = unique(b + 1, b + 1 + n) - b - 1;
    build(rt[0], 1, q);
    //建立基础主席树
    for (int i = 1; i <= n; i++)
    {
        p = lower_bound(b + 1, b + q + 1, a[i]) - b;
        rt[i] = update(rt[i - 1], 1, q);//更新[1,i],i=1,2,3,···，n
        cout<<"----------------\n";
    }
    for(int i=1;i<=node_cnt;i++)
    {
        cout<<"root"<<i<<" "<<lc[i]<<" "<<rc[i]<<endl;
    }
    cout<<node_cnt<<"!!!!\n";
    while(m--)
    {
        scanf("%d%d%d",&l,&r,&k);
        ans = query(rt[l-1],rt[r],1,q,k);//进行查询
        printf("%d\n",b[ans]);
    }
    system("pause");
    return 0;
}
//4 1 1 2 8 9 4 4 3 
```
### 树上路径第k大
```c
#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a, b) make_pair(a, b)
#define F first
#define S second
#define pii pair<int, int>
#define mem0(a) memset(a, 0, sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define MID(l, r) (l + ((r - l) >> 1))
#define ll(o) (o << 1)
#define rr(o) (o << 1 | 1)
const int INF = 0x3f3f3f3f;
const int DEG = 20;
const int maxn = 100000 + 10;
const double pi = acos(-1.0);

struct Edge //链式前向星的边结构体
{
    int to, next;
} edge[maxn * 2];
int head[maxn];  //链式前向星需要
int tot = 0;     //记录链式前向星中边的条数
int node_cnt, n; //主席树的节点个数、数的个数
int m;
int sum[maxn << 5], rt[maxn << 5], lc[maxn << 5], rc[maxn << 5]; //线段树相关 sum记录线段树权值
int a[maxn], b[maxn];                                            //原数组和离散数组
int q;                                                           //离散数组的长度
int fa[maxn][DEG];                                               //LCA用 fa[i][j]表示 i的第2^j个祖先
int deg[maxn];                                                   //LCA用，表示第i个节点的深度，根节点的深度
void Init()                                                      //链式前向星初始化
{
    tot = 0;
    mem(head, -1);
}
void addedge(int u, int v) //链式前向星加边
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int update(int o, int l, int r, int k)//主席树更新
{
    int oo = ++node_cnt; //生成新的节点
    lc[oo] = lc[o];
    rc[oo] = rc[o];
    sum[oo] = sum[o] + 1; //因为新的版本的线段树一定比旧的版本多一个数，所以权值加一
    if (l == r)
        return oo;
    int mid = MID(l, r);
    if (k <= mid) //更新的值在左半区间
        lc[oo] = update(lc[oo], l, mid, k);
    else //更新的值在右半区间内
        rc[oo] = update(rc[oo], mid + 1, r, k);
    return oo;//返回新节点的标号
}
int query(int u, int v, int u1, int v1, int l, int r, int k)
{
    if (l == r)
        return l;
    int ans, mid = MID(l, r);
    int x = sum[lc[v]] + sum[lc[u]] - sum[lc[u1]] - sum[lc[v1]]; //获取区间[1,v]-[1,u-1]的左子树上的权值
    if (x >= k)                                                  //权值大于查询的值，数在左半区间
        ans = query(lc[u], lc[v], lc[u1], lc[v1], l, mid, k);
    else
        ans = query(rc[u], rc[v], rc[u1], rc[v1], mid + 1, r, k - x);
    return ans;
}
int get(int x)//获得x在离散数组中的位置
{
    return lower_bound(b + 1, b + 1 + q, x) - b;
}
void DFS(int root, int fu) //DFS求深度 LCA用
{

    deg[root] = deg[fu] + 1;
    fa[root][0] = fu;
    for (int i = 1; i < DEG; i++)
    {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
    }
    rt[root] = update(rt[fu], 1, q, get(a[root]));
    for (int i = head[root]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == fu)
            continue;
        DFS(v, root);
    }
}
int LCA(int u, int v)
{
    if (deg[u] > deg[v])
        swap(u, v);
    int hu = deg[u], hv = deg[v];
    int tu = u;
    int tv = v;
    for (int det = hv - hu, i = 0; det; det >>= 1, i++)//让tv和tu处于同一深度
        if (det & 1)
            tv = fa[tv][i];//深的节点向上走
    if (tu == tv)
        return tv;
    for (int i = DEG - 1; i >= 0; i--)
    {
        if (fa[tu][i] == fa[tv][i])
            continue;
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return fa[tu][0];//tu的父亲节点即为LCA(u,v)
}
int main()
{
    node_cnt = 0;
    int l, r, k, ans;
    cin >> n >> m;
    Init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    q = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d%d", &l, &r);
        addedge(l, r);
        addedge(r, l);
    }
    mem0(fa);//初始化
    mem0(deg);//
    DFS(1, 0);
    while (m--)
    {
        scanf("%d%d%d", &l, &r, &k);
        int lca = LCA(l, r);
        cout << b[query(rt[l], rt[r], rt[lca], rt[fa[lca][0]], 1, q, k)] << endl;
    }
    system("pause");
    return 0;
}
```
---
# 最近公共祖先（最小公共祖先）（LCA）
### 倍增法
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
#define ll(o) (o<<1)
#define rr(o) (o<<1|1)
const int INF = 0x3f3f3f3f ;
const int maxn = 10000;
const double pi = acos(-1.0);
int T,n,m;
const int DEG=20;
struct Edge//链式前向星的边结构体
{
    int to,next;
}edge[maxn*2];
int head[maxn],tot;
void addedge(int u,int v)//链式前向星加边
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
void init()//初始化
{
    tot=0;
    mem(head,-1);
}
int fa[maxn][DEG];//表示节点i的第2^j个祖先
int deg[maxn];//深度数组
void BFS(int root)//BFS求深度
{
    queue<int>que;
    deg[root]=0;//
    fa[root][0]=root;//初始化根节点的父亲是root
    que.push(root);
    while(!que.empty())
    {
        int tmp=que.front();
        que.pop();
        for(int i=1;i<DEG;i++)//找到这个节点所有的祖先节点
        {
            fa[tmp][i]=fa[fa[tmp][i-1]][i-1];//2^i=2^(i-1)+2^(i-1)表示 tmp向上跳2的i次的节点=tmp向上跳i-1次方的这个节点向上跳i-1次方
        }
        for(int i=head[tmp];i!=-1;i=edge[i].next)
        {
            int v=edge[i].to;
            if(v==fa[tmp][0])continue;//v等于tmp的父亲节点，跳过
            deg[v]=deg[tmp]+1;//记录深度
            fa[v][0]=tmp;//记录父亲
            que.push(v);//入队
        }
    }
}
void DFS(int root,int fu)//DFS求深度
{
    deg[root]=deg[fu]+1;
    fa[root][0]=fu;
    for(int i=1;i<DEG;i++)
    {
        fa[root][i]=fa[fa[root][i-1]][i-1];
    }
    for(int i=head[root];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==fu)continue;
        DFS(v,root);
    }
}
int LCA(int u,int v)
{
    if(deg[u]>deg[v])swap(u,v);//
    int hu=deg[u],hv=deg[v];
    int tu=u;
    int tv=v;
    for(int det=hv-hu,i=0;det;det>>=1,i++)//让u和v跳到同一个深度
        if(det&1)
            tv=fa[tv][i];
    if(tu==tv)return tu;//如果tu==tv说明在同一边
    for(int i=DEG-1;i>=0;i--)
    {
        if(fa[tu][i]==fa[tv][i])continue;
        tu=fa[tu][i];
        tv=fa[tv][i];
    }
    return fa[tu][0];//父亲节点即为lca
}
int main()
{
    system("pause");
    return 0;
}
```
