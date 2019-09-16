https://blog.csdn.net/qq_38944163/article/details/82919189
## CDQ分治
在了解这种算法之前，我们有必要了解一下一种基本的思想：分治 ，并且只能**离线**
我们在合并两个子区间的时候，要考虑到左边区间的对右边区间的影响
在合并的时候，我们只处理左区间的修改，只统计右区间的查询
因为左区间的修改一定可以影响右区间的查询
### 例题 三维偏序问题
给定N个有序三元组(a,b,c)，求对于每个三元组(a,b,c)，有多少个三元组(a0,b0,c0)满足a0 < a且b0 < b且c0 < c 
类似二维偏序问题，先按照a元素从小到大排序，这样我们就可以忽略a元素的影响 
然后CDQ分治，按照b元素从小到大进行归并排序 
哪c元素我们要怎么处理呢？ 
这时候比较好的方案就是借助权值树状数组， 
每次从左边取出三元组（a，b，c），根据c值在树状数组中进行修改 
从右边的序列中取出三元组（a，b，c）时，在树状数组中查询c值小于（a，b，c）的三元组的个数 
注意，每次使用完树状数组要把树状数组清零
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
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
#define ll(o) (o<<1)
#define rr(o) (o<<1|1)
const LL INF = 0x3f3f3f3f ;
const int maxn = 200001;
const double pi = acos(-1.0);
int T,n,m,k;
//BIT部分
int d[maxn];
void add(int i,int x)
{
    while(i<maxn)
    {
        d[i]+=x;
        i+=(i&-i);
    }
}
int ask(int i)
{
    int res=0;
    while(i)
    {
        res+=d[i];
        i-=(i&-i);
    }
    return res;
}
void rm(int i)
{
    while(i<maxn)
    {
        d[i]=0;
        i+=(i&-i);
    }
}
//BIT部分结束
struct Node
{
    int x,y,z,id,val;
    bool operator==(const Node&tmp)const
    {
        return (x==tmp.x&&y==tmp.y&&z==tmp.z);
    }
    bool operator<(const Node&tmp)const
    {
        if(x!=tmp.x)return x<tmp.x;
        if(y!=tmp.y)return y<tmp.y;
        return z<tmp.z;
    }
}node[maxn],tmp[maxn];
int ji[maxn]={0};
int ans[maxn]={0};
void cdq(int l,int r)
{
    if(l>=r)return ;
    int mid=MID(l,r);
    cdq(l,mid),cdq(mid+1,r);
    int cnt=0;
    int pl=l,pr=mid+1;
    while(pl<=mid&&pr<=r)//只进行左半部分中的修改操作
    {
        if(node[pl].y<=node[pr].y)
        {
            add(node[pl].z,node[pl].val);
            tmp[++cnt]=node[pl++];
        }
        else
        {
            ans[node[pr].id]+=ask(node[pr].z);
            tmp[++cnt]=node[pr++];
        }
    }
    while(pl<=mid)
    {
        tmp[++cnt]=node[pl++];
    }
    while(pr<=r)
    {
        ans[node[pr].id]+=ask(node[pr].z);
        tmp[++cnt]=node[pr++];
    }
    for(int i=1;i<=cnt;i++)
    {
        node[l+i-1]=tmp[i];
        rm(tmp[i].z);//清除BIT,不能用memset
    }
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&tmp[i].x,&tmp[i].y,&tmp[i].z);
    }
    int tot=0;
    sort(tmp+1,tmp+1+n);//对一维的x坐标排序
    //去重
    node[++tot]=tmp[1];
    node[tot].id=1;
    node[tot].val=1;
    for(int i=2;i<=n;i++)
    {
        if(tmp[i]==tmp[i-1])node[tot].val++;
        else
        {
            node[++tot]=tmp[i];
            node[tot].val=1;
            node[tot].id=tot;
        }
    }
    //去重结束
    cdq(1,tot);
    for(int i=1;i<=tot;i++)
    {
        ji[ans[node[i].id]+node[i].val-1]+=node[i].val;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d\n",ji[i]);
    }
    return 0;
}
```
### 三维偏序问题扩展
平面上有N个点，每个点的横纵坐标在[0,1e7]之间，有M个询问，每个询问为查询在指定矩形之内有多少个点，矩形用(x1,y1,x2,y2)的方式给出，其中(x1,y1)为左下角坐标，(x2,y2)为右上角坐标

把每个点的位置变成一个修改操作，用三元组（时间，横坐标，纵坐标）来表示，把每个查询变成二维前缀和的查询 
这样对于只有位于询问的左下角的修改，才对询问有影响 
操作的时间是默认有序的，分治过程中按照横坐标从小到大排序，用树状数组维护纵坐标的信息
