#include <iostream>
using namespace std;
// ����symbol�����¼��������Ϣ�ݹ鹹�������������
void getList(int i, int j, int **symbol, char *a)
{
	if (!i || !j)
	{
		return;
	}
	if (symbol[i][j] == 1)
	{
		getList(i - 1, j - 1, symbol, a);
		cout << a[i - 1];
	}
	else if (symbol[i][j] == 2)
	{
		getList(i - 1, j, symbol, a);
	}
	else if (symbol[i][j] == 3)
	{
		getList(i, j - 1, symbol, a);
	}
}
int main()
{
	int m;
	cin >> m;
	char *a = new char[m + 1];
	char *b = new char[m + 1];
	cin >> a >> b;
	int **list = new int *[m + 1];
	int **symbol = new int *[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		list[i] = new int[m + 1];
	}
	for (int i = 0; i < m + 1; i++)
	{
		symbol[i] = new int[m + 1]; // ��¼���Ų�����Դ
	}
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			list[i][j] = 0;
			symbol[i][j] = 0;
		}
	}
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			// �����ǰ�ַ���ͬ���򹫹������еĳ���Ϊ���ַ�ǰ�����������+1
			if (a[i - 1] == b[j - 1])
			{
				list[i][j] = list[i - 1][j - 1] + 1;
				// ��¼���Ų�����Դ
				symbol[i][j] = 1;
			}
			else
			{
				// �����ǰ�ַ�����ͬ���򹫹������еĳ���Ϊlist[i - 1][j]��list[i][j - 1]�е����ֵ
				list[i][j] = max(list[i - 1][j], list[i][j - 1]);
				// ��¼���Ų�����Դ
				if (list[i][j] == list[i - 1][j])
					symbol[i][j] = 2;
				else
					symbol[i][j] = 3;
			}
		}
	}
	if (!list[m][m])
		cout << "�޹���������";
	else
		getList(m, m, symbol, a); // ����symbol[i][j]���鵹�����Ž�
}