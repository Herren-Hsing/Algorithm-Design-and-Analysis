#include <iostream>
using namespace std;
int main()
{
     int x;
     cout << "Please input n(n>0): ";
     cin >> x;
     cout << x << "=";
     int tmp;
     int* a = new int[x];
     int* b = new int[x];
     int s = 0;
     for (int i = 2; i <= x; i++) {
          tmp = 0;
          while (x % i == 0) {
               tmp++;
               x = x / i;
          }
          if (tmp != 0) {
               a[s] = i;
               b[s] = tmp;
               s++;
          }
     }
     for (int i = 0; i < s; i++) {
          if (i != 0)
               cout << '*';
          cout << a[i] << "^" << b[i];
     }
	 system("pause");
}         
