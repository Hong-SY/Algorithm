/*
ID: WILDCARD ( https://algospot.com/judge/problem/read/WILDCARD )
다이나믹 프로그래밍
2017-03-02
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int C;
int file_num;
int kn;
int fn;
int memoization[101][101];
string keyword;
string file_name;
int wildcard(int key_idx, int file_idx);

int main(void)
{
	cin >> C;

	for (int t = 0; t < C; ++t)
	{
		cin >> keyword >> file_num;
		vector<string> result;

		kn = keyword.size();

		for (int f = 0; f < file_num; ++f)
		{
			cin >> file_name;
			fn = file_name.size();

			for (int i = 0; i < kn+1; ++i)
				for (int j = 0; j < fn+1; ++j)
					memoization[i][j] = -1;

			if (wildcard(0, 0))
				result.push_back(file_name);
		}

		sort(result.begin(), result.end());
		int size = result.size();
		for (int i = 0; i < size; ++i)
			cout << result[i] << endl;
	}
}

int wildcard(int key_idx, int file_idx)
{
	// base : 둘다 배열을 딱 벗어난 상태면 pass, 키가 먼저 벗어나거나 파일이 훨씬 많이 벗어나면 fail.
	// key의 마지막이 *이 될 때를 고려해 file_idx == fn 이 될때는 0을 반환하지 않는다.
	if (key_idx == kn && file_idx == fn)
		return 1;
	if (key_idx >= kn || file_idx > fn)
		return 0;
	// 동적 프로그래밍. 현재 idx의 위치를 이미 계산했다면 계산 결과를 이용
	if (memoization[key_idx][file_idx] != -1)
		return memoization[key_idx][file_idx];

	int result;

	if (keyword[key_idx] == '*')
		result = wildcard(key_idx + 1, file_idx) || wildcard(key_idx, file_idx + 1);
	else if (keyword[key_idx] == '?' || keyword[key_idx] == file_name[file_idx])
		result = wildcard(key_idx + 1, file_idx + 1);
	else
		result = 0;

	memoization[key_idx][file_idx] = result;
	return result;
}