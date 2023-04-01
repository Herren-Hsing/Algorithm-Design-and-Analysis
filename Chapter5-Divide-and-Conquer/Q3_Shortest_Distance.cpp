#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
bool cmp_x(const vector<double> &a, const vector<double> &b) // 自定义排序规则，按x升序排序
{
	return a[0] < b[0];
}
bool cmp_y(const vector<double> &a, const vector<double> &b) // 自定义排序规则，按y升序排序
{
	return a[1] < b[1];
}
double get_distance(double x1, double y1, double x2, double y2) // 两点间距离的平方
{
	double res = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	return res;
}
double closet_pair(vector<vector<double>> pos, int start, int end)
{
	if (end - start == 1) // 如果只有两个点，返回两点间距离
	{
		return get_distance(pos[start][0], pos[start][1], pos[end][0], pos[end][1]);
	}
	if (end - start == 2) // 如果只有三个点，两两计算距离，返回最小值
	{
		double d1 = get_distance(pos[start][0], pos[start][1], pos[start + 1][0], pos[start + 1][1]);
		double d2 = get_distance(pos[start + 1][0], pos[start + 1][1], pos[end][0], pos[end][1]);
		double d3 = get_distance(pos[start][0], pos[start][1], pos[end][0], pos[end][1]);
		return min(min(d1, d2), d3);
	}
	int mid = (start + end) / 2;
	double dis1 = closet_pair(pos, start, mid);	  // 左半部分求最短距离
	double dis2 = closet_pair(pos, mid + 1, end); // 右半部分求最短距离
	double dis = min(dis1, dis2);				  // 二者取最短
	vector<vector<double>> left, right;
	// 以mid为中线，收集左右两边距离中线距离不远于dis的点
	for (int i = 0; i < pos.size(); i++)
	{
		if (i <= mid && pos[mid][0] - pos[i][0] <= dis)
		{
			left.push_back(pos[i]);
		}
		else if (i > mid && pos[i][0] - pos[mid][0] <= dis)
		{
			right.push_back(pos[i]);
		}
	}
	// 两边分别按y升序排序
	sort(left.begin(), left.end(), cmp_y);
	sort(right.begin(), right.end(), cmp_y);
	for (int i = 0; i < left.size(); i++)
	{
		int index = 0;
		// 对左边的每个点，在右边按y升序排列的点中找到与之纵向差小于等于dis的第一个点
		for (int j = 0; j < right.size(); j++)
		{
			if (right[j][1] >= left[i][1] - dis)
			{
				index = j;
				break;
			}
		}
		// 从该点开始找6个点，每个点分别计算距离，如果小于dis，更新dis
		for (int j = index; j < right.size() && j < index + 6; j++)
		{
			double new_dis = get_distance(left[i][0], left[i][1], right[j][0], right[j][1]);
			if (new_dis < dis)
			{
				dis = new_dis;
			}
		}
	}
	return dis;
}
int main()
{
	int n;
	cin >> n;
	vector<vector<double>> pos(n); // 存每个点坐标
	for (int i = 0; i < n; i++)
	{
		pos[i].resize(2);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> pos[i][j];
		}
	}
	sort(pos.begin(), pos.end(), cmp_x); // 将每个点坐标按x升序排序
	cout << closet_pair(pos, 0, n - 1);
}