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
    int b=1;
    int c=2;
    double fakeMax=Triangle(poly.v[0], poly.v[1], poly.v[2]).area();
    for(int idx=0;idx<poly.v.size();idx++){
        b=(idx+1)%n;
        c=(idx+2)%n;
        while(Triangle(poly.v[idx], poly.v[b], poly.v[(c+1)%n]).area()>fakeMax){
            fakeMax=Triangle(poly.v[idx], poly.v[b], poly.v[(c+1)%n]).area();
            c=(c+1)%n;
        }
        while(Triangle(poly.v[idx], poly.v[(b+1)%n], poly.v[c]).area()>fakeMax){
            fakeMax=Triangle(poly.v[idx], poly.v[(b+1)%n], poly.v[c]).area();
            b=(b+1)%n;
        }
    }
    printf("%.17f\n", fakeMax);
}