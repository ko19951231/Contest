#include<cstdio>
#include<deque>
#include<vector>

using namespace std;

vector<int> con[50003];
bool traversed[50003]={0};

int n, k, p, q;
long long ans;

long long dp[50005][505];

void solve(int idx)
{
	traversed[idx]=1;
	dp[idx][0]=1;
	int id;
	for(int i=0;i<con[idx].size();i++){
		id=con[idx][i];
		if(traversed[id]) continue;
		solve(id);
		for(int x=0;x<k;x++){
			ans+=dp[idx][x]*dp[id][k-1-x];
		}
		for(int x=0;x<=k;x++){
			dp[idx][x+1]+=dp[id][x];
		}
	}
}

int main()
{
	scanf("%d %d %d", &n, &p, &q);
	k=p+q;
	int a, b;
	for(int i=0;i<50002;i++){
		for(int j=0;j<502;j++) dp[i][j]=0;
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
	solve(1);
	double prob=(double)ans;
	prob/=(double)n;
	prob/=(double)(n-1);
	prob/=(double)(n-2);
	printf("%.17f\n", prob);
}