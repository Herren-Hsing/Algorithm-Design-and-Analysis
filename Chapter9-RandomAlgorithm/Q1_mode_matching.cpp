#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int N = 100;
int Prime[N];

// 素数筛列出给定范围内的全部素数
int getPrime()
{
	bool *notPrime = new bool[N + 1];
	notPrime[0] = true;
	notPrime[1] = true;
	for (int i = 2; i <= N; i++)
	{
		notPrime[i] = false;
	}
	int max = sqrt(N);
	for (int i = 2; i <= max; i++)
	{
		if (!notPrime[i])
		{
			for (int j = i * i; j <= N; j += i)
			{
				notPrime[j] = 1;
			}
		}
	}
	int sum = 0;
	for (int i = 2; i <= N; i++)
	{
		if (!notPrime[i])
		{
			Prime[sum++] = i;
		}
	}
	return sum;
}
int getI(string s, int start, int p, int len) // 计算Ip(s_i)
{
	int I = 0, two = 1;
	for (int i = 0; i < len; i++)
	{
		I += two * (s[start + len - 1 - i] - 'a');
		two *= 2;
	}
	return (I + p) % p;
}
int main()
{
	int num = getPrime();
	srand(time(0));
	int randomIndex = rand() % num;
	int p = Prime[randomIndex]; // 随机生成一个素数
	string x, y;
	cin >> x >> y;
	int len_x = x.length(), len_y = y.length(), res = -1;

	// 计算wp、Ip(y)、Ip(x)
	int wp = int(pow(2, len_y)) % p;
	wp = wp < 0 ? wp + p : wp;
	int I_y = getI(y, 0, p, len_y);
	I_y = I_y < 0 ? I_y + p : I_y;
	int I_x_i = getI(x, 0, p, len_y);
	I_x_i = I_x_i < 0 ? I_x_i + p : I_x_i;

	for (int i = 0; i <= len_x - len_y + 1; i++)
	{
		// 可能找到了匹配子串
		if (I_x_i == I_y)
		{
			res = i;
			break;
		}

		// 迭代计算Ip(x_i+1)
		int temp = (2 * I_x_i - wp * (x[i] - 'a') + (x[i + len_y] - 'a')) % p;
		I_x_i = temp < 0 ? temp + p : temp;
	}

	cout << res;

	return 0;
}