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
     if (a < b)
          swap(a, b);
     while (a % b != 0) {
          int d = a % b;
          a = b;
          b = d;
     }
     cout << "gcd(a,b) = " << b << endl;
     cout << "lcm(a,b) = " << c / b;
	 system("pause");
}                
