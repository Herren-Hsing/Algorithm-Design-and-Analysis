#include <iostream>
using namespace std;
int main()
{
	int m, n;
	cin >> n >> m;
	int *a = new int[n];
	int *b = new int[m];
	int *res = new int[m + n]; // 储存合并结果
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < m; i++)
	{
		cin >> b[i];
	}
	int index_of_a = 0, index_of_b = 0, index_of_res = 0; // 索引
	while (index_of_a != n && index_of_b != m)			  // 直到遍历完一个序列时，循环结束
	{
		if (a[index_of_a] < b[index_of_b]) // 如果a元素小于b，把a的元素放入res，调整索引
		{
			res[index_of_res++] = a[index_of_a++];
		}
		else if (a[index_of_a] > b[index_of_b]) // 如果b元素小于a，把b的元素放入res，调整索引
		{
			res[index_of_res++] = b[index_of_b++];
		}
		else // 二者相等，都放进去
		{
			res[index_of_res++] = b[index_of_b++];
			res[index_of_res++] = a[index_of_a++];
		}
	}
	// 最后有可能b未遍历完或者a未遍历完，就把没遍历完的剩余元素都放入res
	while (index_of_b != m)
	{
		res[index_of_res++] = b[index_of_b++];
	}
	while (index_of_a != n)
	{
		res[index_of_res++] = a[index_of_a++];
	}
	for (int i = 0; i < m + n; i++)
	{
		cout << res[i] << ' ';
	}
	delete a;
	delete b;
	delete res;
	return 0;
}