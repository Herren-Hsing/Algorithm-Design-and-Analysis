#include <iostream>
using namespace std;
struct point
{
	int x;
	int y;
	bool isInfinity = false;
};
class ecc
{
public:
	int p;
	int a;
	int b;

	void init(int _p, int _a, int _b);
	bool onECC(point pt);
	point addPoint(point pt1, point pt2);
	point mulPoint(point pt, int n);
	int getOrder(point pt);
};
bool isPrime(int n);
bool isECC(int _p, int _a, int _b);
int legendreSymbol(int a, int p);
void getAllPoint(int p, int a, int b, point *pts, int &num);
int getECCOrder(int p, int a, int b);
int getInverse(int a, int p);
int square_and_multiply(int a, int n, int m);
int getSolution(int a, int p);