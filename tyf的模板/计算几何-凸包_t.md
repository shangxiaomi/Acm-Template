#Graham扫描法
首先确定最下面（y值最小）的点一定是凸包上的点
把它设为极点，将其他点按极角大小排序
极角最大和极角最小一定在凸包上
这三个点再凸包上一定是连一起的。
然后按照一直向左走或者一直向右走构造即可


```c++
#include<bits/stdc++.h>
using namespace std;

struct point{
    double x,y;
    point friend operator -(point a,point b)
    {return {a.x-b.x,a.y-b.y};}
}p[105],s[105];
double dis(point a,point b)
{
    point c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}
double X(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
int cmp(point a,point b)
{
    double x=X(a-p[1],b-p[1]);
    
    if(x>0) return 1;
    if(x==0&&dis(a,p[1])<dis(b,p[1])) return 1;
    return 0;
}
double multi(point p1,point p2,point p3)
{
    return X(p2-p1,p3-p1);
}
int main()
{
    int N;
    while(scanf("%d",&N),N)
    {
        for(int i=1;i<=N;i++) cin>>p[i].x>>p[i].y;
        int k=1;
        for(int i=2;i<=N;i++)
        if(p[i].y<p[k].y||(p[i].y==p[k].y&&p[i].x<p[k].x))k=i;
        swap(p[1],p[k]);
        sort(p+2,p+1+N,cmp);
        s[1]=p[1];
        s[2]=p[2];
        int t=2;
        for(int i=3;i<=N;i++)
        {
            while(t>=2&&multi(s[t-1],s[t],p[i])<=0) t--;
            s[++t]=p[i];
        }
        double sum=0;
        //求凸包周长
        for(int i=1;i<t;i++)
        {
            sum+=dis(s[i],s[i+1]);
        }
        printf("%.2lf\n",sum+dis(s[1],s[t]));
    }
    return 0;
}
```


#安德鲁算法

按x排序，找到最左点作为起点，
使用栈分别顺时针逆时针走半圈，就是分别的上下两部分凸包。
```C++
#include <bits/stdc++.h>
using namespace std;
#define eps 0.000001
class Point
{
    public:
        double x, y;
        Point(double x = 0, double y = 0):x(x),y(y) {}
        Point operator + (Point a)
        {
            return Point(a.x + x,a.y + y);
        }
        Point operator - (Point a)
        {
            return Point(x - a.x, y - a.y);
        }
        bool operator < (const Point &a) const
        {
            if(x ==a.x)
                return y < a.y;
            return x < a.x;
        }
};

typedef Point Vector;

double cross(Vector a,Vector b)
{
    return a.x*b.y - a.y*b.x;
}

double dot(Vector a,Vector b)
{
    return a.x* b.x + a.y*b.y;
}

bool isclock(Point p0,Point p1,Point p2)
{
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if(cross(a,b) < -eps) return true;
    return false;
}

double getDistance(Point a,Point b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y - b.y,2));
}

typedef vector<Point> Polygon;
Polygon andrewScan(Polygon s)
{
    Polygon u,l;
    if(s.size()<3) return s;
    sort(s.begin(),s.end());
    u.push_back(s[0]);
    u.push_back(s[1]);
    l.push_back(s[s.size() - 1]);
    l.push_back(s[s.size() - 2]);
    printf("l[n-2]:%.2f %.2f\nl[n-1]:%.2f %.2f\n",l[l.size()-2].x,l[l.size()-2].y,l[l.size()-1].x,l[l.size()-1].y);
    for(int i = 2 ; i < s.size() ; i++)
    {
        for(int n = u.size() ; n >= 2 && isclock(u[n-2],u[n-1],s[i])!=true; n--)
        {
            cout<<u[n-2].x<<' '<<u[n-2].y<<'\n'<<u[n-1].x<<u[n-1].y<<endl;
            u.pop_back();
        }
        u.push_back(s[i]);
    }
    for(int i = s.size() - 3 ; i >= 0 ; i--)
    {
        cout<<i<<endl;
        for(int n = l.size() ; n >=2 && isclock(l[n-2],l[n-1],s[i])!=true ; n--)
        {
            cout<<i<<endl;
            printf("del:\nl[n-2]:%.2f %.2f\nl[n-1]:%.2f %.2f\n",l[n-2].x,l[n-2].y,l[n-1].x,l[n-1].y);

            l.pop_back();
        }

        l.push_back(s[i]);
    }
//    for(auto &p : u) printf("%.2f %.2f\n",p.x,p.y);
//    printf("yes\n");
//    for(auto &p : l) printf("%.2f %.2f\n",p.x,p.y);

    for(int i = 1 ; i < u.size() - 1 ; i++) l.push_back(u[i]);
    return l;
}

```

