#include<cstdio>
#include<deque>
#include<vector>

using namespace std;

vector<int> con[50003];
bool traversed[50003]={0};

int n, k;
long long ans;

long long dp[50005][505];

void solve(int idx)
{
	//printf("solve %d\n", idx);
	traversed[idx]=1;
	dp[idx][0]=1;
	int id;
	for(unsigned int i=0;i<con[idx].size();i++){
		id=con[idx][i];
		if(traversed[id]) continue;
		solve(id);
		for(int x=0;x<k;x++){
			//printf("dp[%d][%d](%I64d)*dp[%d][%d](%I64d)=%I64d\n", idx, x, dp[idx][x], id, k-1-x, dp[id][k-1-x], dp[idx][x]*dp[id][k-1-x]);
			ans+=dp[idx][x]*dp[id][k-1-x];
		}
		for(int x=0;x<=k;x++){
			dp[idx][x+1]+=dp[id][x];
		}
	}
	//printf("solved %d ans=%I64d\n", idx, ans);
}

int main()
{
	scanf("%d %d", &n, &k);
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
	printf("%I64d\n", ans);
}