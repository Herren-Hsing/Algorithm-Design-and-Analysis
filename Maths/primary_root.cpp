#include <iostream>
#include <iomanip>
using namespace std;
void getDivisors(int x, int &s, int *&a)
{
	int tmp;
	for (int i = 2; i <= x; i++)
	{
		tmp = 0;
		while (x % i == 0)
		{
			tmp++;
			x = x / i;
		}
		if (tmp != 0)
		{
			a[s] = i;
			s++;
		}
	}
}
int gcd(int a, int b)
{
	if (a < b)
		swap(a, b);
	while (a % b != 0)
	{
		int d = a % b;
		a = b;
		b = d;
	}
	return b;
}
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
int getPhi(int n)
{
	int res = n;
	int *a = new int[n];
	int len = 0;
	getDivisors(n, len, a);
	for (int i = 0; i < len; i++)
		res = res - res / a[i];
	return res;
}
int getG(int n, int phi)
{
	int *a = new int[phi];
	int len = 0;
	getDivisors(phi, len, a);
	for (int i = 2; i < n; i++)
	{
		if (gcd(i, n) != 1)
			continue;
		bool flag = 0;
		for (int j = 0; j < len; j++)
		{
			if (square_and_multiply(i, phi / a[j], n) == 1)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	cout << "Please input n(n>0): ";
	int n;
	cin >> n;
	int phi = getPhi(n);
	int g = getG(n, phi);
	cout << "The main primitive root of " << n << ": g = " << g << endl;
	cout << "The ind_table of " << n << " based on g = " << g << " is: " << endl;
	int unit = n % 10, decade = n / 10;
	int **table = new int *[decade + 1];
	for (int i = 0; i < decade + 1; i++)
	{
		table[i] = new int[10];
	}
	for (int i = 0; i < decade + 1; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			table[i][j] = -1;
		}
	}
	for (int i = 0; i < phi; i++)
	{
		int res = square_and_multiply(g, i, n);
		int decade_of_res = res / 10;
		int unit_of_res = res % 10;
		table[decade_of_res][unit_of_res] = i;
	}
	cout << "      "; // 一些输出格式控制语句
	for (int i = 0; i < 10; i++)
	{
		cout << right
			 << setw(4)
			 << fixed << i << ' ';
	}
	cout << endl;
	for (int i = 0; i < decade + 1; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j == 0)
			{
				cout << right
					 << setw(4)
					 << fixed << i << "  ";
			}
			if (table[i][j] == -1)
			{
				cout << "   - ";
				continue;
			}
			cout << right
				 << setw(4)
				 << fixed << table[i][j] << ' ';
		}
		cout << endl;
	}
	system("pause");
}