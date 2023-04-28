#include <iostream>
using namespace std;
void get_result(int n, int m, int *symbol, int *res)
{
	// 如果已经选择完n个数字，输出结果并返回
	if (m < 1)
	{
		for (int i = 0; i < n; i++)
		{
			cout << res[i] << ' ';
		}
		cout << endl;
		return;
	}
	// 从未被使用的数字中选择一个
	for (int i = 0; i < n; i++)
	{
		if (!symbol[i])                        // 如果数字i+1没有被使用
		{
			res[n - m] = i + 1;				   // 将数字i+1加入结果数组
			symbol[i] = 1;					   // 将数字i+1标记为已使用
			get_result(n, m - 1, symbol, res); // 继续递归，选择下一个数字
			symbol[i] = 0;					   // 恢复数字i+1的标记为未使用
		}
	}
}
int main()
{
	int n;
	cin >> n;
	int *symbol = new int[n]; // 标记数字有无被使用过
	for (int i = 0; i < n; i++)
	{
		symbol[i] = 0;
	}
	int *res = new int[n]; // 存放结果
	get_result(n, n, symbol, res);
}