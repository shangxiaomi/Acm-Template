##DAG上概率dp
注意期望和概率的区别
根据实际意义列出递推式
移项化简后决定正推还是逆推
基本上DAG就是拓扑序了
**具体顺序还是看你怎么推样例的吧**

概率dp是一类求期望/概率的题目
简单总结一下做法
对于求期望
1.先将状态定义出来
2.然后对于每一个状态u uu，考虑他可能的下一个状态v vv，于是从u uu到v vv连一条概率为puv p_{uv}p 
uv
​	
 的边。于是写出一个方程
$$ dp[u]=(\sum{dp[v]*p[u][v]})+1$$

假如这是一个DAG，那么这是个水题，倒着推回去就结束了。

假如不是一个DAG，那么可能会有下面这些东西

    自环
    一条连回某个固定点的边
    一条连回根据当前点确定的某个点的边
    更多。。。
那么一种思路是要转化成一个DAG，在写出方程后：

自环：移项，消掉
把那些不和谐的边拆出来，设一个参数方程：
$$ dp[i]=A_1[i]dp[f_1(i)]+A_2[i]dp[f_2(i)]+...A_n[i]dp[f_n(i)]+B[i]$$
其中$f_k(i)$是那些异常点，那些拓扑序靠后的点都被扔进了B[i]里，然后把这一坨东西丢进刚开始写出的那个方程的右边，把dp[v] 都代换掉，就会写出来一个参数为i的参数方程，接下来问题转换为求$A_t[i]$,看一下同类项，就可以把参数的递推式写出来。
对于求概率，类似期望，不过要正着推；比较好考虑的的一个原因是结束点到结束点的期望肯定是零，而最初状态的概率一般是好算的。



```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef long long ll;
typedef double db;
const int MAXN=400000+7;
vector<int> nextto[MAXN];
int inde[MAXN], order[MAXN], outde[MAXN];
double dp[MAXN], day[MAXN];
void addedge(int st, int ed){
    nextto[st].push_back(ed);
    inde[ed] ++;
    outde[st] ++;
}
int N, M;
void init(){
    memset(inde, 0, sizeof inde);
    memset(outde, 0, sizeof outde);
    for(int i = 0; i <= N; i ++)
        nextto[i].clear();
}
void topo(){
    queue<int> q;
    int cnt=0;
    /*
    for(int i = 0; i < N; i ++){
        if(inde[i] == 0)    q.push(i), order[cnt ++] = i;
    }*/
    order[cnt++]=1;
    q.push(1);

    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(auto ed : nextto[now]){
            inde[ed] --;
            if(inde[ed] == 0)   order[cnt ++] = ed, q.push(ed);
        }

    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d %d",&N,&M);
        for(int i=0;i<M;i++){
            int a,b;
            scanf("%d%d" , &a, &b);
            addedge(a, b);
        }
        topo();
        for(int i = N-1; i >= 0; i --){
            int U = order[i];
            day[U] = 0.0;
            if(outde[U] == 0)continue;
            for(auto ed : nextto[U])
                day[U] += day[ed];
            day[U] /= 1.0 * outde[U];
            day[U] += 1.0 / outde[U] + 1;
        }
        for(int i = N-1; i >= 0; i --){
            int U = order[i];
            dp[U] = 0.0;
            if(outde[U] == 0) continue;
            for(auto ed : nextto[U])
                dp[U] += dp[ed];
            dp[U] /= 1.0 * outde[U];
            dp[U] += day[U] * ( 1 + 1.0 * outde[U]) / outde[U];
        }
        printf("%.2f\n", dp[1]);
    }
    return 0;
}

```
