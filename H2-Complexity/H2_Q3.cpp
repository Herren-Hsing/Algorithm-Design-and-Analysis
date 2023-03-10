#include <iostream>
using namespace std;
void target_sum_n2(int *a, int n, int t) // 时间复杂度为n^2的算法，两轮遍历，找到加和等于t的两个数
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] + a[j] == t)
			{
				cout << '(' << i << ',' << j << ')';
			}
		}
	}
	cout << endl;
}
void target_sum_nlogn(int *a, int n, int t) // 时间复杂度为nlogn的算法
{
	for (int i = 0; i < n - 1; i++) // 确定一个数字，在剩下的范围内用二分查找找到加和为t的另一个数字
	{
		int head = i + 1, tail = n - 1, half;
		while (head <= tail)
		{
			half = (head + tail) / 2;
			if (a[half] == t - a[i])
			{
				cout << '(' << i << ',' << half << ')';
				break;
			}
			else if (a[half] > t - a[i])
			{
				tail = half - 1;
			}
			else
			{
				head = half + 1;
			}
		}
	}
	cout << endl;
}
void target_sum_n(int *a, int n, int t) // 使用头尾两个指针寻找两数，比较两指针指向的数字加和与t
{
	int head = 0, tail = n - 1;
	while (head < tail)
	{
		if (a[head] + a[tail] == t) // 如果加和等于t，说明已找到二数；头后移，尾前移，继续寻找有无其他二数
		{
			cout << '(' << head << ',' << tail << ')';
			head++;
			tail--;
		}
		else if (a[head] + a[tail] > t) // 如果加和大于t，尾指针前移
		{
			tail--;
		}
		else // 如果加和小于t，头指针后移
		{
			head++;
		}
	}
}
int main()
{
	int n;
	cin >> n;
	int *array = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> array[i];
	}
	int T;
	cin >> T;
	target_sum_n2(array, n, T);
	target_sum_nlogn(array, n, T);
	target_sum_n(array, n, T);
	delete array;
	return 0;
}