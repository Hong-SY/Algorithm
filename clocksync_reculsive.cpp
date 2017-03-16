/*
ID: CLOCKSYNC ( https://algospot.com/judge/problem/read/CLOCKSYNC )
재귀 호출을 이용하여 작성하였다.
2017-02-21 12:11
*/
#include<iostream>

using namespace std;

void clickButton(int buttnum);
void clocksync(int buttnum);
void init(void);

int clickednum = 0;
int min_clicked = 31;
int clock_16[16];
int button[10][5] =
{
	{ 0, 1, 2 , -1, -1 },
	{ 3, 7, 9 , 11 , -1 },
	{ 4, 10, 14, 15, -1 },
	{ 0, 4, 5, 6, 7 },
	{ 6, 7, 8, 10, 12 },
	{ 0, 2, 14, 15, -1 },
	{ 3, 14, 15, -1, -1 },
	{ 4, 5, 7, 14, 15 },
	{ 1, 2, 3, 4, 5 },
	{ 3, 4, 5, 9, 13 }
};


int main(void)
{
	int a = 0;

	int tcase = 0;
	cin >> tcase;
	
	for (int t = 0; t < tcase; t++)
	{
		init();
		clocksync(0);

		if (min_clicked == 31)
			cout << min_clicked - 32 << endl;
		else
			cout << min_clicked << endl;
	}
}

//초기화 함수
void init(void)
{
	min_clicked = 31;
	clickednum = 0;
	for (int i = 0; i < 16; i++)
	{
		cin >> clock_16[i];
		clock_16[i] %= 12;
	}
}

void clocksync(int buttnum)
{
	if (clickednum > min_clicked)
		return;
	
	for (int i = 0; i < 4; i++)
	{
		bool flag = true;
		// 16개의 시계가 전부 12시인지 확인하고 하나라도 아니면 false
		for (int j = 0; j < 16; j++)
			if (clock_16[j] != 0) { flag = false; break; }

		// 16개의 시계가 전부 12시라면 현재의 클릭수와 min을 비교해서 min을 갱신하고 더이상 진행해도 의미가 없으므로
		// 현재까지 한 클릭을 지우고 전 단계로 돌아간다.
		if (flag)
		{
			if (min_clicked > clickednum)
				min_clicked = clickednum;
			clickednum -= i;
			return;
		}

		//마지막 버튼이 아니라면 현재 상태에서 아래상태 버튼을 눌렀을떄의 경우 확인
		if (buttnum != 9)
			clocksync(buttnum + 1);
		clickButton(buttnum);
		clickednum++;
	}
	clickednum -= 4;
}

// 버튼의 종류에 따라 시계를 3시간씩 움직여 주는 함수
void clickButton(int buttnum)
{
	for (int i = 0; i < 5; i++)
		if (button[buttnum][i] != -1)
			clock_16[button[buttnum][i]] = (clock_16[button[buttnum][i]] + 3) % 12;
}