#include <iostream>
using namespace std;
int get_Inverse(int a, int b)
{
	int c = a * b;
	bool isSwap = 0;
	int s0 = 1, t0 = 0, s1 = 0, t1 = 1;
	int r0 = a, r1 = b;
	int q1, s2, t2, r2;
	while (r1 != 0)
	{
		q1 = r0 / r1;
		s2 = s0 - q1 * s1;
		t2 = t0 - q1 * t1;
		r2 = r0 - q1 * r1;
		s0 = s1;
		t0 = t1;
		r0 = r1;
		s1 = s2;
		t1 = t2;
		r1 = r2;
	}
	return ((s0 + b) % b);
}
int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	int *b = new int[n];
	int *m = new int[n];
	int *M = new int[n];
	int *inverse_M = new int[n];
	int len = n;
	int index = 0;
	while (len--)
	{
		cout << " b_" << index << " = ";
		cin >> b[index++];
	}
	len = n;
	index = 0;
	while (len--)
	{
		cout << " m_" << index << " = ";
		cin >> m[index++];
	}
	int mul_m = 1;
	for (int i = 0; i < n; i++)
	{
		mul_m *= m[i];
	}
	for (int i = 0; i < n; i++)
	{
		M[i] = mul_m / m[i];
	}
	for (int i = 0; i < n; i++)
	{
		inverse_M[i] = get_Inverse(M[i], m[i]);
	}
	int res = 0, tmp;
	for (int i = 0; i < n; i++)
	{
		tmp = M[i] * inverse_M[i] * b[i];
		res += tmp;
	}
	cout << "x กิ " << res % mul_m << " (mod " << mul_m << ")";
	system("pause");
}