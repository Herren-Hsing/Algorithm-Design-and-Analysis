#include <iostream>
#include <queue>
using namespace std;
void BFS(int n, int start, int **array, int **&layer)
{
	int layer_index = 0; // 层数索引
	queue<int> nodes;	 // 借助队列实现BFS
	// 初始化初始节点信息
	layer[0][start] = layer_index++;		   // 起始位于第0层
	layer[1][start] = 1;					   // 起始节点已被访问
	layer[2][start] = 0;					   // 初始节点为0
	nodes.push(start);						   // 将起始节点入队列
	int cur_num = 1, next_num = 0, color = -1; // cur_num表示当前层未访问的点数，next_num表示下一层的点数，color表示颜色
	while (!nodes.empty())					   // 队列不空时循环
	{
		int cur_node = nodes.front();
		nodes.pop(); // 弹出队首节点
		cur_num--;	 // 当前层未访问的点数减一
		for (int j = 0; j < n; j++)
		{
			if (array[cur_node][j] && (!layer[1][j])) // 遍历所有节点，如果有未访问过的节点与该节点之间有边
			{
				layer[0][j] = layer_index; // 得到该节点的层数
				layer[1][j] = 1;		   // 该节点已经被访问
				layer[2][j] = color;	   // 绘制颜色
				nodes.push(j);			   // 该节点入队
				next_num++;				   // 该节点相对于正在访问的节点是下一层的，所以下一层节点数加一
			}
		}
		if (!cur_num) // 当某层节点访问完后，下一层成为本层，层数索引加一，一层结束后换颜色
		{
			cur_num = next_num;
			next_num = 0;
			layer_index++;
			color = ~color;
		}
	}
}
bool is_bipartite(int m, int **layer, int **edges)
{
	for (int i = 0; i < m; i++)
	{
		if (layer[2][edges[i][0]] == layer[2][edges[i][1]]) // 如果一边的两顶点颜色相同，说明不是
			return false;
	}
	return true;
}
int main()
{
	int n, m, start = 0;
	cin >> n >> m;
	int **array = new int *[n]; // 邻接矩阵表示图
	for (int i = 0; i < n; i++)
	{
		array[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			array[i][j] = 0;
		}
	}
	int **edges = new int *[m]; // 存放所有的边
	for (int i = 0; i < m; i++)
	{
		edges[i] = new int[2];
	}
	int index_of_edge = 0;
	int input1, input2, edge = m;
	while (edge--) // 获取边，并将矩阵内相应位置值置为1
	{
		cin >> input1 >> input2;
		edges[index_of_edge][0] = input1;
		edges[index_of_edge++][1] = input2;
		array[input1][input2] = 1;
		array[input2][input1] = 1;
	}
	int **layer = new int *[3]; // layer第一行表示每个点的层序，第二层表示该点有无被访问过，第三层表示该点的颜色，0和-1标记两种颜色
	for (int i = 0; i < 3; i++)
	{
		layer[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		layer[1][i] = 0; // 初始都未被访问过
	}

	BFS(n, start, array, layer);
	cout << ((is_bipartite(m, layer, edges))?"Yes":"No");

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete[] array;
	for (int i = 0; i < 3; i++)
		delete[] layer[i];
	delete[] layer;
	for (int i = 0; i < m; i++)
		delete[] edges[i];
	delete[] edges;
	return 0;
}