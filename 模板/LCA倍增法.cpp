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