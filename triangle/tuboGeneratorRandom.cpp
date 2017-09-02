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
	Point intersection(const Line &L)const{//line intersection point
		Point result;
		if(cross(L)==0){
			result.x=-999999;
			result.y=-999999;
			return result;
		}
		result=p1+(p2-p1)*(Line(L.p1, p1).cross(L)/L.cross(*this));
		return result;
	}
	bool point_on_segment(const Point &P)const{//point on line, but on segment?
		if((P.x-p1.x)*(P.x-p2.x)<=1e-7&&(P.y-p1.y)*(P.y-p2.y)<=1e-7) return 1;
		return 0;
	}
	bool valid_intersection(const Line &L)const{//segment intersect?
		Point result;
		if(cross(L)==0){
			Line L2(p2, L.p1);
			if(cross(L2)==0&&(point_on_segment(L.p1)||point_on_segment(L.p2)||L.point_on_segment(p1)||L.point_on_segment(p2))) return 1;
			return 0;
		}
		result=intersection(L);
		if(point_on_segment(result)&&L.point_on_segment(result)) return 1;
		return 0;
	}
	Line perpendicular_bisector()const{//a perpendicular bisector line
		Point P1((p1.x+p2.x)/2, (p1.y+p2.y)/2);
		Point v(p2.y-p1.y, p1.x-p2.x);
		Point P2=P1+v;
		Line result(P1, P2);
		return result;
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
	Polygon HPits(Line &L){//half plane intersection //only keep the counterclockwise side's polygon
		Polygon q;
		for(int i=0;i<v.size();i++){
			Line L1(L.p1, v[i]);
			if(L.cross(L1)>=0) q.v.push_back(v[i]);
			Line L2(L.p1, v[(i+1)%v.size()]);
			if(L.cross(L1)*L.cross(L2)<0) q.v.push_back(L.intersection(Line(v[i], v[(i+1)%v.size()])));
		}
		return q;
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
	Point center(){//tircumcenter
		Line L1(a, b);
		Line L2(b, c);
		Line N1=L1.perpendicular_bisector();
		Line N2=L2.perpendicular_bisector();
		return N1.intersection(N2);
	}
	double area(){
		Line L1(a, b);
		Line L2(a, c);
		double ans=L1.cross(L2);
		if(ans<0) ans=-ans;
		return ans/2;
	}
	bool point_in_triangle(const Point &P)const{
		Line L1(P, a);
		Line L2(P, b);
		Line L3(P, c);
		if(L1.cross(L2)<=0&&L2.cross(L3)<=0&&L3.cross(L1)<=0) return 1;
		if(L1.cross(L2)>=0&&L2.cross(L3)>=0&&L3.cross(L1)>=0) return 1;
		return 0;
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