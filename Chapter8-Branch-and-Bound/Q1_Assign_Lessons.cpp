#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int n = 4;
struct node
{
	int teacher;	// 该节点对应的老师
	int lesson;		// 该节点分配的课程
	int cur_time;	// 目前（包括该节点）的总备课时间
	int visited[n]; // 标记老师i有无分配任务
	int sum_time;	// 总时间下界
	node()			// 根节点的构造函数
	{
		cur_time = 0;
		teacher = -1;
		lesson = -1;
		for (int i = 0; i < n; i++)
		{
			visited[i] = -1;
		}
		sum_time = 0;
	}
	// 子节点的构造函数
	node(node *a, int i, int (*array)[n])
	{
		for (int j = 0; j < n; j++)
		{
			visited[j] = a->visited[j]; // 标记已经分配的老师
		}
		teacher = i;
		visited[i] = a->lesson + 1;				   // 本老师得到分配
		lesson = a->lesson + 1;					   // 分配到的是下一个课程
		cur_time = a->cur_time + array[i][lesson]; // 目前时间加上本次分配的时间
		sum_time = cur_time;					   // 总时间下界是目前时间加上之后的时间下界
		// 对于未分配的课程，找每个课程未分配老师的备课时间最小值的加和
		for (int i = lesson + 1; i < n; i++)
		{
			int min_time = 999;
			for (int j = 0; j < n; j++)
			{
				if ((min_time > array[j][i]) && (visited[j] == -1))
				{
					min_time = array[j][i];
				}
			}
			sum_time += min_time;
		}
	}
};

struct cmp
{
	bool operator()(node *&a, node *&b) const // 重载>运算符，在进入优先队列时，节点的比较是节点sum_time值的比较
	{
		return a->sum_time > b->sum_time;
	}
};

void dfs(int (*array)[n])
{
	priority_queue<node *, vector<node *>, cmp> q;
	node *root = new node;
	int bound = 9999;			  // 所有课程分配完的总时间下界
	while (root->lesson != n - 1) // 当最后一个已经分配的课程是n-1时，所有课程分配完成，结束循环
	{
		for (int i = 0; i < n; i++)
		{
			if (root->visited[i] == -1) // 老师i未分配任务
			{
				node *next = new node(root, i, array); // 新建子节点
				if (next->sum_time > bound)			   // 如果预期的总时间下界大于目前分配完的总时间下界，剪枝
				{
					delete next;
				}
				else
				{
					q.push(next);			   // 将该节点压入优先队列
					if (next->lesson == n - 1) // 如果分配完成所有课程，更新下界
					{
						bound = next->sum_time;
					}
				}
			}
		}
		root = q.top();
		q.pop();
	}
	cout << "最优方案为" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "第" << i << "位老师分配第" << root->visited[i] << "门课程" << endl;
	}
	cout << "最小总备课时间为：" << root->sum_time<<endl;
}

int main()
{
	int array[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> array[i][j];
		}
	}
	dfs(array);
}