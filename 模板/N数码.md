>从八数码问题入手

我们首先从经典的八数码问题入手，即对于八数码问题的任意一个排列是否有解？有解的条件是什么？

我在网上搜了半天，找到一个十分简洁的结论。八数码问题原始状态如下：

1 2 3
4 5 6
7 8

为了方便讨论，我们把它写成一维的形式，并以0代替空格位置。那么表示如下：

1 2 3 4 5 6 7 8 0

通过实验得知，以下状态是无解的（交换了前两个数字1 2）：

2 1 3 4 5 6 7 8 0

八数码问题的有解无解的结论：

一个状态表示成一维的形式，求出除0之外所有数字的逆序数之和，也就是每个数字前面比它大的数字的个数的和，称为这个状态的逆序。

若两个状态的逆序奇偶性相同，则可相互到达，否则不可相互到达。

由于原始状态的逆序为0（偶数），则逆序为偶数的状态有解。

也就是说，逆序的奇偶将所有的状态分为了两个等价类，同一个等价类中的状态都可相互到达。

简要说明一下：当左右移动空格时，逆序不变。当上下移动空格时，相当于将一个数字向前（或向后）移动两格，跳过的这两个数字要么都比它大（小），逆序可能±2；要么一个较大一个较小，逆序不变。所以可得结论：只要是相互可达的两个状态，它们的逆序奇偶性相同。我想半天只能说明这个结论的必要性，详细的证明请参考后面的附件。

 

>推广二维N×N的棋盘 (poj 2893)

我们先来看看4×4的情况，同样的思路，我们考虑移动空格时逆序的变化情况。

1    2    3    4
5    6    7    8
9    A    B   C
D   E    F   

我们用字母A~F代替数字10~15。同样地，当左右移动的时候，状态的逆序不改变。而当上下移动的时候，相当于一个数字跨过了另外三个格子，它的逆序可能±3或±1，逆序的奇偶性必然改变。那么又该如何

1    2    3    4
5    6    7    8
9    A    B   
C   D   E    F   

可以证明，以上状态是一个无解的状态（将C移到了第四行）。该状态的逆序为0，和原始状态相同，但是它的空格位置在第三行。若将空格移到第四行，必然使得它的逆序±1或±3，奇偶性必然改变。所以它是一个无解的状态。

然而以下状态就是一个有解的状态（交换了前两个数字1 2）：

2    1    3    4
5    6    7    8
9    A    B   
C   D   E    F

这个状态的逆序为1，和原始状态奇偶性不同，而空格位置在第三行。由于空格每从第三行移动到第四行，奇偶性改变。则该状态的可到达原始状态。

通过观察，得出以下结论：

N×N的棋盘，N为奇数时，与八数码问题相同。

N为偶数时，空格每上下移动一次，奇偶性改变。称空格位置所在的行到目标空格所在的行步数为空格的距离（不计左右距离），若两个状态的可相互到达，则有，两个状态的逆序奇偶性相同且空格距离为偶数，或者，逆序奇偶性不同且空格距离为奇数数。否则不能。

也就是说，当此表达式成立时，两个状态可相互到达：（状态1的逆序数 + 空格距离)的奇偶性==状态2奇偶性。

另外再详细说明一下，无论N是奇数还是偶数，空格上下移动，相当于跨过N-1个格子。那么逆序的改变可能为一下值±N-1，±N-3，±N-5 …… ±N-2k-1。当N为奇数数时N-1为偶数，逆序改变可能为0；当N为偶数时N-1为奇数，逆序的改变不能为0，只能是奇数，所以没上下移动一次奇偶性必然改变。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1000000;
int ar[N],a[N];
int lowb(int t)
{
    return t & (-t) ;
}
void add(int i, int v)
{
    for ( ; i < N; ar[i] += v, i += lowb(i));
}
int sum(int i)
{
    int s = 0;
    for ( ; i > 0; s += ar[i], i -= lowb(i));
    return s;
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m),n||m)
    {
        int x,y,t,s=0,nu=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&t);
                if(t==0)
                    x=i,y=j;
                else
                    a[nu++]=t;
            }
        memset(ar,0,sizeof(ar));
        for(int i=nu-1;i>=0;i--)
        {
            s+=sum(a[i]-1);
            add(a[i],1);
        }
        if(m&1)
            if(s&1)puts("NO");
            else   puts("YES");
        else
            if(((n-x)^s)&1) puts("NO");
            else            puts("YES");
    }
    return 0;
}
```
 

>推广到三维N×N×N   ( zju 2004 )

其实，三维的结论和二维的结论是一样的。

考虑左右移动空格，逆序不变；同一层上下移动空格，跨过N-1个格子；上下层移动空格，跨过N^2-1个格子。

当N为奇数时，N-1和N^2-1均为偶数，也就是任意移动空格逆序奇偶性不变。那么逆序奇偶性相同的两个状态可相互到达。

当N为偶数时，N-1和N^2-1均为奇数，也就是令空格位置到目标状态空格位置的y z方向的距离之和，称为空格距离。若空格距离为偶数，两个逆序奇偶性相同的状态可相互到达；若空格距离为奇数，两个逆序奇偶性不同的状态可相互到达。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=105;
int d[N*N*N],temp[N*N*N],ans;
void mergesort(int left,int right)
{
int i,j,k;
int mid=(left+right)/2,g=0;
if(left<mid)
mergesort(left,mid);
if(mid+1<right)
mergesort(mid+1,right);
for(i=left,j=mid+1,k=left;k<=right;k++)
{
if(i>mid)
temp[k]=d[j++];
else if(j>right)
temp[k]=d[i++],ans=(ans+g)%2;
else if(d[j]<d[i])
temp[k]=d[j++],g++;
else 
temp[k]=d[i++],ans=(ans+g)%2;
}
for(k=left;k<=right;k++)
d[k]=temp[k];
}
int main()
{
int t,m,a;
int zero_x,zero_z;
scanf("%d",&t);
while(t--)
{
int i,j=0;
scanf("%d",&m);
for(i=0;i<m*m*m;i++)
{
scanf("%d",&a);
if(a!=0)
d[j++]=a;
else if(a==0)
{
zero_z=i/(m*m);
zero_x=i%(m*m)/m;
}
}
ans=0;
mergesort(0,m*m*m-2);

ans=(ans+(m*m-1)*(m-1-zero_z)+(m-1)*(m-1-zero_x))%2;
if(ans%2==0)
printf("Puzzle can be solved.\n");
else
printf("Puzzle is unsolvable.\n");
}
return 0;
}
```