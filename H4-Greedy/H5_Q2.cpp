#include <iostream>
using namespace std;
int main()
{
	int n, e, s;
	cin >> n >> e >> s;
	// 邻接矩阵保存图，将图保存时索引从0开始，将路径权值存放在矩阵对应位置，无路径位置值为0
	int **graph = new int *[n];
	for (int i = 0; i < n; i++)
	{
		graph[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graph[i][j] = 0;
		}
	}
	int n1, n2, len;
	for (int i = 0; i < e; i++)
	{
		cin >> n1 >> n2 >> len;
		graph[n1 - 1][n2 - 1] = len;
	}
	int *distances = new int[n]; // distance用来存放起点到i点的最短距离
	for (int i = 0; i < n; i++)
	{
		distances[i] = graph[s - 1][i]; // 初始时，得到起点能访问节点的distance
	}
	bool *picked = new bool[n]; // picked用来标记被选的顶点
	for (int i = 0; i < n; i++)
	{
		if (i == s - 1)
		{
			picked[i] = true; // 起点被选
			continue;
		}
		picked[i] = false;
	}
	int picked_num = 1;		// 初始被选的点为1个
	while (picked_num != n) // 最后所有点被选
	{
		int min_dis = -1, picked_node = 0;
		for (int i = 0; i < n; i++)
		{
			// 遍历节点，得到下一个加入集合的节点，就是到起始点距离最短的点
			if (!picked[i]) // 遍历顶点，如果不在选中的集合里
			{
				if (distances[i] == 0) // 如果起始点到该点无路径，继续遍历
					continue;
				// 如果有路径，且小于min，更新min值和被选节点的序号
				if (min_dis == -1)
				{
					min_dis = distances[i];
					picked_node = i;
				}
				else
				{
					if (min_dis > distances[i])
					{
						min_dis = distances[i];
						picked_node = i;
					}
				}
			}
		}
		picked[picked_node] = true;
		picked_num++;
		// 接下来，需要更新其他点到起始点的最短路径
		for (int i = 0; i < n; i++)
		{
			if (!picked[i])
			{
				if (!graph[picked_node][i]) // 如果刚加入的点到该点无路径，不用更新
					continue;
				int update = distances[picked_node] + graph[picked_node][i]; // 新路径是从起始点到刚加入点的距离加上刚加入点到该点的距离
				if (update < distances[i] || distances[i] == 0)				 // 如果新路径距离小或者原本起点到该点无路径，更新该点到起点的最短距离
				{
					distances[i] = update;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << distances[i] << ' ';
	delete[] picked;
	delete[] distances;
	for (int i = 0; i < n; i++)
	{
		delete[] graph[i];
	}
	delete[] graph;
}