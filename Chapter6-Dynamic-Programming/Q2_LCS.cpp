#include <iostream>
using namespace std;
// 根据symbol数组记录下来的信息递归构造最长公共子序列
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
		symbol[i] = new int[m + 1]; // 记录最优策略来源
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
			// 如果当前字符相同，则公共子序列的长度为该字符前的最长公共序列+1
			if (a[i - 1] == b[j - 1])
			{
				list[i][j] = list[i - 1][j - 1] + 1;
				// 记录最优策略来源
				symbol[i][j] = 1;
			}
			else
			{
				// 如果当前字符不相同，则公共子序列的长度为list[i - 1][j]与list[i][j - 1]中的最大值
				list[i][j] = max(list[i - 1][j], list[i][j - 1]);
				// 记录最优策略来源
				if (list[i][j] == list[i - 1][j])
					symbol[i][j] = 2;
				else
					symbol[i][j] = 3;
			}
		}
	}
	if (!list[m][m])
		cout << "无公共子序列";
	else
		getList(m, m, symbol, a); // 根据symbol[i][j]数组倒推最优解
}