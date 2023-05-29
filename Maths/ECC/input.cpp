#include "input.h"
void getPAB(string input, int &_p, int &_a, int &_b)
{
	size_t p_pos = input.find("p=");
	size_t a_pos = input.find("a=");
	size_t b_pos = input.find("b=");

	if (p_pos != string::npos && a_pos != string::npos && b_pos != string::npos)
	{
		string p_value = input.substr(p_pos + 2, a_pos - (p_pos + 2));
		string a_value = input.substr(a_pos + 2, b_pos - (a_pos + 2));
		string b_value = input.substr(b_pos + 2);

		_p = stoi(p_value);
		_a = stoi(a_value);
		_b = stoi(b_value);
	}
}
pair<int, int> extractCoordinates(const string &input)
{
	regex pattern(R"((?:\()(\d+),(\d+)(?:\)))");
	smatch matches;

	if (regex_search(input, matches, pattern))
	{
		if (matches.size() == 3)
		{
			int x = stoi(matches[1].str());
			int y = stoi(matches[2].str());
			return make_pair(x, y);
		}
	}
	cout << "ILEAGAL INPUT!" << endl;
	return make_pair(-1, -1);
}

pair<pair<int, int>, pair<int, int>> extractPoints(const string &input)
{
	size_t plusPos = input.find('+');
	string point1Str = input.substr(0, plusPos);
	string point2Str = input.substr(plusPos + 1);

	pair<int, int> point1 = extractCoordinates(point1Str);
	pair<int, int> point2 = extractCoordinates(point2Str);

	return make_pair(point1, point2);
}
void getECC(string input, int &p, int &a, int &b)
{
	size_t startPos = input.find('_') + 1; // 查找下划线的位置
	size_t endPos = input.find('(');	   // 查找左括号的位置
	p = stoi(input.substr(startPos, endPos - startPos));

	// 提取数字1和23
	startPos = input.find('(') + 1; // 查找左括号的位置
	endPos = input.find(',');		// 查找逗号的位置
	a = stoi(input.substr(startPos, endPos - startPos));

	startPos = endPos + 1;	  // 更新起始位置为逗号后的位置
	endPos = input.find(')'); // 查找右括号的位置
	b = stoi(input.substr(startPos, endPos - startPos));
}