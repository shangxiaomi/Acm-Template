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
const int maxn = 10000;
const double pi = acos(-1.0);
int T,n,m;
struct L_B{
    long long basis[61],p[61];
    int cnt;
    L_B()
    {
        memset(basis,0,sizeof(basis));
        memset(p,0,sizeof(p));
        cnt=0;
    }
    void clear(){
        memset(basis,0,sizeof(basis));
        memset(p,0,sizeof(p));
        cnt=0;
    }
    bool insert(long long val)
    {
        for (int i=60;i>=0;i--)
            if (val&(1LL<<i))
            {
                if (!basis[i])
                {
                    basis[i]=val;
                    break;
                }
                val^=basis[i];
            }
        return val>0;
    }
    long long query_max()
    {
        long long ret=0;
        for (int i=60;i>=0;i--)
            if ((ret^basis[i])>ret)
                ret^=basis[i];
        return ret;
    }
    long long query_min()
    {
        for (int i=0;i<=60;i++)
            if (basis[i])
                return basis[i];
        return 0;
    }
    void rebuild()
    {
        for (int i=60;i>=0;i--)
            for (int j=i-1;j>=0;j--)
                if (basis[i]&(1LL<<j))
                    basis[i]^=basis[j];
        for (int i=0;i<=60;i++)
            if (basis[i])
                p[cnt++]=d[i];
    }
    long long kthquery(long long k)//先调用rebuild
    {
        int ret=0;
        if (k>=(1LL<<cnt))
            return -1;
        for (int i=60;i>=0;i--)
            if (k&(1LL<<i))
                ret^=p[i];
        return ret;
    }
};
L_B merge(const L_B &n1,const L_B &n2)
{
    L_B ret=n1;
    for (int i=60;i>=0;i--)
        if (n2.basis[i])
            ret.insert(n1.basis[i]);
    return ret;
}
L_B Merge(L_B A,L_B B) {
	L_B All , C , D;
	All.clear();
	C.clear();
	D.clear();
	for (int i = 60;i >= 0;i--) {
		All.basis[i] = A.basis[i];
		D.basis[i] = 1ll << i;
	}
	for (int i = 60; i >= 0; i--) {
		if (B.basis[i]) {
			ll v = B.basis[i] , k = 0;
			bool can = true;
			for (int j = 60; j >= 0; j--) {
				if (v & (1ll << j)) {
					if (All.basis[j]) {
						v ^= All.basis[j];
						k ^= D.basis[j];
					} else {
						can = false;
						All.basis[j] = v;
						D.basis[j] = k;
						break;
					}
				}
			}

			if (can) {
				ll v = 0;
				for (int j = 60; j >= 0; j--) {
					if (k & (1ll << j)) {
						v ^= A.basis[j];
					}
				}
				C.insert(v);
			}
		}
	}
	C.build();
	return C;
}

int main()
{
    system("pause");
    return 0;
}