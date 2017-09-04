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
    int ret1=-1, ret2=-1;
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

double ans=0;
Triangle maxTriangle;
Triangle realMax;

bool find1(Polygon p)
{
	for(int i=0;i<p.v.size();i++){
		if(p.v[i].x==4319188.830369&&p.v[i].y==9019124.561044) return 1;
	}
	return 0;
}

bool find2(Polygon p)
{
	for(int i=0;i<p.v.size();i++){
		if(p.v[i].x==-9970379.536302&&p.v[i].y==-769111.111672) return 1;
	}
	return 0;
}

bool find3(Polygon p)
{
	for(int i=0;i<p.v.size();i++){
		if(p.v[i].x==5651133.619627&&p.v[i].y==-8250132.654275) return 1;
	}
	return 0;
}

double solve(Polygon curPoly, int deep)
{
    //if(curPoly.v.size()==3) return Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[2]).area();
    //if(curPoly.v.size()==4) return max(max(Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[2]).area(), Triangle(curPoly.v[0], curPoly.v[1], curPoly.v[3]).area()), max(Triangle(curPoly.v[0], curPoly.v[3], curPoly.v[2]).area(), Triangle(curPoly.v[3], curPoly.v[1], curPoly.v[2]).area()));
    int n=curPoly.v.size();
	printf("##############n=%d deep=%d\n", n, deep);
	if(n==0) return 0;
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
	if(curPoly.v.size()==14){
		printf("POLYGON\n");
		for(int i=0;i<14;i++){
			printf("%f %f\n",curPoly.v[i].x, curPoly.v[i].y);
		}
		printf("interleave tri:\n");
		for(int i=0;i<6;i++){
			printf("%d %f %f %d\n", v[i].first, curPoly.v[v[i].first].x, curPoly.v[v[i].first].x, v[i].second);
		}
	}
	/*for(int i=0;i<6;i++){
		if(v[i].first==v[(i+1)%6].first){
			pair<int, int> p= maxTri(curPoly, v[i].first);
			if(Triangle(curPoly.v[v[i].first], curPoly.v[p.first], curPoly.v[p.second]).area()>ans){
				ans=Triangle(curPoly.v[v[i].first], curPoly.v[p.first], curPoly.v[p.second]).area();
				maxTriangle=Triangle(curPoly.v[v[i].first], curPoly.v[p.first], curPoly.v[p.second]);
			}
			return Triangle(curPoly.v[v[i].first], curPoly.v[p.first], curPoly.v[p.second]).area();
		}
		if((v[i].first+1)%n==v[(i+1)%6].first&&v[i].second!=v[(i+5)%6].second&&v[(i+1)%6].second!=v[(i+2)%6].second){
			pair<int, int> p1= maxTri(curPoly, v[i].first);
			pair<int, int> p2= maxTri(curPoly, v[(i+1)%6].first);
			if(Triangle(curPoly.v[v[i].first], curPoly.v[p1.first], curPoly.v[p1.second]).area()>ans){
				ans=Triangle(curPoly.v[v[i].first], curPoly.v[p1.first], curPoly.v[p1.second]).area();
				maxTriangle=Triangle(curPoly.v[v[i].first], curPoly.v[p1.first], curPoly.v[p1.second]);
			}
			if(Triangle(curPoly.v[v[(i+1)%6].first], curPoly.v[p2.first], curPoly.v[p2.second]).area()>ans){
				ans=Triangle(curPoly.v[v[(i+1)%6].first], curPoly.v[p2.first], curPoly.v[p2.second]).area();
				maxTriangle=Triangle(curPoly.v[v[(i+1)%6].first], curPoly.v[p2.first], curPoly.v[p2.second]);
			}
			return max(Triangle(curPoly.v[v[i].first], curPoly.v[p1.first], curPoly.v[p1.second]).area(), Triangle(curPoly.v[v[(i+1)%6].first], curPoly.v[p2.first], curPoly.v[p2.second]).area());
		}
	}*/
	for(int i=0;i<6;i++){
		if(v[i].first==v[(i+1)%6].first){
			if(v[(i+5)%6].first!=v[(i+4)%6].first){
				v[i].second=v[(i+4)%6].second;
				v[(i+1)%6].second=v[(i+5)%6].second;
			}
			else{
				v[i].second=v[(i+2)%6].second;
				v[(i+1)%6].second=v[(i+3)%6].second;
			}
		}
	}
	puts("HERE 1");
	double ret1=0;
	double ret2=0;
	double ret=0;
	Polygon polyNext1, polyNext2;
	if(v[0].second!=v[1].second&&v[2].second!=v[3].second&&v[4].second!=v[5].second){
		//printf("sub poly 1: ");
		//printf("%d to %d, ", v[1].first, v[2].first);
		bool cal1=0, cal2=0, cal3=0;
		int minRange;
		if((v[1].first+n-v[0].first)%n<=1&&(v[3].first+n-v[2].first)%n<=1&&(v[5].first+n-v[4].first)%n<=1){
			if((v[2].first+1+n-v[1].first)%n<(v[4].first+1+n-v[3].first)%n){
				cal1=1;
				minRange=(v[2].first+1+n-v[1].first)%n;
			}
			else{
				cal2=1;
				minRange=(v[4].first+1+n-v[3].first)%n;
			}
			if((v[0].first+1+n-v[5].first)%n<minRange){
				cal1=cal2=0;
				cal3=1;
			}
		}
		for(int i=v[1].first;i%n!=(v[2].first+1)%n;i++){
			i%=n;
			if(cal1){
				pair<int, int> p=maxTri(curPoly, i);
				ret1=max(ret1, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext1.v.push_back(curPoly.v[i]);
		}
		//printf("%d to %d, ", v[3].first, v[4].first);
		for(int i=v[3].first;i%n!=(v[4].first+1)%n;i++){
			i%=n;
			if(cal2){
				pair<int, int> p=maxTri(curPoly, i);
				ret1=max(ret1, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext1.v.push_back(curPoly.v[i]);
		}
		//printf("%d to %d\n", v[5].first, v[0].first);
		for(int i=v[5].first;i%n!=(v[0].first+1)%n;i++){
			i%=n;
			printf("len %d\n", (v[0].first+1+n-v[5].first)%n);
			if(cal3){
				pair<int, int> p=maxTri(curPoly, i);
				ret1=max(ret1, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext1.v.push_back(curPoly.v[i]);
		}
	}
	puts("HERE 2");
	if(v[1].second!=v[2].second&&v[3].second!=v[4].second&&v[5].second!=v[0].second){
		//printf("sub poly 2: ");
		//printf("%d to %d, ", v[2].first, v[3].first);
		bool cal1=0, cal2=0, cal3=0;
		int minRange;
		if((v[2].first+n-v[1].first)%n<=1&&(v[4].first+n-v[3].first)%n<=1&&(v[0].first+n-v[5].first)%n<=1){
			if((v[3].first+1+n-v[2].first)%n<(v[5].first+1+n-v[4].first)%n){
				cal1=1;
				minRange=(v[3].first+1+n-v[2].first)%n;
			}
			else{
				cal2=1;
				minRange=(v[5].first+1+n-v[4].first)%n;
			}
			if((v[1].first+1+n-v[0].first)%n<minRange){
				cal1=cal2=0;
				cal3=1;
			}
		}
		for(int i=v[2].first;i%n!=(v[3].first+1)%n;i++){
			i%=n;
			if(cal1){
				pair<int, int> p=maxTri(curPoly, i);
				ret2=max(ret2, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext2.v.push_back(curPoly.v[i]);
		}
		//printf("%d to %d, ", v[4].first, v[5].first);
		for(int i=v[4].first;i%n!=(v[5].first+1)%n;i++){
			i%=n;
			if(cal2){
				pair<int, int> p=maxTri(curPoly, i);
				ret2=max(ret2, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext2.v.push_back(curPoly.v[i]);
		}
		//printf("%d to %d\n", v[0].first, v[1].first);
		for(int i=v[0].first;i%n!=(v[1].first+1)%n;i++){
			i%=n;
			if(cal3){
				pair<int, int> p=maxTri(curPoly, i);
				ret2=max(ret2, Triangle(curPoly.v[i], curPoly.v[p.first], curPoly.v[p.second]).area());
			}
			//printf("%d ", i);
			polyNext2.v.push_back(curPoly.v[i]);
		}
	}
	puts("HERE 3");
	printf("ret1 %f ret2 %f\n", ret1, ret2);
	printf("solve %d %d\n", polyNext1.v.size(), polyNext2.v.size());
	if(ret1==0&&polyNext1.v.size()) ret1=solve(polyNext1, deep+1);
	if(ret2==0&&polyNext2.v.size()) ret2=solve(polyNext2, deep+1);
	puts("HERE 4");
	return max(ret1, ret2);
	/*puts("here");
	if(find1(polyNext1)&&find2(polyNext1)&&find3(polyNext1)){
		printf("all in %d\n", polyNext1.v.size());
		return solve(polyNext1);
	}
	else if(find1(polyNext2)&&find2(polyNext2)&&find3(polyNext2)){
		printf("all in %d\n", polyNext2.v.size());
		return solve(polyNext2);
	}
	else{
		printf("why depart?\n");
		for(int i=0;i<6;i++){
			printf("%f %f\n", curPoly.v[v[i].first].x, curPoly.v[v[i].first].y);
		}
	}*/
}

int main()
{
    freopen("input10.txt", "r", stdin);
	//freopen("output10.txt", "w", stdout);
	Polygon poly;
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        Point p;
        scanf("%lf %lf", &p.x, &p.y);
        poly.v.push_back(p);
    }
	/*int idx;
	while(scanf("%d", &idx)!=EOF){
		pair<int, int> roots=maxTri(poly, idx);
		printf("%d %d %f\n", roots.first, roots.second, Triangle(poly.v[idx], poly.v[roots.first], poly.v[roots.second]).area());
	}*/
	//puts("GOGO");
    printf("%.17f\n", solve(poly, 0));
	//printf("%.17f\n", ans);
	//printf("%f %f, %f %f, %f %f\n", maxTriangle.a.x, maxTriangle.a.y, maxTriangle.b.x, maxTriangle.b.y, maxTriangle.c.x, maxTriangle.c.y);
}