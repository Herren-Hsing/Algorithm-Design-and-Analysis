#include <iostream>
#include <string>
#include <regex>
using namespace std;
void getPAB(string input, int &_p, int &_a, int &_b);
pair<int, int> extractCoordinates(const string &input);
pair<pair<int, int>, pair<int, int>> extractPoints(const string &input);
void getECC(string input, int &p, int &a, int &b);