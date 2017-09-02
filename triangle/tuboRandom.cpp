#include <vector>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>
#include <cstdio>
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
    Polygon poly;
    int n;
    scanf("%d", &n);
    vector<int> ang;
    vector<double> angle;
    double all=0;
    for(int i=0;i<n;i++){
        int rnd=rand()%5+1;
        all+=rnd;
        ang.push_back(rnd);
    }
    int qd4=0, qd1=0, qd2=0, qd3=0;
    for(int i=0;i<n;i++){
        double ag=ang[i]*2*acos(-1)/all;
        if(angle.size()>0) ag+=angle[angle.size()-1];
        if(ag<acos(-1)/2) qd4++;
        else if(ag<acos(-1)) qd1++;
        else if(ag<acos(-1)*3/2) qd2++;
        else qd3++;
        angle.push_back(ag);
    }
    double curX=0;
    double curY=-9999999;
    double len=9999999/qd4;
    printf("from leftdown to rightup\n");
    for(int i=0;i<qd4;i++){
        curX+=len;
        curY+=len*tan(angle[i]);
        printf("%f %f\n", curX, curY);
    }
    len=(9999999-curY)/qd1;
    puts("form rightdown to leftup\n");
    for(int i=qd4;i<qd4+qd1;i++){
        printf("anglei=%f tan=%f\n", angle[i], tan(angle[i]));
        curY+=len;
        curX+=len/tan(angle[i]);
        printf("%f %f\n", curX, curY);
    }
    len=(curX+9999999)/qd2;
    puts("from rightup to leftdown\n");
    for(int i=qd4+qd1;i<qd4+qd1+qd2;i++){
        curX-=len;
        curY-=len*tan(angle[i]);
        printf("%f %f\n", curX, curY);
    }
    len=(curY+99999990/qd3);
    puts("from leftup to rightdown\n");
    for(int i=qd4+qd1+qd2;i<qd4+qd1+qd2+qd3-1;i++){
        curY-=len;
        curX-=len/tan(angle[i]);
        printf("%f %f\n", curX, curY);
    }
    printf("%f %f\n", 0, -9999999);
}