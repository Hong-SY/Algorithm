/*
ID: FENCE ( https://algospot.com/judge/problem/read/FENCE )
�������� �˰���
2017-02-27 21:31
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// C: �׽�Ʈ ���̽� (C<=50)
// N: ������ �� (1<=N<=20000)
int C;
int N;
int Max=-1;
int board[20000];

// ����: �迭 ���� �� ���� ���� ������ �� ��ȣ. 
// ��ȯ: ������ �ִ� ����
int solve(int left, int right);

int main(void)
{
	cin >> C;

	for (int t = 0; t < C; t++)
	{
		cin >> N;
		int tmp;
		for (int i = 0; i < N; i++)
			cin >> board[i];

		cout << solve(0, N - 1) << endl;
	}
}

int solve(int left, int right)
{
	// �ϳ��� �� ���� ��. base
	if (right == left+1)
	{
		if (board[right] > board[left])
			return max(board[left] * 2, board[right]);
		else
			return max(board[right] * 2, board[left]);
	}
	else if (right == left) return board[left];
	else
	{
		// ������ ���� ���� ������ ���� ���� ū ���̸� ���Ѵ�.
		int middle = (right + left) / 2;
		int left_max = solve(left, middle);
		int right_max = solve(middle + 1, right);
		int height = min(board[middle], board[middle + 1]);
		int Max = max(left_max,right_max);
		Max = max(Max, height * 2);

		// ����� �����ϴ� ����. (middle, middle+1) ���� �����Ͽ� board[i-1], board[j+1]�� ���Ͽ� ū ������ ������ ��������.
		// �¿� ������ ������ �� �� ���� ū ���̸� ��ȯ�Ѵ�.
		for (int i = middle, j=middle+1; ; )
		{
			if (j == right && i == left)
				break;
			else if ( j == right )
				height = min(height, board[--i]);
			else if ( i == left )
				height = min(height, board[++j]);
			else if (board[i - 1] < board[j + 1])
				height = min(height, board[++j]);
			else
				height = min(height, board[--i]);

			Max = max(Max, height*(j - i + 1));
		}

		return Max;
	}
}
