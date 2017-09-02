#include<cstdio>
#include<vector>
#include<cmath>
#include<cstdlib>

using namespace std;

vector<int> v;

int main()
{
    freopen("input01.txt", "w", stdout);
    int n;
    //scanf("%d", &n);
    n=50000;
    printf("%d\n", n);
    double all=0;
    for(int i=0;i<n;i++){
        int rnd=1;
        all+=rnd;
        v.push_back(rnd);
    }
    double cur=0;
    for(int i=0;i<n;i++){
        cur+=2*acos(-1)*(double)v[i]/all;
        printf("%f %f\n", 1e7*cos(cur), 1e7*sin(cur));
    }
    return 0;
}