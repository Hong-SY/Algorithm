/*
ID: QUANTIZE ( https://algospot.com/judge/problem/read/QUANTIZE )
2017-03-12 12:19
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<numeric>

using namespace std;

const int INF = 987654321;

int C, N, S;
int sequence[100];
int memoization[11][100];

int quantization(int start, int S);
int variance(int start, int end);

int main(void)
{
	cin >> C;

	for (int t = 0; t < C; ++t)
	{
		// �ʱ�ȭ
		cin >> N >> S;

		for (int i = 0; i < N; ++i)
			cin >> sequence[i];
		for (int i = 0; i <= S; ++i)
			for(int j= 0 ; j < N ; ++j)
				memoization[i][j] = -1;

		// ������������ �����Ѵ�.
		sort(sequence, sequence+N);

		int result = INF;

		// �ִ� S���� �κ����� �����Ƿ� 1���� S���� ���� �� ����. �� �� �ּڰ�.
		for (int i = 1; i <= S; ++i)
		{
			int tmp = quantization(0, i);
			if (tmp < result)
				result = tmp;
		}

		cout <<result << endl;
	}
}
// ����ȭ�� Ǫ�� �Լ�
int quantization(int start, int S)
{
	//base
	if (start >= N - 1)
		return 0;
	if (memoization[S][start] != -1)
		return memoization[S][start];

	int mn = INF;
	int tmp = 0;

	// S �� 1�̸� �������ڷ� ����ȭ
	if (S == 1)
		return variance(start, N - 1);
	// S�� 1�� �ƴϸ� start���� start+N-S ������ ���ʷ� �л��� ���ϰ� �������� ��ͷ� ����.
	else
	{
		for (int i = 0; i < N - S+1; ++i)
		{
			tmp = variance(start, start + i) + quantization(start+i+1, S-1);
			if (tmp < mn)
				mn = tmp;
		}
	}

	memoization[S][start] = mn;
	return mn;
}

int variance(int start, int end)
{
	int mean_up;
	int mean_down;
	int sum = sequence[start];
	int variance_up=0;
	int variance_down=0;
	for (int i = start+1; i <= end; ++i)
		sum += sequence[i];

	// ������ �������� �����°� �������� �ø��°� �������� �𸣹Ƿ� �� �� ���.
	mean_up = sum / (end - start + 1);
	mean_down = sum / (end - start + 1) + 1;

	for (int i = start; i <= end; ++i)
	{
		variance_up += (sequence[i] - mean_up)*(sequence[i] - mean_up);
		variance_down += (sequence[i] - mean_down)*(sequence[i] - mean_down);
	}

	return min(variance_up, variance_down);
}
