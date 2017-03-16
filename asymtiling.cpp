/*
ID: ASYMTILING ( https://algospot.com/judge/problem/read/ASYMTILING )
2017-03-16 13:37
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
int C;
int n;
int memoization[101];

int asymtiling(int n);
int tiling(int n);

int main(void)
{
	cin >> C;

	for (int t = 0; t < C; ++t)
	{
		cin >> n;
		for (int i = 1; i <= n; ++i)
			memoization[i] = -1;
		printf("%d\n", asymtiling(n));
	}
}

int asymtiling(int n)
{
	if (n % 2 == 1)
		return (tiling(n) - tiling(n / 2)+MOD)%MOD;
	else
		return (tiling(n) - (tiling(n / 2) + tiling(n / 2 - 1))%MOD + MOD)%MOD;
}

int tiling(int n)
{
	if (n <= 1) return 1;
	int& ret = memoization[n];
	if (ret != -1) return ret;
	return ret = (tiling(n - 1) + tiling(n - 2))%MOD;
}