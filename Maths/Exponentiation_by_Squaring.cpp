#include <iostream>
using namespace std;
int square_and_multiply(int a, int n, int m)
{
	int res = 1;
	int binary[32] = {0};
	int length = 0;
	while (n)
	{
		binary[length++] = n & 1;
		n >>= 1;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		res = (res * res) % m;
		if (binary[i])
		{
			res = (res * a) % m;
		}
	}
	return res;
}
int main()
{
	cout << "Calculater a n(mod m)..." << endl
		 << "Please input:" << endl
		 << "  a = ";
	int a, n, m, res;
	cin >> a;
	cout << "  n = ";
	cin >> n;
	cout << "  m = ";
	cin >> m;
	res = square_and_multiply(a, n, m);
	cout << a << '^' << n << "(mod " << m << ')' << " = " << res;
	system("pause");
}