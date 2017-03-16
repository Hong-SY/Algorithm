/*
ID: POLY ( https://algospot.com/judge/problem/read/POLY )
2017-03-16 16:05
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 10000000;
int memoization[101][101];
int C, n;

int poly_omino(int num, int prev_num);

int main(void)
{
	cin >> C;

	for (int i = 0; i < 101; ++i)
		for(int j= 0; j<101 ; ++j)
			memoization[i][j] = -1;

	for (int t = 0; t < C; ++t)
	{
		cin >> n;
		int result = poly_omino(n, 0);
		cout <<result << endl;
	}
}

int poly_omino(int num, int prev_num)
{
	int& ret = memoization[num][prev_num];
	int sum = 0, tmp;

	if (ret != -1)
		return ret;
	// Ã¹ ½ÃÀÛ
	if (prev_num == 0)
	{
		for (int i = 1; i < num; ++i)
			sum = (sum+poly_omino(num - i, i))%MOD;
		sum += 1;
		return ret = sum%MOD;
	}
	// base
	if (num == 1)
		return prev_num;

	for (int i = 1; i < num; ++i)
	{
		tmp = (prev_num+i-1)*poly_omino(num - i, i);
		sum = (sum+tmp)%MOD;
	}

	ret = (sum + (num+prev_num-1))%MOD;

	return ret;
}