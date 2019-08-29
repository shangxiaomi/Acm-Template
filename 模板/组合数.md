```C++
#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef long long int ll;
const int mod=998244353;
const int N=1e7+987,MAXX=1e7+929;
long long fac[N],inv[N];
long long quickmod(long long a,long long b){
    long long ans=1;
    while(b){
        if(b%2==1)
            ans=ans*a%mod;
        a=a*a%mod;
        b=b/2;
    }
    return ans;
}
long long C(long long n,long long m){
    if(n<0||m<0) return 0;
    if(n<m)
        return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init(){
    fac[0]=1;
    for(int i=1;i<MAXX;i++)
        fac[i]=fac[i-1]*i%mod;
    inv[MAXX-1]=quickmod(fac[MAXX-1],mod-2);
    for(int i=MAXX-2;i>=0;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
}
/*求单个逆元
void exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0) {
        x=1; y=0; return;
    }
    exgcd(b,a%b,y,x);
    y-=(a/b)*x;
}

ll inv(ll a){
    ll x,y; exgcd(a,mod,x,y);
    return (x+mod)%mod;
}
*/
int main(){
    return 0;
}



```