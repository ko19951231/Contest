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
    int n=curPoly.v.size();
    int ret1=-1, ret2=-1;
    int a=(idx+1)%n;
    int b=(idx+2)%n;
    double globalMax=0;
	for(a=(idx+1)%n;a%n!=idx;a++){
		a=a%n;
		double localMax=Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[b]).area();
		while((b+1)%n!=idx&&Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[(b+1)%n]).area()>localMax){
			localMax=Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[(b+1)%n]).area();
			b=(b+1)%n;
		}
        if(localMax>globalMax){
			globalMax=localMax;
			ret1=a;
			ret2=b;
		}
	}
	if(ret1<0||ret2<0){
		for(int i=0;i<n;i++) printf("%d %f %f\n", i, curPoly.v[i].x, curPoly.v[i].y);
	}
    return make_pair(ret1, ret2);
}

double maxmax=0;

pair<int, int> checker(Polygon poly, int idx)
{
    int ret1, ret2;
    double globalmax=0;
    int n=poly.v.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(Triangle(poly.v[idx], poly.v[i], poly.v[j]).area()>globalmax){
                ret1=i;
                ret2=j;
                globalmax=Triangle(poly.v[idx], poly.v[i], poly.v[j]).area();
            }
        }
    }
    return make_pair(ret1, ret2);
}

int main()
{
    int n, cases;
	scanf("%d", &cases);
	for(int t=0;t<cases;t++){
		scanf("%d", &n);
		Polygon poly;
		Point p;
		for(int i=0;i<n;i++){
			scanf("%lf %lf", &p.x, &p.y);
			poly.v.push_back(p);
		}
		int idx;
		maxmax=0;
		for(idx=0;idx<poly.v.size();idx++){
			pair<int, int> maxtri_ans=maxTri(poly, idx);
			//pair<int, int> maxtri_ans=checker(poly, idx);
			if(Triangle(poly.v[idx], poly.v[maxtri_ans.first], poly.v[maxtri_ans.second]).area()>maxmax){
				maxmax=Triangle(poly.v[idx], poly.v[maxtri_ans.first], poly.v[maxtri_ans.second]).area();
			}
		}
		printf("%.17f\n", maxmax);
	}
}