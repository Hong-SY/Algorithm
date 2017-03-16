/*
ID: WILDCARD ( https://algospot.com/judge/problem/read/WILDCARD )
���̳��� ���α׷���
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
	// base : �Ѵ� �迭�� �� ��� ���¸� pass, Ű�� ���� ����ų� ������ �ξ� ���� ����� fail.
	// key�� �������� *�� �� ���� ����� file_idx == fn �� �ɶ��� 0�� ��ȯ���� �ʴ´�.
	if (key_idx == kn && file_idx == fn)
		return 1;
	if (key_idx >= kn || file_idx > fn)
		return 0;
	// ���� ���α׷���. ���� idx�� ��ġ�� �̹� ����ߴٸ� ��� ����� �̿�
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