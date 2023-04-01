#include <iostream>
#include <cmath>
using namespace std;
int get_distance(int x1, int y1, int x2, int y2) // 获取两点之间距离的平方
{
	return pow((x1 - x2), 2) + pow((y1 - y2), 2);
}
int main()
{
	int n;
	cin >> n;
	int **pair = new int *[n];
	for (int i = 0; i < n; i++)
	{
		pair[i] = new int[2];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> pair[i][j];
		}
	}
	int min_distance = pow(2, 31) - 1;
	int min_pair[2][2];
	int distance;
	for (int i = 0; i < n - 1; i++) // 两层遍历，计算任意两点间距离，与min_distance比较
	{
		for (int j = i + 1; j < n; j++)
		{
			distance = get_distance(pair[i][0], pair[i][1], pair[j][0], pair[j][1]);
			if (min_distance > distance) // 更新最小值和对应点对
			{
				min_distance = distance;
				min_pair[0][0] = pair[i][0];
				min_pair[0][1] = pair[i][1];
				min_pair[1][0] = pair[j][0];
				min_pair[1][1] = pair[j][1];
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << min_pair[i][j] << ' ';
		}
		cout << endl;
	}
	for(int i=0;i<n;i++)
	delete []pair[i];
	delete []pair;
}