
记得上限要变换成2的幂次

```cpp
#include <bits/stdc++.h>
#define cp complex<double>
using namespace std;
const int maxn=5000000+9;
cp F[maxn],G[maxn];
int c[maxn];

const double pi=acos(-1);
int rev[maxn];
void fft(cp *a,int n,int inv)
{
    int bit=0;
    while ((1<<bit)<n)bit++;
    for(int i=0;i<n;i++)
    {
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
        if (i<rev[i])swap(a[i],a[rev[i]]);//不加这条if会交换两次（就是没交换）
    }
    for (int mid=1;mid<n;mid*=2)//mid是准备合并序列的长度的二分之一
    {
    	cp temp(cos(pi/mid),inv*sin(pi/mid));//单位根，pi的系数2已经约掉了
        for (int i=0;i<n;i+=mid*2)//mid*2是准备合并序列的长度，i是合并到了哪一位
		{
            cp omega(1,0);
            for (int j=0;j<mid;j++,omega*=temp)//只扫左半部分，得到右半部分的答案
            {
                cp x=a[i+j],y=omega*a[i+j+mid];
                a[i+j]=x+y,a[i+j+mid]=x-y;//这个就是蝴蝶变换什么的
            }
        }
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++){
        int x;scanf("%d",&x);
        F[i]=cp(1.0*x,0);
    }
    for(int i=0;i<=m;i++){
        int x;scanf("%d",&x);
        G[i]=cp(1.0*x,0);
    }
    int LMIN=1;
    while(LMIN<n+m+2)LMIN<<=1;
    fft(F,LMIN,1),fft(G,LMIN,1);
    for(int i=0;i<=LMIN;i++)F[i]*=G[i];
    fft(F,LMIN,-1);
    for(int i=0;i<=LMIN;i++)c[i]=(int) (F[i].real()/LMIN+0.5);
    for(int i=0;i<=n+m;i++)printf("%d ",c[i]);
    cout<<endl;
}

```