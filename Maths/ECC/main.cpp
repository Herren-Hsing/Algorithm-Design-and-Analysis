#include "ecc.h"
#include "input.h"
// mingw32-make
int main()
{
	ecc e;
	int _p, _a, _b;
	while (1)
	{
		cout << "E_p(a,b):";
		string input;
		getline(cin, input);
		getPAB(input, _p, _a, _b);
		if (!isECC(_p, _a, _b))
		{
			cout << "E_" << _p << "(" << _a << "," << _b << ")"
				 << " is not elliptic curve." << endl;
		}
		else
		{
			cout << "E_" << _p << "(" << _a << "," << _b << ")"
				 << " is elliptic curve." << endl;
			break;
		}
	}
	e.init(_p, _a, _b);
	string input;
	while (getline(cin, input))
	{
		if (isdigit(input[0]))
		{
			int number = stoi(input);
			pair<int, int> coordinates = extractCoordinates(input);
			point p1;
			p1.x = coordinates.first;
			p1.y = coordinates.second;
			point res = e.mulPoint(p1, number);
			if (res.isInfinity)
				cout << 'O' << endl;
			else
				cout << "(" << res.x << ',' << res.y << ")" << endl;
		}
		else if (input.find("+") != string::npos)
		{
			pair<pair<int, int>, pair<int, int>> points = extractPoints(input);
			point p1, p2;
			p1.x = points.first.first;
			p1.y = points.first.second;
			p2.x = points.second.first;
			p2.y = points.second.second;
			point res = e.addPoint(p1, p2);
			if (res.isInfinity)
				cout << 'O' << endl;
			else
				cout << "(" << res.x << ',' << res.y << ")" << endl;
		}
		else if (input.find("#E_") != string::npos)
		{
			int ordp, orda, ordb;
			getECC(input, ordp, orda, ordb);
			cout << getECCOrder(ordp, orda, ordb) << endl;
		}
		else if (input.find("ord") != string::npos)
		{
			pair<int, int> coordinates = extractCoordinates(input);
			point p1;
			p1.x = coordinates.first;
			p1.y = coordinates.second;
			int order = e.getOrder(p1);
			cout << order << endl;
		}
		else if (input.find("all points") != string::npos)
		{
			int ordp, orda, ordb, num = 0;
			getECC(input, ordp, orda, ordb);
			point *pts = new point[3 * ordp];
			getAllPoint(ordp, orda, ordb, pts, num);
			for (int i = 0; i < num; i++)
			{
				if (pts[i].isInfinity)
				{
					cout << 'O' << ',';
				}
				else
				{
					cout << '(' << pts[i].x << ',' << pts[i].y << ')' << ',';
				}
			}
			cout << endl;
		}
		else if (input.find("(") != string::npos)
		{
			pair<int, int> coordinates = extractCoordinates(input);
			point p1;
			p1.x = coordinates.first;
			p1.y = coordinates.second;
			if (e.onECC(p1))
			{
				cout << input << " is on E_" << e.p << "(" << e.a << "," << e.b << ")" << endl;
			}
			else
			{
				cout << input << " is not on E_" << e.p << "(" << e.a << "," << e.b << ")" << endl;
			}
		}
		else if (input.find("END") != string::npos)
		{
			break;
		}
		else
		{
			cout << "ILEAGAL INPUT!" << endl;
			continue;
		}
	}
}
