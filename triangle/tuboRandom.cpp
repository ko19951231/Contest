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
    freopen("test.txt", "w", stdout);
    Polygon poly;
    int n=10;
    //scanf("%d", &n);
    printf("%d\n", n);
    vector<int> ang;
    vector<double> angle;
    vector<int> dy;
    double all=0;
    for(int i=0;i<n;i++){
        int rnd=rand()%16+10;
        all+=rnd;
        ang.push_back(rnd);
        rnd=rand()%16+10;
        dy.push_back(rnd);
    }
    int left=0, right=0;
    double rightAll=0, leftAll=0;
    for(int i=0;i<n;i++){
        double ag=ang[i]*2*acos(-1)/all;
        if(angle.size()>0) ag+=angle[angle.size()-1];
        if(i<5||i>=n-5) dy[i]=1;
        if(ag<acos(-1)){
            right++;
            rightAll+=dy[i];
        }
        else{
            dy[right]=1;
            left++;
            if(i<n-1) leftAll+=dy[i];
        }
        angle.push_back(ag);
    }
    double leftMost=0, rightMost=0;
    double curX=0;
    double curY=-9999999;
    double dlen=9999999*2/rightAll;
    for(int i=0;i<right;i++){
        //printf("angle %f len %f\n", angle[i], len);
        double len=dlen*dy[i];
        curY+=len;
        curX+=len/tan(angle[i]);
        if(curX>rightMost) rightMost=curX;
        if(curX<leftMost) leftMost=curX;
        poly.v.push_back(Point(curX, curY));
    }
    dlen=(curY+9999999)/leftAll;
    for(int i=right;i<right+left-1;i++){
        //printf("angle %f len %f\n", angle[i], len);
        double len=dlen*dy[i];
        curY-=len;
        curX-=len/tan(angle[i]);
        if(curX>rightMost) rightMost=curX;
        if(curX<leftMost) leftMost=curX;
        poly.v.push_back(Point(curX, curY));
    }
    poly.v.push_back(Point(0, -9999999));
    double dx=max(-leftMost, rightMost);
    dx/=9999999;
    for(int i=0;i<n;i++){
        printf("%f %f\n", poly.v[i].x/dx, poly.v[i].y);
    }
}