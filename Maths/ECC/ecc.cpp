#include "ecc.h"
#include <cmath>
bool isPrime(int n)
{
	if (n < 2)
	{
		return false;
	}
	if (n % 2 == 0)
	{
		return false;
	}
	for (int i = 3; i <= sqrt(n); i += 2)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}
bool isECC(int _p, int _a, int _b)
{
	if (_p <= 3)
		return false;
	if (!isPrime(_p))
		return false;
	int delta = 4 * _a * _a * _a + 27 * _b * _b;
	return delta != 0;
}
int getInverse(int a, int p)
{
	int s0 = 1, t0 = 0, s1 = 0, t1 = 1;
	int r0 = a, r1 = p;
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
	return (s0 + p) % p;
}
void ecc::init(int _p, int _a, int _b)
{
	ecc::p = _p;
	ecc::a = _a;
	ecc::b = _b;
}
bool ecc::onECC(point pt)
{
	if (pt.isInfinity)
		return true;
	int left = (pt.y * pt.y) % p;
	int right = (pt.x * pt.x * pt.x + ecc::a * pt.x + ecc::b) % p;
	return left == right;
}
point ecc::addPoint(point pt1, point pt2)
{
	point pt3 = {0, 0};
	if ((!onECC(pt1)) || (!onECC(pt2)))
	{
		cout << "This point is not on the elliptic curve.";
		return pt3;
	}

	if ((pt1.x == pt2.x) && (pt1.y != pt2.y))
	{
		pt3.isInfinity = true;
		return pt3;
	}
	if (pt1.isInfinity || pt2.isInfinity)
	{
		pt3 = pt1.isInfinity ? pt2 : pt1;
		return pt3;
	}
	int k, k1, k2, k2Inverse;
	if (pt1.x == pt2.x)
	{
		k1 = (3 * pt1.x * pt1.x + ecc::a) % ecc::p;
		k2 = (2 * pt1.y) % ecc::p;
		k2Inverse = getInverse(k2, p);
		k = k1 * k2Inverse % ecc::p;
	}
	else
	{
		k1 = (pt2.y - pt1.y) % ecc::p;
		k2 = (pt2.x - pt1.x) % ecc::p;
		if (k1 < 0)
			k1 += ecc::p;
		if (k2 < 0)
			k2 += ecc::p;
		k2Inverse = getInverse(k2, p);
		k = k1 * k2Inverse % ecc::p;
	}
	pt3.x = k * k - pt1.x - pt2.x;
	pt3.y = k * (pt1.x - pt3.x) - pt1.y;
	pt3.x %= ecc::p;
	pt3.y %= ecc::p;
	if (pt3.x < 0)
	{
		pt3.x += ecc::p;
	}
	if (pt3.y < 0)
	{
		pt3.y += ecc::p;
	}
	return pt3;
}

point ecc::mulPoint(point pt, int n)
{
	point res = {0, 0};
	if (!onECC(pt))
	{
		cout << "This point is not on the elliptic curve.";
		return res;
	}
	int binary[32] = {0};
	int length = 0;
	while (n)
	{
		binary[length++] = n & 1;
		n >>= 1;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		if (i == length - 1)
		{
			res = pt;
			continue;
		}
		res = ecc::addPoint(res, res);
		if (binary[i])
		{
			res = ecc::addPoint(res, pt);
		}
	}
	return res;
}
int ecc::getOrder(point pt)
{
	if (!onECC(pt))
	{
		cout << "This point is not on the elliptic curve." << endl;
		return 0;
	}
	point t = pt;
	int order = 1;
	while (order++)
	{
		t = ecc::addPoint(t, pt);
		if (t.isInfinity)
		{
			break;
		}
	}
	return order;
}
int legendreSymbol(int a, int p)
{
	int q = a % p;
	if (q == 0)
	{
		return 0;
	}
	else if (q == 1)
	{
		return 1;
	}
	else if (q == 2)
	{
		if (p % 8 == 1 || p % 8 == 7)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if (q == -1)
	{
		if (p % 2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (q % 2 == 0)
	{
		return legendreSymbol(2, p) * legendreSymbol(q / 2, p);
	}
	else
	{
		if ((p - 1) * (q - 1) / 4 % 2 == 0)
		{
			return legendreSymbol(p % q, q);
		}
		else
		{
			return -legendreSymbol(p % q, q);
		}
	}
}
int getECCOrder(int p, int a, int b)
{
	if (!isECC(p, a, b))
	{
		cout << "INVAILD ECC" << endl;
		return -1;
	}
	int num = 1;
	for (int i = 0; i < p; i++)
	{
		int value = i * i * i + a * i + b;
		if (legendreSymbol(value, p) == 0)
		{
			num++;
		}
		else if (legendreSymbol(value, p) == 1)
		{
			num += 2;
		}
	}
	return num;
}
void getAllPoint(int p, int a, int b, point *pts, int &num)
{
	if (!isECC(p, a, b))
	{
		cout << "INVAILD ECC" << endl;
		return;
	}
	pts[num++].isInfinity = 1;
	for (int i = 0; i < p; i++)
	{
		int value = (i * i * i + a * i + b) % p;
		if (legendreSymbol(value, p) == 0)
		{
			pts[num].x = i;
			pts[num].y = 0;
			num++;
		}
		else if (legendreSymbol(value, p) == 1)
		{
			int solution = getSolution(value, p);
			pts[num].x = i;
			pts[num].y = solution;
			num++;
			pts[num].x = i;
			pts[num].y = p - solution;
			num++;
		}
	}
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
int getSolution(int a, int p)
{
	if (a == 1)
		return 1;

	int b = 1;
	while (legendreSymbol(b, p) != -1)
	{
		b++;
	}

	int q = (p - 1) / 2;
	int s = 0;
	while (q % 2 == 0)
	{
		q /= 2;
		s++;
	}

	int c = square_and_multiply(b, q, p);
	int x = square_and_multiply(a, (q + 1) / 2, p);
	int y = square_and_multiply(a, q, p);
	int r = s;

	if (y % p == 1)
		return x;
	else
	{
		int i = 0;
		while (y % p != 1)
		{
			int temp = square_and_multiply(y, pow(2, i + 1), p);
			i++;
			if (temp % p == 1)
			{
				int m = square_and_multiply(c, pow(r - i - 1, 2), p);
				x = x * m % p;
				c = m * m % p;
				y = y * c % p;
				r = i;
				i = 0;
			}
		}
		return x;
	}
}