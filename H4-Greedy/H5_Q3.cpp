#include <iostream>
using namespace std;
int main()
{
	int n, e;
	cin >> n >> e;
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
		if (graph[n1 - 1][n2 - 1] != 0 && len >= graph[n1 - 1][n2 - 1])
			continue;
		graph[n1 - 1][n2 - 1] = len;
		graph[n2 - 1][n1 - 1] = len;
	}
	bool *picked = new bool[n]; // picked用来标记被选的顶点
	for (int i = 0; i < n; i++)
	{
		if (!i)
		{
			picked[i] = true; // 先选第0个顶点
			continue;
		}
		picked[i] = false;
	}
	int picked_num = 1;			 // 初始被选的点为1个
	int *distances = new int[n]; // distance用来存放i点到集合里的点的最短距离
	for (int i = 0; i < n; i++)
	{
		distances[i] = graph[0][i]; // 初始时，得到起点能访问节点的distance
	}
	int sum = 0;
	while (picked_num != n)
	{
		int min_dis = -1, picked_node = 0;
		for (int i = 0; i < n; i++)
		{
			// 遍历节点，得到下一个加入集合的节点，就是到集合的点的距离最短的点
			if (!picked[i]) // 遍历顶点，如果不在选中的集合里
			{
				if (distances[i] == 0) // 如果该点到集合里的点无路径，继续遍历
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
		if (distances[picked_node] == 0) // 图不联通，不存在最小生成树
		{
			sum = 0;
			break;
		}
		sum += distances[picked_node];
		for (int i = 0; i < n; i++)
		{
			if (!picked[i])
			{
				if (!graph[picked_node][i]) // 如果刚加入的点到该点无路径，不用更新
					continue;
				if ((graph[picked_node][i] < distances[i]) || (!distances[i])) // 如果新加入点到该点距离小或者原本集合的点到该点无路径，更新该点到集合的点的最短距离
				{
					distances[i] = graph[picked_node][i];
				}
			}
		}
	}
	cout << sum;
}
