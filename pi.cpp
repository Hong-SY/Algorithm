/*
ID:PI ( https://algospot.com/judge/problem/read/PI )
2017-09-11 16:49
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string sequence;
int memoization[10000];
int length=0;
int C;

bool check_is_all_same(int start, int num);
// 단순 증가,감소 수열
bool check_is_simple(int start, int num);
bool check_is_repeat_two_number(int start, int num);
bool check_is_arithmetic_sequence(int start, int num);
int check_difficulty(int start, int num);
int min_difficulty(int start);

int main(void)
{
	cin >> C;

	for (int i = 0; i < 10000; ++i)
		memoization[i] = -1;

	for (int t = 0; t < C; ++t)
	{
		cin >> sequence;

		for (int i = 0; i < length; ++i)
			memoization[i] = -1;

		length = sequence.length();
		
		int result = min_difficulty(0);
		cout << result << endl;
	}
}

bool check_is_all_same(int start, int num)
{
	for (int i = 1; i < num; ++i)
		if (sequence[start + i - 1] != sequence[start + i])
			return false;
	return true;
}

bool check_is_simple(int start, int num)
{
	int common_difference = sequence[start + 1] - sequence[start];

	if (common_difference != 1 && common_difference != -1)
		return false;

	for (int i = 2; i < num; ++i)
		if ((sequence[start + i] - sequence[start + i - 1] != common_difference))
			return false;

	return true;
}

bool check_is_repeat_two_number(int start, int num)
{
	char A = sequence[start];
	char B = sequence[start + 1];
	for (int i = 2; i < num; ++i)
		if (i % 2 == 0)
		{
			if (sequence[start+i] != A)
				return false;
		}
		else
		{
			if (sequence[start+i] != B)
				return false;
		}
	return true;
}

bool check_is_arithmetic_sequence(int start, int num)
{
	int common_difference = sequence[start + 1] - sequence[start];

	for (int i = 2; i < num; ++i)
		if ((sequence[start + i] - sequence[start + i - 1] != common_difference))
			return false;

	return true;
}

int check_difficulty(int start, int num)
{
	if (check_is_all_same(start, num))
		return 1;
	else if (check_is_simple(start, num))
		return 2;
	else if (check_is_repeat_two_number(start, num))
		return 4;
	else if (check_is_arithmetic_sequence(start, num))
		return 5;
	else
		return 10;
}

int min_difficulty(int start)
{
	if (memoization[start] != -1)
		return memoization[start];
	if (length - start == 3)
		memoization[start] = check_difficulty(start, 3);
	else if (length - start == 4)
		memoization[start] = check_difficulty(start, 4);
	else if (length - start == 5)
		memoization[start] = check_difficulty(start, 5);
	else if (length - start == 6)
		memoization[start] = check_difficulty(start, 3) + check_difficulty(start + 3, 3);
	else if (length - start == 7)
	{
		memoization[start] =
			min(check_difficulty(start, 3) + check_difficulty(start + 3, 4), 
				check_difficulty(start, 4) + check_difficulty(start + 4, 3));
	}
	else
	{
		int mn =
			min(min_difficulty(start + 3) + check_difficulty(start, 3),
				min_difficulty(start + 4) + check_difficulty(start, 4));
		memoization[start] =
			min(mn, min_difficulty(start + 5) + check_difficulty(start, 5));
	}

	return memoization[start];
}