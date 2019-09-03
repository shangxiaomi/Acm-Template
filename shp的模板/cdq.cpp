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
    while(pl<=mid&&pr<=r)
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
        rm(tmp[i].z);
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
    sort(tmp+1,tmp+1+n);
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
    cdq(1,tot);
    for(int i=1;i<=tot;i++)
    {
        ji[ans[node[i].id]+node[i].val-1]+=node[i].val;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d\n",ji[i]);
    }
    //system("pause");
    return 0;
}