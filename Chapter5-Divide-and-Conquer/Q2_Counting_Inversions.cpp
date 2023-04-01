#include <iostream>
using namespace std;
int merge_and_count(int *&list, int a1, int a2, int b1, int b2, int n)
{
	int res = 0;
	int *merge_list = new int[n]; // 储存排序后的列表
	int index = a1, i = a1, j = b1;
	// 合并两个部分，就是合并两个有序表的算法
	while (i <= a2 && j <= b2)
	{
		if (list[i] <= list[j])
		{
			merge_list[index++] = list[i++];
		}
		else
		{
			merge_list[index++] = list[j++];
			res += (j - index);
			// 如果前面元素大于后面元素，则后者元素与前者元素构成逆序对，后者元素与它们之间的任何一个元素都构成逆序对
		}
	}
	while (i <= a2)
	{
		merge_list[index++] = list[i++];
	}
	while (j <= b2)
	{
		merge_list[index++] = list[j++];
	}
	// 把merge_list数组中的元素复制回原始数组中
	for (int k = a1; k <= b2; k++)
	{
		list[k] = merge_list[k];
	}
	return res;
	delete[] merge_list;
}
int sort_and_count(int *&list, int i, int j, int n)
{
	if (i >= j)
		return 0;
	int sum = 0;
	// 把列表划分成两半，对每部分排序并求内部逆序对的数量，然后合并两部分，求之间的逆序对数
	int mid = (i + j) / 2;
	sum += sort_and_count(list, i, mid, n);
	sum += sort_and_count(list, mid + 1, j, n);
	sum += merge_and_count(list, i, mid, mid + 1, j, n);
	return sum;
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
	cout << sort_and_count(list, 0, n - 1, n);
	delete[] list;
}