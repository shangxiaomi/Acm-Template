# [C 数学](https://ac.nowcoder.com/acm/contest/881/C)
## 题解
拉格朗日乘子法的强对偶转换不会，采用了讨论区的方法
[这里是连接](https://blog.nowcoder.net/n/1539da6d6d6e47a6998b5c6f5bba2167)
将目标式乘上 $m^2$
$$||A-p||^2_2= \sum_{i=1}^n(a_i/m-p_i)^2 $$
目标式变为
$$\frac{1}{m^2}\sum_{i=1}^n(a_i-m*p_i)^2 $$
那么我们令
$$p_i'=m*p_i$$
那么目标式变为
$$\frac{1}{m^2}\sum_{i=1}^n(a_i-p_i')^2 $$
约束式变为
 $$\sum_{i=1}^n(p_i')=m$$
 由于$p_i'$一定为正，所以每个$p_i'$对于$(a_i-p_i')^2$的贡献这种模型可以被抽象为
 ![mHEOOJ.png](https://s2.ax1x.com/2019/08/28/mHEOOJ.png)
 将所有ai从大到小排一排，从高的开始向下推平。这个好像比较难证明，但是确实是正确的结论。
 然后分数类计算就行。
 ```Cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef long long int ll;
const int N=10000+7,M=1000+7;

LL gcd(LL x,LL y){
        return (x%y==0?y:gcd(y,x%y));
    }
LL lcm(LL x,LL y){
        return x/gcd(x,y)*y;
}
struct Fen{
    LL a,b; //分子 分母
    Fen(){
        a=0;b=1;
    }
    Fen(LL a,LL b){
        *this=make_pair(a,b);
    }

    Fen(LL num){
        *this=num;
    }
    Fen(pair<LL,LL> x){
        *this=x;
    }
    Fen (const Fen &x){
        a=x.a;
        b=x.b;
        check();
    }
    double value(){
        return (double)a/b;
    }
    int check(){//约分
        int p=gcd(a,b);
        a/=p;
        b/=p;
        return 0;
    }
    Fen operator = (LL num){
        a=num;
        b=1;
        return *this;
    }
    Fen operator = (pair<LL,LL> x){
        a=x.first;
        b=x.second;
        check();
        return *this;
    }
    Fen operator = (const Fen &x){
        a=x.a;
        b=x.b;
        check();
        return *this;
    }
    Fen operator +(const Fen &x) const{
        Fen y=*this,z=x;
        LL p=lcm(y.b,z.b);
        y.a=y.a*(p/y.b);
        y.b=p;
        z.a=z.a*(p/z.b);
        z.b=p;
        Fen kl=make_pair(y.a+z.a,p);
        return kl;
    }
    Fen operator -(const Fen &x) const{
        Fen y=*this,z=x;
        LL p=lcm(y.b,z.b);
        y.a=y.a*(p/y.b);
        y.b=p;
        z.a=z.a*(p/z.b);
        z.b=p;
        Fen kl=make_pair(y.a-z.a,p);
        return kl;
    }
    Fen operator *(const Fen &x) const{
        Fen z=make_pair(a*x.a,b*x.b);
        z.check();
        return z;
    }
    Fen operator /(const Fen &x) const{
        Fen z=make_pair(x.b,x.a);
        z*=*this;
        return z;
    }
    bool operator <(const Fen &x) const{
        Fen y=*this;
        Fen z=x;
        LL p=lcm(y.b,z.b);
        y.a=y.a*(p/y.b);
        y.b=p;
        z.a=z.a*(p/z.b);
        z.b=p;
        return y.a<z.a;
    }
    bool operator >(const Fen &x) const{
        return x<*this;
    }
    bool operator <=(const Fen &x){
        return !(x<*this);
    }
    bool operator >=(const Fen &x){
        return !(*this<x);
    }
    bool operator !=(const Fen &x){
        return x<*this || *this<x;
    }
    bool operator ==(const Fen &x){
        return !(x<*this) && !(*this<x);
    }
    Fen operator +=(const Fen &x){
        *this=*this+x;
        return *this;
    }
    Fen operator -=(const Fen &x){
        *this=*this-x;
        return *this;
    }
    Fen operator *=(const Fen &x){
        *this=*this*x;
        return *this;
    }
    Fen operator /=(const Fen &x){
        *this=*this/x;
        return *this;
    }
    bool is_right(){//确认分母不为0
        if (b==0) return false;
        else return true;
    }
    Fen clear(){//分数清零
        a=0;
        b=1;
        return *this;
    }
    Fen be_right(){
        if (!is_right()) clear();
        return *this;
    }
};
istream& operator >> (istream &in,Fen &x)//重载IO运算
{
    LL l,p;
    in>>l>>p;
    pair<LL,LL> pl=make_pair(l,p);
    x=pl;
    x.be_right();
    return in;
}
ostream& operator << (ostream &out,const Fen &x){
    if(x.b!=1)
        out<<x.a<<'/'<<x.b;
    else out<<x.a;
    return out;
}



int a[N];
int main(){
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=0;i<n;i++)scanf("%d",&a[i]);
        sort(a,a+n);
        int K=m,last=a[n-1];
        Fen ans;
        int i;
        for( i=n-1;i>=1;i--){
            int u=n-i;
            if(u*(last-a[i-1])>=K){
                    Fen buf=Fen(K,u);
                    buf=Fen(last,1)-buf;
                ans+=buf*buf*Fen(u,1);
                break;
            }
            K-=u*(last-a[i-1]);
            last=a[i-1];
        }
        if(K>0&&i==0){
            i=-1;
            ans+=Fen(K-a[0]*n,n)*Fen(K-a[0]*n,n)*Fen(n);
        }
        i--;
        for(i;i>=0;i--)ans+=Fen(a[i]*a[i],1);
        ans=ans/Fen(m*m);
        ans.check();
        cout<<ans<<endl;
    }
    return 0;
}
 ```