/*
ID: BOARDCOVER ( https://algospot.com/judge/problem/read/BOARDCOVER )
���ȣ���� �̿��Ͽ� ����
2017-02-21
*/

#include<iostream>

using namespace std;

bool init();
//��� ȣ�� �Լ�
void boardCover();
// ���� ��ġ�� ����� ���⿡ ��ȿ�� ��ġ���� Ȯ�����ִ� �Լ�
bool isAvailable(int i, int j);
void set(int i, int j, int type);

int board[20][20];
int H = 0;
int W = 0;
int C = 0;
int white = 0;
int result = 0;

int block[4][2][2] =
{
	{{ 0,1 }, { 1,0 }},
	{{ 0,1 }, { 1,1 }},
	{{ 1,0 }, { 1,1 }},
	{{ 1,-1 }, { 1,0 }}
};

int main(void)
{
	cin >> C;

	for (int t = 0; t < C; t++)
	{
		if (init())
		{
			boardCover();
			printf("\n%d\n\n", result);
		}
	}
}

bool init()
{
	char tmp;

	result = 0;
	H = 0;
	W = 0;
	white = 0;

	cin >> H;
	cin >> W;

	// board�� ����
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> tmp;
			if (tmp == '#') board[i][j] = 1;
			else { board[i][j] = 0; white++; }
		}
	}

	if (white % 3) { printf("0\n"); return false; }

	return true;
}

void boardCover()
{
	if (white == 0) { result++; return; }
	
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			// ���� ���� �� ĭ�� ã�� �� ���� ����� ���� �� �ִ� ����� ���� Ž���Ѵ�. 
			if (isAvailable(i, j))
			{
				for (int k = 0; k < 4; k++)
					set(i, j, k);
				// �װ��� ��츦 �� ���� �� �Ŀ� �Լ��� �����Ѵ�.
				return;
			}
}

void set(int i, int j, int type)
{
	// ���� Ÿ���� i,j�̿��� �� ��Ͽ� ���� ���ο� i,j ��ǥ
	int ni_1 = i + block[type][0][0];
	int nj_1 = j + block[type][0][1];
	int ni_2 = i + block[type][1][0];
	int nj_2 = j + block[type][1][1];
	//���� ����� ���� �� �ִٸ� ���带 ä��� ����� -3 �� �� �� ������ ���忡�� �ٽ� Ž���Ѵ�.
	if (isAvailable(ni_1, nj_1) && isAvailable(ni_2, nj_2))
	{
		board[i][j] = board[ni_1][nj_1] = board[ni_2][nj_2] = 1;
		white -= 3;
		boardCover();
		white += 3;
		board[i][j] = board[ni_1][nj_1] = board[ni_2][nj_2] = 0;
	}
}

// �� �ڸ��� ��ȿ�� ���� ���� ����ִ� �ڸ��ΰ� Ȯ�����ش�.
bool isAvailable(int i, int j)
{
	if (i < 0 || j < 0 || i >= H || j >= W || board[i][j]==1)
		return false;

	return true;
}