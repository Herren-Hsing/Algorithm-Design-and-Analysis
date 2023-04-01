#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void quickSort(int **a, int i, int j) // 快速排序
{
	if (j <= i || j <= 0)
		return;
	int m = i, n = j, s = a[m][0], t = a[m][1];
	// 依据第0列（开始时间）进行排序
	while (m < n)
	{
		while (m < n && a[n][0] >= s)
		{
			n--;
		}
		if (m < n)
		{
			a[m][0] = a[n][0];
			a[m++][1] = a[n][1];
		}
		while (m < n && a[m][0] < s)
		{
			m++;
		}
		if (m < n)
		{
			a[n][0] = a[m][0];
			a[n--][1] = a[m][1];
		}
	}
	a[m][0] = s;
	a[m][1] = t;
	// 经过这一轮的排序，m左侧都比它小，右侧都比它大
	quickSort(a, i, m - 1);
	quickSort(a, m + 1, j);
	// 再从m左右两侧分别进行排序
}
int main()
{
	int n;
	cin >> n;
	int **lectures = new int *[n];
	for (int i = 0; i < n; i++)
	{
		lectures[i] = new int[2];
		for (int j = 0; j < 2; j++)
		{
			cin >> lectures[i][j];
		}
	}
	quickSort(lectures, 0, n - 1);							   // 依据结束时间升序排序
	priority_queue<int, vector<int>, greater<int>> classrooms; // 需要优先队列升序存放教室的结束时间
	int index_of_lectures = 0;
	while (index_of_lectures != n)
	{
		if (!index_of_lectures) // 最初无教室
		{
			classrooms.push(lectures[0][1]);
			index_of_lectures++;
			continue;
		}
		if (lectures[index_of_lectures][0] < classrooms.top()) // 如果开始时间早于教室结束时间的最小值，需要开辟一个新教室
		{
			classrooms.push(lectures[index_of_lectures][1]);
		}
		else // 否则放到最早结束的教室，把其结束时间弹出，压入新的结束时间
		{
			classrooms.pop();
			classrooms.push(lectures[index_of_lectures][1]);
		}
		index_of_lectures++;
	}
	cout << classrooms.size();
}