#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
int n,maxn;
namespace BIT{
    int bit[200100];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int pos,int val){
        while(pos<=maxn){
            bit[pos]+=val;
            pos+=lowbit(pos);
        }
    }
    int query(int pos){
        int ans=0;
        while(pos){
            ans+=bit[pos];
            pos-=lowbit(pos);
        }
        return ans;
    }
    void clear(int pos){
        while(pos<=maxn){
            if(bit[pos])
                bit[pos]=0;
            else
                break;
            pos+=lowbit(pos);
        }
    }
}
struct Num{
    int a,b,c,val;
    bool operator == (const Num &bx) const{
        if(a==bx.a&&b==bx.b&&c==bx.c)
            return true;
        return false;
    }
    bool operator < (const Num &bx) const{
        if(a<bx.a)
            return true;
        else if(a==bx.a&&b<bx.b)
            return true;
        else if(a==bx.a&&b==bx.b&&c<bx.c)
            return true;
        else return false;
    }
}a[100100],num[100100];
int ans[100100],d[100100];
int cntnum=0,qid,aid;
struct Query{
    int posx,valy,val,aid;
}query[100100<<1];
Query tmp[100100<<1];
void cdq(int L,int R){
    // printf("%d %d\n",L,R);
    if(R<=L+1)
        return;
    int mid=(L+R)>>1;
    cdq(L,mid);
    cdq(mid,R);
    int l=L,r=mid,tot=0;
    while(l<mid&&r<R){
        if(query[l].posx<=query[r].posx){
            BIT::add(query[l].valy,query[l].val);
            tmp[++tot]=query[l++];  
        }
        else{
            ans[query[r].aid]+=BIT::query(query[r].valy);
            tmp[++tot]=query[r++];
        }
    }
    while(l<mid)
        tmp[++tot]=query[l++];
    while(r<R){
        ans[query[r].aid]+=BIT::query(query[r].valy);    
        tmp[++tot]=query[r++];
    }
    for(int i=1;i<=tot;i++){
        BIT::clear(tmp[i].valy);
        query[i+L-1]=tmp[i];
    }
}
int main(){
    scanf("%d %d",&n,&maxn);
    for(int i=1;i<=n;i++)
        scanf("%d %d %d",&a[i].a,&a[i].b,&a[i].c),a[i].val=1;
    sort(a+1,a+n+1);
    num[++cntnum]=a[1];
    for(int i=1;i<=n-1;i++){
        if(a[i]==a[i+1])
            num[cntnum].val++;
        else
            num[++cntnum]=a[i+1];
    }
    for(int i=1;i<=cntnum;i++){
        query[++qid].posx=num[i].b;
        query[qid].aid=++aid;
        query[qid].valy=num[i].c;
        query[qid].val=num[i].val;
    }
    
    // printf("ok\n");
    cdq(1,qid+1);
    cout<<"SUM "<<qid<<"!!!\n";
    for(int i=1;i<=qid;i++)cout<<ans[i]<<' ';
    cout<<endl;
    for(int i=1;i<=qid;i++){
        //cout<<ans[query[i].aid]+query[i].val-1<<" ";
        d[ans[query[i].aid]+query[i].val-1]+=query[i].val;
    }
    for(int i=0;i<=n-1;i++)
        printf("%d\n",d[i]);
       system("pause");
    return 0;
}