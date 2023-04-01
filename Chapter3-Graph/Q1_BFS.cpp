#include <iostream>
#include <queue>
using namespace std;
int main()
{
	int n, m, start;
	cin >> n >> m >> start;
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
	int input1, input2, edge = m;
	while (edge--) // 获取边，并将矩阵内相应位置值置为1
	{
		cin >> input1 >> input2;
		array[input1][input2] = 1;
		array[input2][input1] = 1;
	}
	int **layer = new int *[2]; // layer第一行表示每个点的层序，第二层表示该点有无被访问过
	for (int i = 0; i < 2; i++)
	{
		layer[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		layer[1][i] = 0; // 初始都未被访问过
	}
	int layer_index = 0;			 // 层数索引
	queue<int> nodes;				 // 借助队列实现BFS
	layer[0][start] = layer_index++; // 起始位于第0层
	layer[1][start] = 1;			 // 起始节点已被访问
	nodes.push(start);				 // 将起始节点入队列
	int cur_num = 1, next_num = 0;	 // cur_num表示当前层未访问的点数，next_num表示下一层的点数
	while (!nodes.empty())			 // 队列不空时循环
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
				nodes.push(j);			   // 该节点入队
				next_num++;				   // 该节点相对于正在访问的节点是下一层的，所以下一层节点数加一
			}
		}
		if (!cur_num) // 当某层节点访问完后，下一层成为本层，层数索引加一
		{
			cur_num = next_num;
			next_num = 0;
			layer_index++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << layer[0][i] << ' '; // 输出每个节点的层数
	}
	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete[] array;
	for (int i = 0; i < 2; i++)
		delete[] layer[i];
	delete[] layer;
	return 0;
}