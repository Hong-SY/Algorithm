/*
ID: JLIS ( https://algospot.com/judge/problem/read/JLIS )
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int c, n, m;

const long long INF = numeric_limits<long long>::min();
int A[100], B[100];
int cache[101][101];

int jlis(int indexA, int indexB)
{
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	
	ret = 2;
	long long a = (indexA == -1 ? INF : A[indexA]);
	long long b = (indexB == -1 ? INF : B[indexB]);
	long long maxElement = max(a, b);

	for (int nextA = indexA + 1; nextA < n; ++nextA)
		if (maxElement < A[nextA])
			ret = max(ret, jlis(nextA, indexB) + 1);
	for (int nextB = indexB + 1; nextB < m; ++nextB)
		if (maxElement < B[nextB])
			ret = max(ret, jlis(indexA, nextB) + 1);
	return ret;
}

int main(void)
{
	cin >> c;
	for (int t = 0; t < c; ++t)
	{
		cin >> n >> m;
		int a, b;

		for (int i = 0; i < n; ++i)
		{
			cin >> a;
			A[i] = a;
		}
		for (int i = 0; i < m; ++i)
		{
			cin >> a;
			B[i] = a;
		}

		for (int i = 0; i < 101; ++i)
			for (int j = 0; j < 101; ++j)
				cache[i][j] = -1;
		
		int mx = 0;
		int tmp = 0;
		mx = jlis(-1, -1);
		cout << mx-2 << endl;
	}
}