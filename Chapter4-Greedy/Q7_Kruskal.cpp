#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct edges
{
	int length;
	int node1;
	int node2;
	edges(int l, int n1, int n2)
	{
		length = l;
		node1 = n1;
		node2 = n2;
	}
	bool operator>(const edges &e) const // 重载>运算符，比较长度
	{
		return length > e.length;
	}
};
int find(int x, int *root_of_nodes)
{
	if (root_of_nodes[x] != x)
		root_of_nodes[x] = find(root_of_nodes[x], root_of_nodes);
	return root_of_nodes[x];
}
void merge(int x, int y, int *root_of_nodes)
{
	int rootx = find(x, root_of_nodes), rooty = find(y, root_of_nodes);
	if (rootx != rooty)
	{
		root_of_nodes[rootx] = rooty;
	}
}
int main()
{
	int n, e;
	cin >> n >> e;
	int n1, n2, len;
	priority_queue<edges, vector<edges>, greater<edges>> edges_order; // 优先队列存放边，按照边长升序存放
	for (int i = 0; i < e; i++)
	{
		cin >> n1 >> n2 >> len;
		edges_order.emplace(len, n1 - 1, n2 - 1);
	}
	int picked_num = 0, res = 0;
	bool *picked = new bool[n]; // picked用来标记已经加入最小生成树的顶点
	for (int i = 0; i < n; i++)
	{
		picked[i] = false;
	}
	int *root_of_nodes = new int[n]; // 每个节点的祖先，初始时是自己
	for (int i = 0; i < n; i++)
	{
		root_of_nodes[i] = i;
	}
	while (picked_num != n)
	{
		edges tmp = edges_order.top();
		edges_order.pop();
		if (find(tmp.node1, root_of_nodes) == find(tmp.node2, root_of_nodes)) // 如果两个节点的祖先相同，说明两个节点在同一连通分量中，如果加入会构成环
			continue;
		res += tmp.length;
		merge(tmp.node1, tmp.node2, root_of_nodes); // 合并
		// 把两个节点中未加入生成树的节点加入生成树
		if (!picked[tmp.node1])
		{
			picked[tmp.node1] = 1;
			picked_num++;
		}
		if (!picked[tmp.node2])
		{
			picked[tmp.node2] = 1;
			picked_num++;
		}
	}
	cout << res;
	delete[] picked;
	delete[] root_of_nodes;
}