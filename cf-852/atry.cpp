
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstdlib>
#pragma comment(linker, "/STACK:336777216")  

using namespace std;

const int MAXN = 2000000 + 10;
const int MOD = 1000000007;

int N;
char S[MAXN];
int dp[MAXN];

int dfs(int rem, int sum)
{
	if (dp[sum + rem] == 1)
	{
		//printf("%d+", rem);
		return 1;
	}

	if (rem == 0)
		return 0;
	
	int tmp = 10;
	while (1)
	{
		if (rem / tmp == 0)
			break;
		if (dfs(rem / tmp, sum + rem % tmp))
		{
			//printf("%d+", rem % tmp);
			return 1;
		}
		tmp *= 10;
	}
	return 0;
}

void Work()
{
	/*
	scanf("%d%s", &N, S);
	for (int i = 0; i < N - 1; i ++)
		printf("%c+", S[i]);
	printf("%c\n", S[N - 1]);
	*/
	int sum = 0;
	for (int i = 0; i < N; i ++)
		sum += S[i] - '0';

	sum = 1800000;

	int maxx = 0;
	for (int i = 10; i <= sum; i ++)
	{
		int tmp = 0, cur = i;
		while (cur)
		{
			tmp += cur % 10;
			cur /= 10;
		}
		if (tmp < 10)
			dp[i] = 1;
		else
			dp[i] = dp[tmp] + 1;
		if (dp[i] == 3)
		{
			if (! dfs(i, 0))
				maxx ++;
		}
	}

	printf("%d\n", maxx);
}

int main()
{
	Work();
	return 0;
}
