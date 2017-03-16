/*
ID: PICNIC ( https://algospot.com/judge/problem/read/PICNIC )
재귀 호출을 이용하여 작성하였다.
2017-02-22 16:14
*/

#include<iostream>

using namespace std;

void picnic(void);

int student[10][10]; // 전체 학생 분포
int remainStudent[10]; // 짝지어지지 않고 남아 있는 학생/
int result=0;
int num=0; // 학생 수

int main(void)
{
	int Tnum;

	cin >> Tnum;

	//Test number 만큼 진행
	for (int t = 0; t < Tnum; t++)
	{
		//전역 변수 초기화
		result = 0;
		num = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
				student[i][j] = 0;
			remainStudent[i] = 0;
		}

		//학생 수와 순서쌍 수를 받아 전역변수 배열에 저장
		int m;
		int x, y; // 순서쌍 변수

		cin >> num;
		cin >> m;

		for (int i = 0; i < num; i++) remainStudent[i] = 1;

		for (int j = 0; j < m; j++)
		{
			cin >> x;
			cin >> y;
			student[x][y] = student[y][x] = 1;
		}

		picnic();
		printf("%d\n", result);
	}
}

void picnic(void)
{
	int firstFree = -1;

	//남은 학생이 있으면 그 학생을 firstFree로 지정
	for (int i = 0; i < num; i++)
		if (remainStudent[i] == 1) { firstFree = i; break;}

	//남은 학생이 없다면 모든 순서쌍이 정해진 것이므로 결과를 1 증가시키고 함수를 종료한다.
	if (firstFree == -1) { result++; return; }

	//남은 학생들 중 firstFree와 짝이 맞는 학생이 있다면 짝을 짓고 remainStudent에서 지워준다.
	//이후 재귀 호출을 진행하고 진행후에는 다음 탐색을 위해 원상복구 해준다.
	for (int i = firstFree+1; i < num; i++)
		if (remainStudent[i] == 1 && student[firstFree][i] == 1)
		{
			remainStudent[i] = remainStudent[firstFree] = 0;
			picnic();
			remainStudent[i] = remainStudent[firstFree] = 1;
		}
}