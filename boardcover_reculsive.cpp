/*
ID: BOARDCOVER ( https://algospot.com/judge/problem/read/BOARDCOVER )
재귀호출을 이용하여 구현
2017-02-21
*/

#include<iostream>

using namespace std;

bool init();
//재귀 호출 함수
void boardCover();
// 현재 위치가 블록을 놓기에 유효한 위치인지 확인해주는 함수
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

	// board판 생성
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
			// 가장 앞의 빈 칸을 찾아 네 가지 블록을 놓을 수 있는 경우의 수를 탐색한다. 
			if (isAvailable(i, j))
			{
				for (int k = 0; k < 4; k++)
					set(i, j, k);
				// 네가지 경우를 다 보고 난 후엔 함수를 종료한다.
				return;
			}
}

void set(int i, int j, int type)
{
	// 현재 타입의 i,j이외의 두 블록에 대한 새로운 i,j 좌표
	int ni_1 = i + block[type][0][0];
	int nj_1 = j + block[type][0][1];
	int ni_2 = i + block[type][1][0];
	int nj_2 = j + block[type][1][1];
	//각각 블록을 놓을 수 있다면 보드를 채우고 흰색을 -3 한 후 그 상태의 보드에서 다시 탐색한다.
	if (isAvailable(ni_1, nj_1) && isAvailable(ni_2, nj_2))
	{
		board[i][j] = board[ni_1][nj_1] = board[ni_2][nj_2] = 1;
		white -= 3;
		boardCover();
		white += 3;
		board[i][j] = board[ni_1][nj_1] = board[ni_2][nj_2] = 0;
	}
}

// 그 자리가 유효한 보드 안의 비어있는 자리인가 확인해준다.
bool isAvailable(int i, int j)
{
	if (i < 0 || j < 0 || i >= H || j >= W || board[i][j]==1)
		return false;

	return true;
}