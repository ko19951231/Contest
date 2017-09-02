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
    int n=curPoly.v.size();
    int ret1, ret2;
    int a=(idx+1)%n;
    int b=(idx+2)%n;
    double globalMax=0;
    while(a!=idx){
        double localMax=0;
        bool change=1;
        while(change){
            change=0;
            for(int tmp=b;tmp%n!=idx;tmp++)
            {
                tmp%=n;
                //printf("tmpb=%d\n", tmp);
                if(Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[tmp]).area()>localMax){
                    if(tmp!=b) change=1;
                    b=tmp;
                    localMax=Triangle(curPoly.v[idx], curPoly.v[a], curPoly.v[tmp]).area();
                }
            }
            if(!change) break;
            change=0;
            //printf("B=%d\n", b);
            for(int tmp=a;tmp%n!=b;tmp++){
                tmp%=n;
                //printf("tmpa=%d\n", tmp);
                if(Triangle(curPoly.v[idx], curPoly.v[tmp], curPoly.v[b]).area()>localMax){
                    if(tmp!=a) change=1;
                    a=tmp;
                    localMax=Triangle(curPoly.v[idx], curPoly.v[tmp], curPoly.v[b]).area();
                }
            }
            //printf("A=%d\n", a);
        }
        //printf("2 stable %d %d\n", a, b);
        if(localMax>globalMax){
            globalMax=localMax;
            ret1=a;
            ret2=b;
        }
        a=(a+1)%n;
    }
    return make_pair(ret1, ret2);
}

double solve(Polygon curPoly)
{
    if(curPoly.v.size()==3) return Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[2]).area();
    if(curPoly.v.size()==4) return max(max(Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[2]).area(), Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[3]).area()), max(Triangle(curPoly.v[0], curPoly.v[3], curPoly.v[2]).area(), Triangle(curPoly.v[3], curPoly.v[1], curPoly.v[2]).area()));
    int n=curPoly.v.size();
	int rootA=rand()%n;
	pair<int, int> pairA=maxTri(curPoly, rootA);
    int triA[3];
	triA[0]=rootA;
	triA[1]=pairA.first;
	triA[2]=pairA.second;
	int maxRange;
	int rootB;
	if((triA[1]+n-triA[0])%n>(triA[2]+n-triA[1])%n){
		maxRange=(triA[1]+n-triA[0])%n;
		rootB=(maxRange/2+triA[0])%n;
	}
	else{
		maxRange=(triA[2]+n-triA[1])%n;
		rootB=(maxRange/2+triA[1])%n;
	}
	if((triA[0]+n-triA[2])%n>maxRange){
		maxRange=(triA[0]+n-triA[2])%n;
		rootB=(maxRange/2+triA[2])%n;
	}
	pair<int, int> pairB=maxTri(curPoly, rootB);
	int triB[3];
	triB[0]=rootB;
	triB[1]=pairB.first;
	triB[2]=pairB.second;
	printf("A %d %d %d\n", triA[0], triA[1], triA[2]);
	printf("B %d %d %d\n", triB[0], triB[1], triB[2]);
	vector<pair<int, int> > v;
	for(int i=0;i<3;i++){
		v.push_back(make_pair(triA[i], 1));
		v.push_back(make_pair(triB[i], 2));
	}
	sort(v.begin(), v.end());
	for(int i=0;i<5;i++){
		if(v[i].first==v[i+1].first){
			pair<int, int> p= maxTri(curPoly, v[i].first);
			return Triangle(curPoly.v[v[i].first], curPoly.v[p.first], curPoly.v[p.second]).area();
		}
		if((v[i].first+1)%n==v[i+1].first&&v[i].second!=v[i+1].second){
			pair<int, int> p1= maxTri(curPoly, v[i].first);
			pair<int, int> p2= maxTri(curPoly, v[i+1].first);
			return max(Triangle(curPoly.v[v[i].first], curPoly.v[p1.first], curPoly.v[p1.second]).area(), Triangle(curPoly.v[v[i+1].first], curPoly.v[p2.first], curPoly.v[p2.second]).area());
		}
	}
	for(int i=0;i<6;i++) printf("%d ", v[i].first);
	puts("");
	double ret=0;
	if(v[0].second!=v[1].second&&v[2].second!=v[3].second&&v[4].second!=v[5].second){
		Polygon polyNext;
		printf("sub poly: ");
		for(int i=v[1].first;i%n!=(v[2].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		for(int i=v[3].first;i%n!=(v[4].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		for(int i=v[5].first;i%n!=(v[0].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		puts("");
		ret=solve(polyNext);
	}
	if(v[1].second!=v[2].second&&v[3].second!=v[4].second&&v[5].second!=v[0].second){
		Polygon polyNext;
		printf("sub poly: ");
		for(int i=v[2].first;i%n!=(v[3].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		for(int i=v[4].first;i%n!=(v[5].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		for(int i=v[0].first;i%n!=(v[1].first+1)%n;i++){
			i%=n;
			printf("%d ", i);
			polyNext.v.push_back(curPoly.v[i]);
		}
		puts("");
		ret=max(ret, solve(polyNext));
	}
	return ret;
}

int main()
{
    Polygon poly;
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        Point p;
        scanf("%lf %lf", &p.x, &p.y);
        poly.v.push_back(p);
    }
    printf("%.17f\n", solve(poly));
    /*pair<int, int> result=maxTri(poly, 0);
    printf("%d %d\n", result.first, result.second);*/
}