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

```cpp
#当模不是素数的时候
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <bitset>
#include <cmath>
#include <cctype>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef vector<long long> VI;
typedef unsigned long long ull;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const ll mod=1e9;
#define FOR(i,a,b) for(int i(a);i<=(b);++i)
#define FOL(i,a,b) for(int i(a);i>=(b);--i)
#define SZ(x) ((long long)(x).size())
#define REW(a,b) memset(a,b,sizeof(a))
#define inf int(0x3f3f3f3f)
#define si(a) scanf("%d",&a)
#define sl(a) scanf("%I64d",&a)
#define sd(a) scanf("%lf",&a)
#define ss(a) scanf("%s",a)
#define pb push_back
#define eps 1e-6
#define lc d<<1
#define rc d<<1|1
#define Pll pair<ll,ll>
#define P pair<int,int>
#define pi acos(-1)
ll powmod(ll a,ll b)
{
    ll res=1ll;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
namespace linear_seq {
    const int N=10010;
    using int64 = long long;
    using vec = std::vector<int64>;
    ll res[N],base[N],_c[N],_md[N];
    vector<int> Md;
    void mul(ll *a,ll *b,int k) {
        FOR(i,0,k+k-1) _c[i]=0;
        FOR(i,0,k-1) if (a[i]) FOR(j,0,k-1) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (int i=k+k-1;i>=k;i--) if (_c[i])
            FOR(j,0,SZ(Md)-1) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        FOR(i,0,k-1) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b) { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
//        printf("%d\n",SZ(b));
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        FOR(i,0,k-1) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        FOR(i,0,k-1) if (_md[i]!=0) Md.push_back(i);
        FOR(i,0,k-1) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                FOR(j,0,SZ(Md)-1) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        FOR(i,0,k-1) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        FOR(n,0,SZ(s)-1) {
            ll d=0;
            FOR(i,0,L) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                FOR(i,0,SZ(B)-1) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                FOR(i,0,SZ(B)-1) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    static void extand(vec &a, size_t d, int64 value = 0) {
        if (d <= a.size()) return;
        a.resize(d, value);
    }
    static void exgcd(int64 a, int64 b, int64 &g, int64 &x, int64 &y) {
        if (!b) x = 1, y = 0, g = a;
        else {
            exgcd(b, a % b, g, y, x);
            y -= x * (a / b);
        }
    }
    static int64 crt(const vec &c, const vec &m) {
        int n = c.size();
        int64 M = 1, ans = 0;
        for (int i = 0; i < n; ++i) M *= m[i];
        for (int i = 0; i < n; ++i) {
            int64 x, y, g, tm = M / m[i];
            exgcd(tm, m[i], g, x, y);
            ans = (ans + tm * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static vec ReedsSloane(const vec &s, int64 mod) {
        auto inverse = [](int64 a, int64 m) {
            int64 d, x, y;
            exgcd(a, m, d, x, y);
            return d == 1 ? (x % m + m) % m : -1;
        };
        auto L = [](const vec &a, const vec &b) {
            int da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -1000;
            int db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -1000;
            return std::max(da, db + 1);
        };
        auto prime_power = [&](const vec &s, int64 mod, int64 p, int64 e) {
            // linear feedback shift register mod p^e, p is prime
            std::vector<vec> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            vec t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
            pw[0] = 1;
            for (int i = pw[0] = 1; i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (int64 i = 0; i < e; ++i) {
                a[i] = {pw[i]}, an[i] = {pw[i]};
                b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
                t[i] = s[0] * pw[i] % mod;
                if (t[i] == 0) {
                    t[i] = 1, u[i] = e;
                } else {
                    for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
                }
            }
            for (size_t k = 1; k < s.size(); ++k) {
                for (int g = 0; g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e - 1 - u[g]];
                        bo[g] = b[e - 1 - u[g]];
                        to[g] = t[e - 1 - u[g]];
                        uo[g] = u[e - 1 - u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an, b = bn;
                for (int o = 0; o < e; ++o) {
                    int64 d = 0;
                    for (size_t i = 0; i < a[o].size() && i <= k; ++i) {
                        d = (d + a[o][i] * s[k - i]) % mod;
                    }
                    if (d == 0) {
                        t[o] = 1, u[o] = e;
                    } else {
                        for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
                        int g = e - 1 - u[o];
                        if (L(a[g], b[g]) == 0) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        } else {
                            int64 coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                            int m = k - r[g];
                            extand(an[o], ao[g].size() + m);
                            extand(bn[o], bo[g].size() + m);
                            for (size_t i = 0; i < ao[g].size(); ++i) {
                                an[o][i + m] -= coef * ao[g][i] % mod;
                                if (an[o][i + m] < 0) an[o][i + m] += mod;
                            }
                            while (an[o].size() && an[o].back() == 0) an[o].pop_back();
                            for (size_t i = 0; i < bo[g].size(); ++i) {
                                bn[o][i + m] -= coef * bo[g][i] % mod;
                                if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
                            }
                            while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
                        }
                    }
                }
            }
            return std::make_pair(an[0], bn[0]);
        };
        std::vector<std::tuple<int64, int64, int>> fac;
        for (int64 i = 2; i * i <= mod; ++i)
            if (mod % i == 0) {
                int64 cnt = 0, pw = 1;
                while (mod % i == 0) mod /= i, ++cnt, pw *= i;
                fac.emplace_back(pw, i, cnt);
            }
        if (mod > 1) fac.emplace_back(mod, mod, 1);
        std::vector<vec> as;
        size_t n = 0;
        for (auto &&x: fac) {
            int64 mod, p, e;
            vec a, b;
            std::tie(mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) x %= mod;
            std::tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = std::max(n, a.size());
        }
        vec a(n), c(as.size()), m(as.size());
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < as.size(); ++j) {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = crt(c, m);
        }
        return a;
    }
    ll gao(VI a,ll n,ll mod,bool prime=true) {
        VI c;
        if(prime) c=BM(a);        //素数使用BM
        else c=ReedsSloane(a,mod);   //合数使用ReedsSloane
        c.erase(c.begin());
        FOR(i,0,SZ(c)-1) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
};
 
ll qpow(ll a,ll b, ll mod)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
 
vector<ll>tmp;
int n, m;
 
int main()
{
    scanf("%d%d", &n,&m);
    ll a = 0, b = 1, c, sum = 1;
    tmp.push_back(0);tmp.push_back(1);
    for(int i = 2;i <= 2*57;i++)
    {
        c = (a + b) % mod;
        a = b;
        b = c;
 
        sum = (sum + qpow(c, m, mod)) % mod;
        tmp.push_back(sum);
 
        //printf("%lld\n", c);
    }
 
    //for(int i = 0;i <= 2*m;i++)  printf("%lld\n", tmp[i]);
   printf("%lld\n",  linear_seq::gao(tmp, n, mod, false));
 
}
```
