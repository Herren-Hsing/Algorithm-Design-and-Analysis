#include <iostream>
using namespace std;
int main()
{
	int num, capacity;
	cin >> capacity>>num;
	int **goods = new int *[num];
	for (int i = 0; i < num; i++)
	{
		goods[i] = new int[2];
		for (int j = 0; j < 2; j++)
		{
			cin >> goods[i][j];
		}
	}
	int **list = new int *[num + 1];
	for (int i = 0; i < num + 1; i++)
	{
		list[i] = new int[capacity + 1];
		for (int j = 0; j < capacity + 1; j++)
		{
			list[i][j] = 0;
		}
	}
	for (int i = 1; i < num + 1; i++)
	{
		for (int j = 1; j < capacity + 1; j++)
		{
			if (goods[i - 1][0] <= j)
			{
				list[i][j] = max(list[i - 1][j], list[i - 1][j - goods[i - 1][0]] + goods[i - 1][1]);
			}
			else
			{
				list[i][j] = list[i - 1][j];
			}
		}
	}
	cout<<list[num][capacity];
}