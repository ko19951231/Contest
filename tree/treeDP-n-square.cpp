#include<cstdio>
#include<deque>
#include<vector>

using namespace std;

vector<int> con[50003];
int n, k;
long long ans;

void solve(int idx, int parent, int deep)
{
	int id;
    if(deep==k-1){
        ans+=con[idx].size()-1;
        return;
    }
	for(int i=0;i<con[idx].size();i++){
		id=con[idx][i];
        if(id==parent) continue;
        solve(id, idx, deep+1);
	}
}

int main()
{
	int p, q;
    scanf("%d %d %d", &n, &p, &q);
	k=p+q;
	int a, b;
	for(int i=0;i<50002;i++){
		con[i].clear();
	}
	for(int i=0;i<n-1;i++){
		scanf("%d %d", &a, &b);
		con[a].push_back(b);
		con[b].push_back(a);
	}
	if(k==1){
		printf("%d\n", n-1);
		return 0;
	}
	ans=0;
	for(int i=1;i<=n;i++){
        solve(i, 0, 0);
    }
	double prob=(double)ans;
	prob/=(double)n;
	prob/=(double)(n-1);
	prob/=(double)(n-2);
	printf("%.17f\n", prob);
}