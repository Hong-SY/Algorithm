/*
ID: FAmembers_numEETING ( https://algospot.com/judge/problem/read/FAmembers_numEETING )
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int C;
int fans_num;
int members_num;
int Fans[200000];
int Members_revers[200000];
int Members[200000];

void addTo(vector<int>& a, const vector<int>& b, int k);
void subFrom(vector<int>& a, const vector<int>& b);
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);
vector<int > multiply(const vector<int>& a, const vector<int>& b);
int hugs(int fan_start, int fan_end, int member_start, int member_end);

int main(void)
{
	cin >> C;
	
	for (int t = 0; t < C; t++)
	{
		char tmp;
		int fans_num = 0;
		int members_num = 0;
		while (true)
		{
			scanf("%d", &tmp);
			if (tmp == '\n')
				break;
			if (tmp == 'M')
				Members[members_num++] = 1;
			else
				Members[members_num++] = 0;
		}

		for (int i = members_num-1; i >=0 ; --i)
		{
			Members_revers[i] = Members[members_num - 1 - i];
		}

		while (true)
		{
			scanf("%d", &tmp);
			if (tmp == '\n')
				break;
			if (tmp == 'M')
				Fans[fans_num++] = 1;
			else
				Fans[fans_num++] = 0;
		}

		int result = hugs(0, fans_num-1, 0, members_num-1);

		cout << result << endl;
	}
}

int hugs(int fan_start, int fan_end, int member_start, int member_end )
{
	int N = fans_num; 
	int M = members_num;
	vector<int> C = karatsuba(A, B);
	int allHugs = 0;
	for (int i = N - 1; i < M; ++i)
		if (C[i] == 0)
			++allHugs;
	return allHugs;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
	int an = a.size(), bn = b.size();
	if (an < bn) return karatsuba(b, a);
	if (an == 0 || bn == 0) return vector<int>();
	if (an <= 50) return multiply(a, b);
	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	addTo(a0, a1, 0); addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

vector<int > multiply(const vector<int>& a, const vector<int>& b)
{
	vector<int> c(a.size() + b.size() + 1, 0);
	int an = a.size();
	int bn = b.size();
	for (int i = 0; i < an; ++i)
		for (int j = 0; j < bn; ++j)
			c[i + j] += a[i] * b[j];

	return c;
}

void subFrom(vector<int>& a, const vector<int>& b)
{
	int bn = b.size();
	for (int i = 0; i < bn; i++)
		a[i] -= b[i];

	int an = a.size();
	for (int i = an-1; i >= 0; --i)
	{
		if (a[i] != 0)
			break;
		else
			a.pop_back();
	}
}

void addTo(vector<int>& a, const vector<int>& b, int k)
{
	int bn = b.size();
	for (int i = bn-1; i >= 0; --i)
	{
		if (i + k >= a.size())
		{
			int an = a.size();
			for (int j = an; j <= i + k; j++)
				a.push_back(0);
		}
		a[i + k] += b[i];
	}
}