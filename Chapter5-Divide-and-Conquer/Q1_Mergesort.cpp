#include <iostream>
using namespace std;
void merge_sort(int *&list, int i, int j, int n)
{
	if (i >= j)
		return;
	// 把列表分成两部分，两部分分别归并排序
	int mid = (i + j) / 2;
	merge_sort(list, i, mid, n);
	merge_sort(list, mid + 1, j, n);
	// 合并两个部分，就是合并两个有序表的算法
	int *merge_list = new int[n];
	int index = i, index_a = i, index_b = mid + 1;
	while (index_a <= mid && index_b <= j)
	{
		if (list[index_a] <= list[index_b])
		{
			merge_list[index++] = list[index_a++];
		}
		else
		{
			merge_list[index++] = list[index_b++];
		}
	}
	while (index_a <= mid)
	{
		merge_list[index++] = list[index_a++];
	}
	while (index_b <= j)
	{
		merge_list[index++] = list[index_b++];
	}
	// 将合并好的列表拷贝到原始列表中
	for (int k = i; k <= j; k++)
	{
		list[k] = merge_list[k];
	}
	delete[] merge_list;
}
int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> list[i];
	}
	merge_sort(list, 0, n - 1, n);
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << ' ';
	}
	delete[] list;
}