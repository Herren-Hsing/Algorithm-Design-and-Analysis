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
int main()
{
	int n;
	cin >> n;
	int **jobs = new int *[n];
	for (int i = 0; i < n; i++) // 第一列是持续时间，第二列是ddl
	{
		jobs[i] = new int[2];
		for (int j = 0; j < 2; j++)
		{
			cin >> jobs[i][j];
		}
	}
	quickSort(jobs, 0, n - 1); // 依据ddl升序排序
	int sum_of_delayed_time = 0;
	int actual_time = 0;
	int index_of_jobs = 0;
	while (index_of_jobs != n)
	{
		actual_time += jobs[index_of_jobs][0];
		if (actual_time > jobs[index_of_jobs][1]) // 比较实际完成时间与ddl时间，如果晚于，总拖延时间加上它们的差
		{
			sum_of_delayed_time = sum_of_delayed_time - jobs[index_of_jobs][1] + actual_time;
		}
		index_of_jobs++;
	}
	cout << sum_of_delayed_time;
}