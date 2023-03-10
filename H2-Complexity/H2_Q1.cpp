#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int *array = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> array[i];
	}
	int x;
	cin >> x;
	int pos_of_x;					  // x在数组中的位置
	int head = 0, tail = n - 1, half; // head是一段数据的头，tail是尾，half是一半
	while (head <= tail)			  // 待查找的序列头大于尾时，结束循环
	{
		half = (head + tail) / 2; // 每轮的half都在中间位置
		if (array[half] == x)	  // 找到x
		{
			pos_of_x = half;
			break;
		}
		else if (array[half] > x) // 中间数据大于x，再去左半部分查找x，待查找序列尾成为half-1
		{
			tail = half - 1;
		}
		else // 中间数据小于x，再去右半部分查找x，待查找序列头成为half+1
		{
			head = half + 1;
		}
	}
	if (array[half] != x) // 上述循环结束后，如果有x，array[half]一定等于x；如果不等于，说明序列中不存在x
		pos_of_x = -1;
	cout << pos_of_x;
	delete array;
	return 0;
}