#include <iostream>
using namespace std;
int main()
{
	int a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	int c = a * b;
	bool isSwap = 0;
	if (a < b)
	{
		swap(a, b);
		isSwap = 1;
	}
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
	cout << "gcd(a,b) = " << r0 << endl
		 << "lcm(a,b) = " << a * b / r0 << endl
		 << "a^(-1) = " << (isSwap ? ((t0 + a) % a) : ((s0 + b) % b)) << "(mod " << (isSwap ? a : b) << ")" << endl
		 << "b^(-1) = " << (isSwap ? ((s0 + b) % b) : ((t0 + a) % a)) << "(mod " << (isSwap ? b : a) << ")" << endl;
	system("pause");
}
