#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int n, m, a, b;
	int min;
	cin >> n >> m >> a >> b;
	if (m * a <= b) // 如果多程票的里程用单程票买更便宜
	{
		min = n * a; // 全买单程票
	}
	else // 如果多程票的里程用单程票买更贵，有两种情况，全买多程或者单多混合
	{
		int bonly = ceil(double(n) / double(m)) * b; // 全买多程，票数是n/m向上取整
		int mix = n / m * b + (n - n / m * m) * a;	 // 多程票数是n/m向下取整，其余买单程
		min = bonly > mix ? mix : bonly;			 // 比较二者，选最优
	}
	cout << min;
	return 0;
}