#include <iostream>
using namespace std;
int main()
{
	int n, m;
	cin >> n >> m;
	int **array = new int *[n]; // 邻接矩阵表示图
	for (int i = 0; i < n; i++)
	{
		array[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			array[i][j] = 0;
		}
	}
	int input1, input2, edge = m;
	while (edge--) // 获取边，并将矩阵内相应位置值置为1
	{
		cin >> input1 >> input2;
		array[input1][input2] = 1;
	}
	int sorted_num = 0;
	int *res = new int[n];
	while (sorted_num < n)
	{
		for (int i = 0; i < n; i++)
		{
			int num = 0;
			for (int j = 0; j < n; j++)
			{
				if (array[j][i] == 0)
					num++;
			}
			if (num == n) // 对应顶点的入度为0，没有任何一个点有到该点的有向线段
			{
				res[sorted_num++] = i; // 删除这个点
				for (int j = 0; j < n; j++)
				{
					array[i][j] = 0; // 删除从这个点出的边
				}
				for (int j = 0; j < n; j++)
				{
					array[j][i] = 1; /// 防止重复，令所有点都有指向该点的边
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << res[i] << ' ';
	}
	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete[] array;
	delete res;
}