#判断两个凸包是否香蕉
首先思考，如果有一个凸包A的一部分在另一个凸包B内
那么A中肯定有一个顶点在凸包B内
```C++
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;
const int N=1e5;

int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    return x>0?1:-1;
}
struct point
{
    double x,y;
    point() {}
    point(double x,double y):x(x),y(y){}
    point operator + (const point &a) const
    {
        return point(x+a.x,y+a.y);
    }
    point operator - (const point &a) const
    {
        return point(x-a.x,y-a.y);
    }
    void in(int xx,int yy)
    {
         x=xx;y=yy;
    }
    bool operator < (const point &a) const
    {
        return x+eps<a.x||(!dcmp(x-a.x)&&y<a.y);
    }
    bool operator == (const point &a) const
    {
        return x==a.x&&y==a.y;
    }
};
 point p1[510],p2[510],ch1[510],ch2[510];
double dot(point a,point b)
{
    return a.x*b.x+a.y*b.y;
}
double cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
bool SegmentProperIntersectiom(point a1,point a2,point b1,point b2)
{
    if(a1==a2&&b1==b2){
        if(a1==b1)return true;
        else return false;
    }
    if(a1==a2||b1==b2)return false;
    double c1=cross(a2-a1,b1-a1),c2=cross(a2-a1,b2-a1),
           c3=cross(b2-b1,a1-b1),c4=cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<=0&&dcmp(c3)*dcmp(c4)<=0;
}
bool OnSegment(point p,point a1,point a2)
{
    return dcmp(cross(a1-p,a2-p))==0&&dcmp(dot(a1-p,a2-p))<0;
}
int isPointInpolygon(point p,point *ch,int n)
{
    int wn=0;
    for(int i=0;i<n;i++)
    {
        if(OnSegment(p,ch[i],ch[(i+1)%n])) return 1;
        int k=dcmp(cross(ch[(i+1)%n]-ch[i],p-ch[i]));
        int d1=dcmp(ch[i].y-p.y);
        int d2=dcmp(ch[(i+1)%n].y-p.y);
        if(k>0&&d1<=0&&d2>0) wn++;
        if(k<0&&d2<=0&&d1>0) wn--;
    }
    if(wn!=0) return 1;
    return 0;
}
int ConvexHull(point *p,int n,point *ch)
{
    sort(p,p+n);
    int m=0;
    for(int i=0;i<n;i++)
    {
        while(m>1&&cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--)
    {
        while(m>k&&cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++]=p[i];
    }
    if(n>1) m--;
    return m;
}
int main()
{
    int T;
    scanf("%d",&T);
    int cnt1=0,cnt2=0;
    while(T--)
    {
        cnt1=0,cnt2=0;
        memset(p1,0,sizeof p1);
        memset(p2,0,sizeof p2);
        memset(ch1,0,sizeof ch1);
        memset(ch2,0,sizeof ch2);
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            if(c==1)p1[cnt1++].in(a,b);
            else p2[cnt2++].in(a,b);
        }
        if(cnt1==0&&cnt2==0) break;
        int n1=ConvexHull(p1,cnt1,ch1);
        int n2=ConvexHull(p2,cnt2,ch2);
        int flag=1;
        for(int i=0;i<n1;i++)
            if(isPointInpolygon(ch1[i],ch2,n2)){
                flag=0;
                break;
            }
        for(int i=0;i<n2;i++)
            if(isPointInpolygon(ch2[i],ch1,n1)){
            flag=0;
            break;
            }
        if(flag)
            cout<<"Successful!"<<endl;
        else
            cout<<"Infinite loop!"<<endl;
    }
    return 0;
}
```