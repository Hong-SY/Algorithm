/*
ID:NUMB3RS ( https://algospot.com/judge/problem/read/NUMB3RS )
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
c : �׽�Ʈ���̽�
n : ���� �� 50��
d : ���� �ϼ� 100��
p : ������ ��ġ
t : ����� ������ ��
q : Ȯ���� ����� ������ ��ȣ
*/
int c, n, d, p, t, q;

int map[50][50];
double memoization[50][100];
int deg[50];

double numb3rs(int here, int days);

int main(void)
{
	cin >> c;

	for (int T = 0; T < c; ++T)
	{
		cin >> n >> d >> p;

		for (int i = 0; i < n; ++i)
		{
			deg[i] = 0;
			for (int j = 0; j < d; ++j)
				memoization[i][j] = -1;
			for (int j = 0; j < n; ++j)
			{
				cin >> map[i][j];
				if (map[i][j] == 1)
					deg[i]++;
			}
		}

		cin >> t;
		double result;
		
		for (int i = 0; i < t; ++i)
		{
			cin >> q;
			result = numb3rs(q, d);
			printf("%.8lf ", result);
		}

		cout << endl;
	}
}

double numb3rs(int here, int days)
{
	if (days == 0) return (here == p ? 1.0 : 0.0);
	double& ret = memoization[here][days-1];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int next = 0; next < n; ++next)
		if(map[here][next])
			ret += numb3rs(next, days - 1)/deg[next];
	return ret;
}