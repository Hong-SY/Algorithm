/*
ID: QUADTREE ( https://algospot.com/judge/problem/read/QUADTREE )
���������� ���ȣ���� �̿��� �ۼ��Ͽ���.
2017-02-27 18:40
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ������ Ǭ��. ����� zip_original�� �����Ѵ�.
int solve(vector<char>& zip_original);

// �� ���� Ʈ���� 3,4 ��и� 1,2 ��и� ������ ��ģ��.
// ����� vector2�� �����Ѵ�.
vector<char>& merge(const vector<char>& vector1, vector<char>& vector2);

int main(void)
{
	int Tcase;
	cin >> Tcase;

	for (int t = 0; t < Tcase; t++)
	{
		// string���� �� ���� �ѹ��� �޴´�.
		string zip_original_string;
		cin >> zip_original_string;

		// ���� ������ �ϳ��� zip_original�� �ִ´�.
		vector<char> zip_original;
		for (unsigned int i = 0; i < zip_original_string.size(); i++)
			zip_original.push_back(zip_original_string[i]);

		// ������ Ǯ�� ����Ѵ�.
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
	// ũ�Ⱑ 5�̸� �׳� ���ش�.
	else if (zip_original.size() == 5)
	{
		vector<char> a(zip_original.begin() + 1, zip_original.begin() + 3);	
		vector<char> b(zip_original.begin() + 3, zip_original.begin() + 5);
		
		zip_original = merge(a,b);
		return 5;
	}
	else
	{
		// ���� x�� �����ϴ� ���忡�� �ڽ��� child�� 3��° ��ȣ�� 4��° ��ȣ�� �����Ѵ�.
		// �ٽ� x�� ������ �� x���� �������� ���ȣ��� �����Ѵ�.
		// 3��°�� ó���� 4��°�� ���� ã���� begin()���� begin()+second, begin()+second���� begin()+forth �� ���� ��
		// ������ �ٲ� merge�Ѵ�. (3,4,1,2 ��и� ������ ����)
		// forth�� ����ȣ�� ��ȯ�Ѵ�. ��ȯ���� ����ȣ�� ���� x�� ���� ������ ���ڿ��� �����ϰ� ������° ���ĺ��� ó���� �˷��ش�.
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