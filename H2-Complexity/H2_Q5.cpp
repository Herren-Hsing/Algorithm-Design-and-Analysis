#include <iostream>
using namespace std;
void three_sum_n3(int *a, int n, int t) // 三层遍历，找到加和为t的三个数字
{
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = i + 1; j < n - 1; j++)
		{
			for (int k = j + 1; k < n; k++)
			{
				if (a[i] + a[j] + a[k] == t)
				{
					cout << '(' << i << ',' << j << ',' << k << ')';
				}
			}
		}
	}
	cout << endl;
}
// 以i为索引进行一层遍历，然后对剩余的元素，以j为索引遍历，然后在j后的元素中，用二分查找找到加上a[i]与a[j]和为t的元素
void three_sum_n2logn(int *a, int n, int t)
{
	for (int i = 0; i < n - 2; i++)
	{
		for (int j = i + 1; j < n - 1; j++)
		{
			int head = j + 1, tail = n - 1, half;
			while (head <= tail)
			{
				half = (head + tail) / 2;
				if (a[half] == t - a[i] - a[j])
				{
					cout << '(' << i << ',' << j << ',' << half << ')';
					break;
				}
				else if (a[half] > t - a[i] - a[j])
				{
					tail = half - 1;
				}
				else
				{
					head = half + 1;
				}
			}
		}
	}
	cout << endl;
}
// 以i为索引进行一层遍历，在剩余元素中通过头尾指针的方法找到加和为 t - a[i] 的两个数字
void three_sum_n2(int *a, int n, int t)
{
	for (int i = 0; i < n - 2; i++)
	{
		int head = i + 1, tail = n - 1;
		while (head < tail)
		{
			if (a[head] + a[tail] == t - a[i])
			{
				cout << '(' << i << ',' << head << ',' << tail << ')';
				head++;
				tail--;
			}
			else if (a[head] + a[tail] > t - a[i])
			{
				tail--;
			}
			else
			{
				head++;
			}
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
	three_sum_n3(array, n, T);
	three_sum_n2logn(array, n, T);
	three_sum_n2(array, n, T);
	delete array;
	return 0;
}