/*
ID: PICNIC ( https://algospot.com/judge/problem/read/PICNIC )
��� ȣ���� �̿��Ͽ� �ۼ��Ͽ���.
2017-02-22 16:14
*/

#include<iostream>

using namespace std;

void picnic(void);

int student[10][10]; // ��ü �л� ����
int remainStudent[10]; // ¦�������� �ʰ� ���� �ִ� �л�/
int result=0;
int num=0; // �л� ��

int main(void)
{
	int Tnum;

	cin >> Tnum;

	//Test number ��ŭ ����
	for (int t = 0; t < Tnum; t++)
	{
		//���� ���� �ʱ�ȭ
		result = 0;
		num = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
				student[i][j] = 0;
			remainStudent[i] = 0;
		}

		//�л� ���� ������ ���� �޾� �������� �迭�� ����
		int m;
		int x, y; // ������ ����

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

	//���� �л��� ������ �� �л��� firstFree�� ����
	for (int i = 0; i < num; i++)
		if (remainStudent[i] == 1) { firstFree = i; break;}

	//���� �л��� ���ٸ� ��� �������� ������ ���̹Ƿ� ����� 1 ������Ű�� �Լ��� �����Ѵ�.
	if (firstFree == -1) { result++; return; }

	//���� �л��� �� firstFree�� ¦�� �´� �л��� �ִٸ� ¦�� ���� remainStudent���� �����ش�.
	//���� ��� ȣ���� �����ϰ� �����Ŀ��� ���� Ž���� ���� ���󺹱� ���ش�.
	for (int i = firstFree+1; i < num; i++)
		if (remainStudent[i] == 1 && student[firstFree][i] == 1)
		{
			remainStudent[i] = remainStudent[firstFree] = 0;
			picnic();
			remainStudent[i] = remainStudent[firstFree] = 1;
		}
}