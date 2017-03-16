/*
ID: QUADTREE ( https://algospot.com/judge/problem/read/QUADTREE )
분할정복과 재귀호출을 이용해 작성하였다.
2017-02-27 18:40
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 문제를 푼다. 결과는 zip_original에 저장한다.
int solve(vector<char>& zip_original);

// 두 개의 트리를 3,4 사분면 1,2 사분면 순서로 합친다.
// 결과는 vector2에 저장한다.
vector<char>& merge(const vector<char>& vector1, vector<char>& vector2);

int main(void)
{
	int Tcase;
	cin >> Tcase;

	for (int t = 0; t < Tcase; t++)
	{
		// string으로 한 줄을 한번에 받는다.
		string zip_original_string;
		cin >> zip_original_string;

		// 받은 문장을 하나씩 zip_original에 넣는다.
		vector<char> zip_original;
		for (unsigned int i = 0; i < zip_original_string.size(); i++)
			zip_original.push_back(zip_original_string[i]);

		// 문제를 풀고 출력한다.
		solve(zip_original);
		vector<char>& zip_new = zip_original;

		for (unsigned int i = 0; i < zip_new.size(); i++)
			cout << zip_new[i];
		cout << endl;
	}
	cin >> Tcase;
}

int solve(vector<char>& zip_original)
{
	if (zip_original.size() == 1)
		return 1;
	// 크기가 5이면 그냥 해준다.
	else if (zip_original.size() == 5)
	{
		vector<char> a(zip_original.begin() + 1, zip_original.begin() + 3);	
		vector<char> b(zip_original.begin() + 3, zip_original.begin() + 5);
		
		zip_original = merge(a,b);
		return 5;
	}
	else
	{
		// 현재 x로 시작하는 문장에서 자신의 child의 3번째 번호와 4번째 번호를 저장한다.
		// 다시 x를 만나면 그 x부터 끝까지를 재귀호출로 전달한다.
		// 3번째의 처음과 4번째의 끝을 찾으면 begin()부터 begin()+second, begin()+second부터 begin()+forth 로 나눈 후
		// 순서를 바꿔 merge한다. (3,4,1,2 사분면 순으로 저장)
		// forth의 끝번호를 반환한다. 반환받은 끝번호는 상위 x에 대해 어디까지 문자열을 복사하고 다음번째 알파벳의 처음을 알려준다.
		int second = -1;
		int forth = -1;
		int cnt = 0;

		for (unsigned int i = 1; i < zip_original.size(); i++)
		{
			if (zip_original[i] == 'x')
			{
				vector<char> tmp(zip_original.begin() + i, zip_original.end());
				int length = solve(tmp);
				for (unsigned int j = 0; j < length; j++)
					zip_original[i + j] = tmp[j];
				i = i + length-1;
			}
			++cnt;
			if (cnt == 2)
				second = i + 1;
			else if (cnt == 4)
			{ forth = i + 1; break; }
		}

		vector<char> zip_first(zip_original.begin()+1, zip_original.begin()+second);
		vector<char> zip_second(zip_original.begin() + second, zip_original.begin() + forth);

		merge(zip_first, zip_second);

		for (unsigned int i = 0; i < zip_second.size(); i++)
			zip_original[i] = zip_second[i];

		return forth;
	}
}

vector<char>& merge(const vector<char>& vector1, vector<char>& vector2)
{
	for(unsigned int i=0 ; i<vector1.size() ; i++)
		vector2.push_back(vector1[i]);
	vector2.insert(vector2.begin(), 'x');

	return vector2;
}