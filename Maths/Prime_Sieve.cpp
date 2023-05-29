#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    cout << "Range: " ;
    int x, num; 
    char y;
    cin >> x >> y >> num;
    bool *notPrime = new bool[num + 1];
    notPrime[0] = true;
    notPrime[1] = true;
    for (int i = 2; i <= num; i++) {
        notPrime[i] = false;
    }
    int max = sqrt(num);
    int sum = 0;
    for (int i = 2; i <= max; i++) {
        if (!notPrime[i]) {
            for (int j = i * i; j <= num; j += i) {
                notPrime[j] = 1;
            }
        }
    }
    for (int i = x; i <= num; i++)
        if (!notPrime[i]) {
            sum++;
            cout << i << ' ';
        }
    cout << endl<< "Total: " << sum;
	system("pause");
}
