#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
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
    //freopen("input01.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
	double theta=2*acos(-1)/n;
	printf("theta=%f\n", theta);
	double len=2*1e7*sin(theta/2);
    Polygon poly;
	poly.v.push_back(Point(-len/2, 1e7*cos(theta/2)));
	poly.v.push_back(Point(len/2, 1e7*cos(theta/2)));
    double x, y;
    int a, b;
    for(int i=2;i<n;i++){
        a=rand()%2000;
        b=rand()%10000;
        x=a*10000+b-1e7;
        a=rand()%2000;
        b=rand()%10000;
        y=a*10000+b-1e7;
        int cnt=poly.v.size();
        if(poly.v.size()>=2){
            while(Line(poly.v[cnt-1], poly.v[cnt-2]).cross(Line(poly.v[cnt-1], Point(x, y)))<0||Line(poly.v[0], Point(x, y)).cross(Line(poly.v[0], poly.v[1]))<0||Line(Point(x, y), poly.v[cnt-1]).cross(Line(Point(x, y), poly.v[0]))<0||Line(poly.v[cnt-1], poly.v[cnt-2]).dot(Line(poly.v[cnt-1], Point(x, y)))/(Line(poly.v[cnt-1], poly.v[cnt-2]).length()*Line(poly.v[cnt-1], Point(x, y)).length())>cos(acos(-1)-theta)||Line(poly.v[cnt-1], Point(x, y)).length()>len){
                a=rand()%2000;
                b=rand()%10000;
                x=a*10000+b-1e7;
                a=rand()%2000;
                b=rand()%10000;
                y=a*10000+b-1e7;
            }
        }
        printf("%f %f\n", x, y);
        poly.v.push_back(Point(x, y));
    }
}