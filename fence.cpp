/*
ID: FENCE ( https://algospot.com/judge/problem/read/FENCE )
분할정복 알고리즘
2017-02-27 21:31
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// C: 테스트 케이스 (C<=50)
// N: 판자의 수 (1<=N<=20000)
int C;
int N;
int Max=-1;
int board[20000];

// 인자: 배열 범위 의 왼쪽 끝과 오른쪽 끝 번호. 
// 반환: 판자의 최대 넓이
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
	// 하나나 두 개일 때. base
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
		// 반으로 나눠 왼쪽 오른쪽 따로 가장 큰 넓이를 구한다.
		int middle = (right + left) / 2;
		int left_max = solve(left, middle);
		int right_max = solve(middle + 1, right);
		int height = min(board[middle], board[middle + 1]);
		int Max = max(left_max,right_max);
		Max = max(Max, height * 2);

		// 가운데를 포함하는 넓이. (middle, middle+1) 부터 시작하여 board[i-1], board[j+1]을 비교하여 큰 쪽으로 범위를 넓혀간다.
		// 좌우 끝까지 넓히고 그 중 가장 큰 넓이를 반환한다.
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
