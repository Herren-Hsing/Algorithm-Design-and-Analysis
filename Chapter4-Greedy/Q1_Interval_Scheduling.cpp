#include <iostream>
using namespace std;
void quickSort(int **a, int i, int j) // 快速排序
{
	if (j <= i || j <= 0)
		return;
	int m = i, n = j, s = a[m][1], t = a[m][0];
	// 依据第一列（结束时间）进行排序
	while (m < n)
	{
		while (m < n && a[n][1] >= s)
		{
			n--;
		}
		if (m < n)
		{
			a[m][1] = a[n][1];
			a[m++][0] = a[n][0];
		}
		while (m < n && a[m][1] < s)
		{
			m++;
		}
		if (m < n)
		{
			a[n][1] = a[m][1];
			a[n--][0] = a[m][0];
		}
	}
	a[m][1] = s;
	a[m][0] = t;
	quickSort(a, i, m - 1);
	quickSort(a, m + 1, j);
}
bool is_Compatible(int a1, int a2, int b1, int b2)
// a1,a2是选出来的起始时间，b1,b2是剩余元素的起始时间，因为排序过，a2肯定小于b2，不相容时只需a2小于b1
{
	if (a2 <= b1)
	{
		return true;
	}
	return false;
}
int main()
{
	int n;
	cin >> n;
	int **schedules = new int *[n];
	for (int i = 0; i < n; i++)
	{
		schedules[i] = new int[3];
		for (int j = 0; j < 2; j++)
		{
			cin >> schedules[i][j];
		}
		schedules[i][2] = 1; // 0表示被删除，1表示存在
	}
	quickSort(schedules, 0, n - 1); // 依据结束时间升序排序
	int maximum = 0, index = 0;
	while (index != n)
	{
		if (!schedules[index][2]) // 跳过被删除的点
		{
			index++;
			continue;
		}
		// 选中第index个元素
		maximum++;
		for (int i = 0; i < n; i++)
		{
			if (!schedules[i][2])
				continue;
			// 比较选出来的元素与集合中剩余的存在的元素
			if (!is_Compatible(schedules[index][0], schedules[index][1], schedules[i][0], schedules[i][1]))
			{
				schedules[i][2] = 0;
				// 如果某元素与选出来的元素不相容，就删掉该元素
			}
		}
		index++;
	}
	cout << maximum;
}