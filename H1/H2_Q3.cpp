#include <iostream>
using namespace std;
int main()
{
	int m;
	cin >> m;
	int res;
	if (m >= 0)
	{
		res = m; // 余额大于等于0，不管去掉哪一位，都会变小
	}
	else
	{
		int k1 = m;						   // k1是不做任何处理的结果
		int k2 = m / 10, s2 = m % 10;	   // k2是去掉最后一位的结果，s2是最后一位
		int n = m / 100, k3 = n * 10 + s2; // n是去掉最后两位的值，n*10+s2是去掉倒数第二位的处理结果
		res = max(max(k1, k2), k3);		   // 找到最大值
	}
	cout << res;
	return 0;
}