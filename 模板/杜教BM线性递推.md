##杜教BM线性递推
原理线性代数
解决的问题：
对于递推式类似  $$ dp[i]=\sum_{j=i-k}^{i-1}{a[j]*dp[j]} $$
的问题
具体使用方法是将前面2-3倍k项先推入，然后调用就行。事实上求第n项时参数为**n-1**，但是板子中的题第一项是a[0]所以参数使用了n。
```c++
#include <bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
using namespace std;
typedef long long int LL;
typedef long long int ll;
typedef vector<ll> VI;
typedef pair<ll,ll> PII;
const ll N=5000,M=1000+7;
const ll mod=1e9+7;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
namespace linear_seq{
    const int N=10010;
    ll res[N],base[N],_c[N],_md[N];
    vector<ll> Md;
    void mul(ll *a,ll *b,int k)
    {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (int i=k+k-1;i>=k;i--) if (_c[i])
            rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b)
    {
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--)
        {
            mul(res,res,k);
            if ((n>>p)&1)
            {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s)) {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a,ll n){
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
};

ll qpow(ll x,ll n) {
    ll res=1;
    for(; n; x=x*x%mod,n>>=1)
        if(n&1)
            res=res*x%mod;
    return res;
}

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


LL a[N];
int main(){
    LL T,k,n;
    cin>>T;
    while(T--){
        scanf("%lld%lld",&k,&n);
        if(n==-1){
            cout<<((2LL*inv(k+1))%mod)<<endl;
            continue;
        }
        a[0]=1;
        LL iik=inv(k)%mod;
        a[1]=iik;
        for(LL i=2;i<3*k;i++){
            a[i]=0;
            for(LL j=max(0LL,i-k);j<i;j++){
                a[i]=a[i]+a[j]*iik%mod;
                a[i]%=mod;
            }
        }
        vector<LL> v;
        for(LL i=0;i<3*k;i++)v.push_back(a[i]);
        cout<<linear_seq::gao(v,n)%mod<<endl;
    }
    return 0;
}




```