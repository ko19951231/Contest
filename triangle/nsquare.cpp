#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>
using namespace std;

class Point
{
public:
	double x;
	double y;
	Point(){}
	Point(const Point &P){
		x=P.x;
		y=P.y;
	}
	Point(double a, double b)
	{
		x=a;
		y=b;
	}
	Point operator*(const double coe)const
	{
		Point P;
		P.x=x*coe;
		P.y=y*coe;
		return P;
	}
	Point operator-(const Point P)const
	{
		Point result;
		result.x=x-P.x;
		result.y=y-P.y;
		return result;
	}
	Point operator+(const Point P)const
	{
		Point result;
		result.x=x+P.x;
		result.y=y+P.y;
		return result;
	}
};

class Line
{
public:
	Point p1;
	Point p2;
	Line(){}
	Line(Point a, Point b){
		p1=a;
		p2=b;
	}
	Line(const Line &L){
		p1=L.p1;
		p2=L.p2;
	}
	double cross(const Line &L)const{
		return (p2.x-p1.x)*(L.p2.y-L.p1.y)-(p2.y-p1.y)*(L.p2.x-L.p1.x);
	}
    double dot(const Line &L)const{
        return (p2.x-p1.x)*(L.p2.x-L.p1.x)+(p2.y-p1.y)*(L.p2.y-L.p1.y);
    }
	double length()
	{
		return(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
	}
};

class Polygon
{
public:
	vector<Point> v;
	Polygon(){
		v.clear();
	}
	double area(){//area
		double a=0;
		for(int i=1;i<v.size()-1;i++){
			Line L1(v[0], v[i]);
			Line L2(v[0], v[i+1]);
			a+=L1.cross(L2);
		}
		if(a<0) return (-a)/2;
		else return a/2;
	}
};

class Triangle
{
public:
	Point a;
	Point b;
	Point c;
	Triangle(){}
	Triangle(Point A, Point B, Point C){
		a=A; b=B; c=C;
	}
	double area(){
		Line L1(a, b);
		Line L2(a, c);
		double ans=L1.cross(L2);
		if(ans<0) ans=-ans;
		return ans/2;
	}
};

pair<int, int> maxTri(Polygon curPoly, int idx)
{
    //printf("make query %d\n", idx);
	int n=curPoly.v.size();
    int ret1, ret2;
    int a=(idx+1)%n;
    int b=(idx+2)%n;
    double globalMax=0;
	int cnt=0;
    while(a!=idx){
        double localMax=0;
        bool change=1;
        while(change){
            change=0;
            for(int tmp=b;tmp%n!=idx;tmp++)
            {
                tmp%=n;
                //printf("tmpb=%d\n", tmp);
				cnt++;
                if(Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[tmp]).area()>localMax){
                    if(tmp!=b) change=1;
                    b=tmp;
                    localMax=Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[tmp]).area();
                }
				else break;
            }
            if(!change) break;
            change=0;
            //printf("####################################################B=%d\n", b);
            for(int tmp=a;tmp%n!=b;tmp++){
                tmp%=n;
                //printf("tmpa=%d\n", tmp);
				cnt++;
                if(Triangle(curPoly.v[idx], curPoly.v[tmp], curPoly.v[b]).area()>localMax){
                    if(tmp!=a) change=1;
                    a=tmp;
                    localMax=Triangle(curPoly.v[idx], curPoly.v[tmp], curPoly.v[b]).area();
                }
				else break;
            }
            //printf("####################################################A=%d idx=%d\n", a, idx);
        }
        //printf("2 stable %d %d\n", a, b);
        if(localMax>globalMax){
            globalMax=localMax;
            ret1=a;
            ret2=b;
        }
        a=(a+1)%n;
    }
	//printf("cnt %d return %d %d\n",cnt, ret1, ret2);
    return make_pair(ret1, ret2);
}

int main()
{
    int n;
    scanf("%d", &n);
    Polygon poly;
    Point p;
    for(int i=0;i<n;i++){
        scanf("%lf %lf", &p.x, &p.y);
        poly.v.push_back(p);
    }
    int idx;
    double maxmax=0;
    Triangle large;
    int ans[5];
    for(idx=0;idx<poly.v.size();idx++){
        if(idx%100==0) printf("%d\n", idx);
        pair<int, int> maxtri_ans=maxTri(poly, idx);
        if(Triangle(poly.v[idx], poly.v[maxtri_ans.first], poly.v[maxtri_ans.second]).area()>maxmax){
            maxmax=Triangle(poly.v[idx], poly.v[maxtri_ans.first], poly.v[maxtri_ans.second]).area();
            large=Triangle(poly.v[idx], poly.v[maxtri_ans.first], poly.v[maxtri_ans.second]);
            ans[0]=idx;
            ans[1]=maxtri_ans.first;
            ans[2]=maxtri_ans.second;
        }
    }
    printf("maxmax=%.17f\n", maxmax);
    printf("%f %f, %f %f, %f %f\n", large.a.x, large.a.y, large.b.x, large.b.y, large.c.x, large.c.y);
    printf("%d %d %d\n", ans[0], ans[1], ans[2]);
}