#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
#define mkp(a,b) make_pair(a,b)
#define F first
#define ep(a) emplace_back(a)
#define S second
#define pii pair<int,int>
#define mem0(a) memset(a,0,sizeof(a))
#define mem(a,b) memset(a,b,sizeof(a))
#define MID(l,r) (l+((r-l)>>1))
#define ll(o) (o<<1)
#define rr(o) (o<<1|1)
const int INF = 0x3f3f3f3f ;
const int maxn = 110000;
const double pi = acos(-1.0);
int T,n,m;
const int N_ch=26;
struct SAM
{
    int fa[maxn<<1],nxt[maxn<<1][N_ch],val[maxn<<1];
    int right[maxn<<1];
    int root,tail,n_node;
    int new_node(int v)
    {
        int p=++n_node;
        memset(nxt[p],0,sizeof(nxt[p]));
        fa[p]=0;right[p]=0;val[p]=v;
        return n_node;
    }
    void init(){
        root = tail = new_node(n_node=0);
    }
    void rel(){tail=1;}
    void add(int c)
    {
        int p=tail,np=new_node(val[p]+1);
        while(p&&!nxt[p][c])nxt[p][c]=np,p=fa[p];
        if(!p)fa[np]=root;
        else{
            int q=nxt[p][c];
            if(val[p]+1==val[q])fa[np]=q;
            else{
                int nq=new_node(val[p]+1);
                for(int i=0;i<N_ch;i++)nxt[nq][i]=nxt[q][i];
                fa[nq]=fa[q],fa[q]=fa[np]=nq;
                while(p&&nxt[p][c]==q)nxt[p][c]=nq,p=fa[p];
            }
        }
        tail=np,right[np]=1;
    }
    int d[maxn*2],b[maxn*2];
    void topo_sort(int len)
    {
        for(int i=0;i<=n_node;i++)d[i]=0;
        for(int i=1;i<=n_node;i++)d[val[i]]++;
        for(int i=1;i<=len;i++)d[i]+=d[i-1];
        for(int i=1;i<=n_node;i++)b[d[val[i]]--]=i;
    }
    LL sum()
    {
        LL ans=0;
        for(int i=1;i<=n_node;i++)ans+=val[i]-val[fa[i]];
        return ans;
    }
}sam;
int main()
{
    system("pause");
    return 0;
}