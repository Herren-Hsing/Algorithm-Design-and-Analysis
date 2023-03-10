#include <iostream>
#include <queue>
#include <stack>
using namespace std;
void BFS_get_componet(int n, int start, int **array)
{
	int *visited_node = new int[n]; // 表示某节点有无被访问
	for (int i = 0; i < n; i++)
	{
		visited_node[i] = 0;
	}
	int *connected_componet = new int[n]; // 储存遍历序列
	int index = 0;
	queue<int> nodes; // 借助队列实现BFS
	visited_node[start] = 1;
	connected_componet[index++] = start;
	nodes.push(start);	   // 将起始节点入队列
	while (!nodes.empty()) // 队列不空时循环
	{
		int cur_node = nodes.front();
		nodes.pop(); // 弹出队首节点
		for (int j = 0; j < n; j++)
		{
			if (array[cur_node][j] && (!visited_node[j])) // 遍历所有节点，如果有未访问过的节点与该节点之间有边
			{
				nodes.push(j);
				visited_node[j] = 1;
				connected_componet[index++] = j; // 该节点属于连通分量，加入序列中
			}
		}
	}
	for (int i = 0; i < index; i++)
	{
		cout << connected_componet[i] << ' '; // 输出遍历序列
	}
	delete visited_node;
	delete connected_componet;
}
void DFS_get_componet(int n, int start, int **array)
{
	int *visited_node = new int[n]; // 表示某节点有无被访问
	for (int i = 0; i < n; i++)
	{
		visited_node[i] = 0;
	}
	int *connected_componet = new int[n]; // 储存遍历序列
	int index = 0;
	stack<int> nodes; // 借助栈实现DFS
	visited_node[start] = 1;
	nodes.push(start); // 起始节点入栈
	while (!nodes.empty())
	{
		int cur_node = nodes.top();
		nodes.pop();
		connected_componet[index++] = cur_node; // 将栈顶元素弹出，并加入遍历序列
		for (int j = n - 1; j >= 0; j--)		// 因为按照索引顺序，所以倒序遍历节点
		{
			if (array[cur_node][j] && (!visited_node[j])) // 遍历所有节点，如果有未访问过的节点与该节点之间有边
			{
				nodes.push(j);
				visited_node[j] = 1;
			}
		}
	}
	for (int i = 0; i < index; i++)
	{
		cout << connected_componet[i] << ' '; // 输出遍历序列
	}
	delete visited_node;
	delete connected_componet;
}

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
	BFS_get_componet(n, start, array); // 借助BFS寻找connected componet
	cout << endl;
	DFS_get_componet(n, start, array); // 借助DFS寻找connected component
	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete[] array;
	return 0;
}